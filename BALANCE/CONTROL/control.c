#include "control.h"		
#include "event_queue.h"
#include "key.h"
#define T 0.156f
#define L 0.1445f
#define K 622.8f
u8 Flag_Target;
int Voltage_Temp,Voltage_Count,Voltage_All,sum;



/**************************************************************************
�������ܣ�С���˶���ѧģ��
��ڲ������ٶȺ�ת��
����  ֵ����
**************************************************************************/
void Kinematic_Analysis(float velocity,float angle)
{
		Target_A=velocity*(1+T*tan(angle)/2/L); 
		Target_B=velocity*(1-T*tan(angle)/2/L);      //���ֲ���
		Servo=SERVO_INIT+angle*K;                    //���ת��   
}



/********************************************************************************
    ���ܣ�	ɲ��
    ������ ��
    ���أ�	��
    ��ע��	�����ٶ�PI���������ٶ����㣬Ȼ���ͷŵ��
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
    ���ܣ�	����ֱ���˶�������
    ������  velocity    �����ٶ�
    ���أ�	��
    ��ע��	����ٶ�Ϊ0��ɲ��
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
	
	     if(TIM_GetFlagStatus(TIM1,TIM_FLAG_Update)==SET)//5ms��ʱ�ж�
   {   
	
		 TIM_ClearITPendingBit(TIM1,TIM_IT_Update);                             //===�����ʱ��1�жϱ�־λ			
		 encoder_caculter(encoder);
	    if(CAR_Run_Flag == SET)
	{ 		

              if(Dis_PID_Flag == SET)										          //���ƫ���ǻ�PID������ʹ��
           {
                   CAR_Velocity = Distance_PID(encoder->angle,CAR_Distance,&Dis_Arrive_Flag);																									
                   Amplitude_Limiting(&CAR_Velocity,7000);        //���ٶ��޷�
           }
		
		            if(delay_flag==1)
			   {
				 if(++delay_50==5)	 delay_50=0,delay_flag=0;                      //���������ṩ50ms�ľ�׼��ʱ
			   }
		  	        Encoder_Left=Read_Encoder(2);                                       //===��ȡ��������ֵ							 //Ϊ�˱�֤M�����ٵ�ʱ���׼�����ȶ�ȡ����������
				    Encoder_Right=-Read_Encoder(3);                                      //===��ȡ��������ֵ

					Kinematic_Analysis(Velocity,Angle);     															//С���˶�ѧ����   
			          if(Turn_Off(Voltage)==0)                              							 //===����������쳣
				    {
					    Motor_A=Incremental_PI_A(Encoder_Left,Target_A);                   //===�ٶȱջ����Ƽ�����A����PWM
					    Motor_B=Incremental_PI_B(Encoder_Right,Target_B);                  //===�ٶȱջ����Ƽ�����B����PWM 
					    Xianfu_Pwm();                                                      //===PWM�޷�
					    Set_Pwm(Motor_A,Motor_B,Servo);                                 	 //===��ֵ��PWM�Ĵ���  
				   }
			 else   Set_Pwm(0,0,SERVO_INIT);  
                               						 //===��ֵ��PWM�Ĵ���  	
	}
	
	           else 
					                  					            //��������˶�δʹ��
                  {
                        MOTOR_Release();                                    //�ͷŵ��
                  }	
				
				       Voltage_Temp=Get_battery_volt();		                                 //=====��ȡ��ص�ѹ		
					   Voltage_Count++;                                                     //=====ƽ��ֵ������
					   Voltage_All+=Voltage_Temp;                                           //=====��β����ۻ�
				
			if(Voltage_Count==100) Voltage=Voltage_All/100,Voltage_All=0,Voltage_Count=0;//=====��ƽ��ֵ		                                   
			  
			if(Flag_Show==0)				Led_Flash(100);
			else if(Flag_Show==1)	Led_Flash(0);  //led��˸
				
				
				
//			 Key();    //===ɨ�谴��״̬ ����˫�����Ըı�С������״̬
	}
} 


/**************************************************************************
�������ܣ��쳣�رյ��
��ڲ�������ѹ
����  ֵ��1���쳣  0������
**************************************************************************/
u8 Turn_Off( int voltage)
{
	    u8 temp;
			if(voltage<740||Flag_Stop==1)//��ص�ѹ����7.4V�رյ��
			{	                                                
              temp=1;                                            
            }
			else
            temp=0;
      return temp;			
}

/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
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
	 Bias=Target-Encoder;                //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ���������PWM������PWM
����  ֵ����
**************************************************************************/
void Set_Pwm(int motor_a,int motor_b,int servo)
{
	    if(Flag_Way>=2)//Ѳ��ģʽ�£�ֻ��������ת
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
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=6900;    //===PWM������7200 ������6900
    if(Motor_A<-Amplitude) Motor_A=-Amplitude;	
		if(Motor_A>Amplitude)  Motor_A=Amplitude;	
	  if(Motor_B<-Amplitude) Motor_B=-Amplitude;	
		if(Motor_B>Amplitude)  Motor_B=Amplitude;		
		if(Servo<(SERVO_INIT-500))     Servo=SERVO_INIT-500;	  //����޷�
		if(Servo>(SERVO_INIT+500))     Servo=SERVO_INIT+500;		  //����޷�
}
/**************************************************************************
�������ܣ�ң��
��ڲ�������
����  ֵ����
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
	*Arrive_Flag = SET;																				//������FLAG��ΪSET
   return velocity;  

}
/********************************************************************************
    ���ܣ�	ȡ����ֵ
    ������	number ȡ����ֵ����
    ���أ�	����ֵ
    ��ע��	��
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

