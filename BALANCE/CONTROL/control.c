#include "control.h"		
#include "event_queue.h"
#include "key.h"
#define T 0.156f
#define L 0.1445f
#define K 622.8f
u8 Flag_Target;
int Voltage_Temp,Voltage_Count,Voltage_All,sum;



/**************************************************************************
函数功能：小车运动数学模型
入口参数：速度和转角
返回  值：无
**************************************************************************/
void Kinematic_Analysis(float velocity,float angle)
{
		Target_A=velocity*(1+T*tan(angle)/2/L); 
		Target_B=velocity*(1-T*tan(angle)/2/L);      //后轮差速
		Servo=SERVO_INIT+angle*K;                    //舵机转向   
}



/********************************************************************************
    功能：	刹车
    参数： 无
    返回：	无
    备注：	利用速度PI控制器将速度置零，然后释放电机
*********************************************************************************/
void CAR_Breaking(void)
{
    CAR_Velocity = 0;
  
    CAR_Run_Flag = SET;

    while( Encoder_Left|| Encoder_Right );

    CAR_Run_Flag = RESET;
    MOTOR_Release();
}


/********************************************************************************
    功能：	车辆直线运动，开环
    参数：  velocity    车辆速度
    返回：	无
    备注：	如果速度为0，刹车
*********************************************************************************/
void CAR_Move(int velocity)
{
    if(velocity == 0) {CAR_Breaking();return;}

    CAR_Velocity = velocity;
    CAR_Run_Flag = SET;
}


void CAR_Dis(int Dis)
{
    CAR_Distance=(int)(1561.0000/21)*Dis;
    Dis_PID_Flag    = SET;
    CAR_Run_Flag    = SET;
    Dis_Arrive_Flag = RESET;
	
    while(Dis_Arrive_Flag == RESET);   
    Dis_PID_Flag    = RESET;
	CAR_Breaking();
}

int flag;


void TIM1_UP_IRQHandler(void)  
{    
	
	     ENCODER_T *encoder=control_return_to_show();
	
	     if(TIM_GetFlagStatus(TIM1,TIM_FLAG_Update)==SET)//5ms定时中断
   {   
	
		 TIM_ClearITPendingBit(TIM1,TIM_IT_Update);                             //===清除定时器1中断标志位			
		 encoder_caculter(encoder);
	    if(CAR_Run_Flag == SET)
	{ 		

              if(Dis_PID_Flag == SET)										          //如果偏航角环PID控制器使能
           {
                   CAR_Velocity = Distance_PID(encoder->angle,CAR_Distance,&Dis_Arrive_Flag);																									
                   Amplitude_Limiting(&CAR_Velocity,7000);        //角速度限幅
           }
		
		            if(delay_flag==1)
			   {
				 if(++delay_50==5)	 delay_50=0,delay_flag=0;                      //给主函数提供50ms的精准延时
			   }
		  	        Encoder_Left=Read_Encoder(2);                                       //===读取编码器的值							 //为了保证M法测速的时间基准，首先读取编码器数据
				    Encoder_Right=-Read_Encoder(3);                                      //===读取编码器的值

					Kinematic_Analysis(Velocity,Angle);     															//小车运动学分析   
			          if(Turn_Off(Voltage)==0)                              							 //===如果不存在异常
				    {
					    Motor_A=Incremental_PI_A(Encoder_Left,Target_A);                   //===速度闭环控制计算电机A最终PWM
					    Motor_B=Incremental_PI_B(Encoder_Right,Target_B);                  //===速度闭环控制计算电机B最终PWM 
					    Xianfu_Pwm();                                                      //===PWM限幅
					    Set_Pwm(Motor_A,Motor_B,Servo);                                 	 //===赋值给PWM寄存器  
				   }
			 else   Set_Pwm(0,0,SERVO_INIT);  
                               						 //===赋值给PWM寄存器  	
	}
	
	           else 
					                  					            //如果车辆运动未使能
                  {
                        MOTOR_Release();                                    //释放电机
                  }	
				
				       Voltage_Temp=Get_battery_volt();		                                 //=====读取电池电压		
					   Voltage_Count++;                                                     //=====平均值计数器
					   Voltage_All+=Voltage_Temp;                                           //=====多次采样累积
				
			if(Voltage_Count==100) Voltage=Voltage_All/100,Voltage_All=0,Voltage_Count=0;//=====求平均值		                                   
			  
			if(Flag_Show==0)				Led_Flash(100);
			else if(Flag_Show==1)	Led_Flash(0);  //led闪烁
				
				
				
//			 Key();    //===扫描按键状态 单击双击可以改变小车运行状态
	}
} 


/**************************************************************************
函数功能：异常关闭电机
入口参数：电压
返回  值：1：异常  0：正常
**************************************************************************/
u8 Turn_Off( int voltage)
{
	    u8 temp;
			if(voltage<740||Flag_Stop==1)//电池电压低于7.4V关闭电机
			{	                                                
              temp=1;                                            
            }
			else
            temp=0;
      return temp;			
}

/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
int Incremental_PI_A (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：左轮PWM、右轮PWM
返回  值：无
**************************************************************************/
void Set_Pwm(int motor_a,int motor_b,int servo)
{
	    if(Flag_Way>=2)//巡线模式下，只允许电机正转
			{
			  if(motor_a<0)motor_a=0;
				if(motor_b<0)motor_b=0;
			}
    	if(motor_a<0)			PWMA1=7200,PWMA2=7200+motor_a;
			else 	            PWMA2=7200,PWMA1=7200-motor_a;
		
		  if(motor_b<0)			PWMB1=7200,PWMB2=7200+motor_b;
			else 	            PWMB2=7200,PWMB1=7200-motor_b;
     SERVO=servo;	
}
/**************************************************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=6900;    //===PWM满幅是7200 限制在6900
    if(Motor_A<-Amplitude) Motor_A=-Amplitude;	
		if(Motor_A>Amplitude)  Motor_A=Amplitude;	
	  if(Motor_B<-Amplitude) Motor_B=-Amplitude;	
		if(Motor_B>Amplitude)  Motor_B=Amplitude;		
		if(Servo<(SERVO_INIT-500))     Servo=SERVO_INIT-500;	  //舵机限幅
		if(Servo>(SERVO_INIT+500))     Servo=SERVO_INIT+500;		  //舵机限幅
}
/**************************************************************************
函数功能：遥控
入口参数：无
返回  值：无
**************************************************************************/

int Distance_PID(int Now,int Target,FlagStatus* Arrive_Flag)
{
		static float Bias,velocity;
		int Bias_abs;
    Bias =Now-Target; 
	Bias_abs=__abs(Bias);
	if(200<Bias_abs)
	velocity=Bias*5;
	else if(5<Bias_abs)
	{
	if(Bias>5)
	velocity=200;	
	else
	velocity=-200;	
	}
	else 
	*Arrive_Flag = SET;																				//将到达FLAG置为SET
   return velocity;  

}
/********************************************************************************
    功能：	取绝对值
    参数：	number 取绝对值的数
    返回：	绝对值
    备注：	无
*********************************************************************************/
int __abs(int number)
{
    return number>0?number:-number;
}

void Amplitude_Limiting(int* Variable,int Range)    
{   
    if(*Variable >  Range)*Variable =  Range;  
    if(*Variable < -Range)*Variable = -Range;
} 

