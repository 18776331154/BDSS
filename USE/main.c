#include "sys.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/

u8 Flag_Way=0,Flag_Show=0,Flag_Stop=1,Flag_Next;                 //ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ��
int Encoder_Left,Encoder_Right;             //���ұ��������������
int Motor_A,Motor_B,Servo,Target_A,Target_B;  //�������������           
int Voltage;                                //��ص�ѹ������صı���
u8 delay_50,delay_flag; 										//��ʱ����
float Velocity_KP=12,Velocity_KI=12;	       //�ٶȿ���PID����	
u16 ADV[128]={0}; 
float Velocity,Angle;
FlagStatus  Dis_Arrive_Flag=SET;	
FlagStatus  CAR_Run_Flag=RESET;		
FlagStatus  Dis_PID_Flag=RESET;							            //�����˶�ʹ�ܱ�־λ
FlagStatus  Yaw_PID_Flag=RESET;		
int  			  CAR_Velocity=0,CAR_Yaw=0,CAR_Distance=0;				            //����Ŀ���ٶȺ�ƫ����

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����жϷ���Ϊ2
	delay_init(72);                 //=====��ʱ��ʼ��
	JTAG_Set(JTAG_SWD_DISABLE);     //=====�ر�JTAG�ӿ�
	LED_Init();                     //=====��ʼ���� LED ���ӵ�Ӳ���ӿ�
	KEY_Init();
	OLED_Init();                    //=====OLED��ʼ��
	Encoder_Init_TIM2();            //=====��ʼ����������TIM2�ı������ӿ�ģʽ�� 
	Encoder_Init_TIM3();            //=====��ʼ����������TIM3�ı������ӿ�ģʽ�� 
	EXTIX_Init();                    //=====������ʼ��(�ⲿ�жϵ���ʽ)	 
	Adc_Init();                     //=====��ص�ѹ����adc��ʼ��
	Servo_PWM_Init(9999,71);   		//=====��ʼ��PWM50HZ���� ���
	Motor_PWM_Init(7199,0);  				//=====��ʼ��PWM 10KHZ������������� 
	
	while(1)
		{     

					if(Flag_Show==0)         //ʹ��MiniBalance APP��OLED��ʾ��
					{

						oled_show();          //===��ʾ����
					
					}
	
	}
}
