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






int flag;


void TIM1_UP_IRQHandler(void)  
{    
	ENCODER_T *encoder=control_return_to_show();
	if(TIM_GetFlagStatus(TIM1,TIM_FLAG_Update)==SET)			//5ms��ʱ�ж�
	{   
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);				//�����ʱ��1�жϱ�־λ			
		encoder_caculter(encoder);
      
			if(delay_flag==1)
			{
				if(++delay_50==5)
					delay_50=0;
					delay_flag=0;								//���������ṩ50ms�ľ�׼��ʱ
			}
			Encoder_Left=Read_Encoder(2);						//��ȡ��������ֵ
			Encoder_Right=-Read_Encoder(3);						//��ȡ��������ֵ
            Get_RC();
			Kinematic_Analysis(Velocity,Angle);					//С���˶�ѧ����   
			if(Turn_Off(Voltage)==0)							//����������쳣
			{
				Motor_A=Incremental_PI_A(Encoder_Left,Target_A);//�ٶȱջ����Ƽ�����A����PWM
				Motor_B=Incremental_PI_B(Encoder_Right,Target_B);//�ٶȱջ����Ƽ�����B����PWM 
				Xianfu_Pwm();									//PWM�޷�
				Set_Pwm(Motor_A,Motor_B,Servo);					//��ֵ��PWM�Ĵ���  
			}
			else
			Set_Pwm(0,0,SERVO_INIT);							//��ֵ��PWM�Ĵ���  	
		}
		
		Voltage_Temp=Get_battery_volt();						//��ȡ��ص�ѹ		
		Voltage_Count++;										//ƽ��ֵ������
		Voltage_All+=Voltage_Temp;								//��β����ۻ�
		if(Voltage_Count==100) Voltage=Voltage_All/100,Voltage_All=0,Voltage_Count=0;//��ƽ��ֵ		                                   
		if(Flag_Show==0)
			Led_Flash(100);
		else if(Flag_Show==1)
			Led_Flash(0);										//led��˸
				 Key();    //===ɨ�谴��״̬ ����˫�����Ըı�С������״̬
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
/**************************************************************************
�������ܣ�ң��
��ڲ�������
����  ֵ����
**************************************************************************/
void Get_RC(void)
{
	int Yuzhi=2;
	static float Bias,Last_Bias;
  float LY,RX;
	if(Flag_Way==0)//��������
	{
		if(Flag_Direction==0) Velocity=0,Angle=0;   //ֹͣ
//		else if(Flag_Direction==1) Velocity=Bluetooth_Velocity,Angle=0;  //ǰ��
//		else if(Flag_Direction==2) Velocity=Bluetooth_Velocity,Angle=PI/5;  //��ǰ
//		else if(Flag_Direction==3) Velocity=0,Angle=0;   //�������
//		else if(Flag_Direction==4) Velocity=-Bluetooth_Velocity,Angle=PI/5;  // �Һ�
//		else if(Flag_Direction==5) Velocity=-Bluetooth_Velocity,Angle=0;    //����
//		else if(Flag_Direction==6) Velocity=-Bluetooth_Velocity,Angle=-PI/5;  //���
//		else if(Flag_Direction==7) Velocity=0,Angle=0;                       //�������
//		else if(Flag_Direction==8) Velocity=Bluetooth_Velocity,Angle=-PI/5;  //��ǰ
	}
	
}
void automatic_control(u8 now,u8 targe)
{
	u8 error;
	error=now-targe;
	if(error==0)
		Set_Pwm(0,0,SERVO_INIT);
	else
		Set_Pwm(10,10,SERVO_INIT);	
	
}
