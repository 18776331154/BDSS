#include "sys.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/

u8 Flag_Way=0,Flag_Show=0,Flag_Stop=1,Flag_Next;                 //ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ��
int Encoder_Left,Encoder_Right;             //���ұ��������������
int Encoder_A_EXTI,Flag_Direction;  
int Encoder_Temp;
float Velocity,Velocity_Set,Angle,Angle_Set;
int Motor_A,Motor_B,Servo,Target_A,Target_B;  //�������������           
int Voltage;                                //��ص�ѹ������صı���
float Show_Data_Mb;                         //ȫ����ʾ������������ʾ��Ҫ�鿴������
u8 delay_50,delay_flag; 										//��ʱ����
float Velocity_KP=12,Velocity_KI=12;	       //�ٶȿ���PID����
int PS2_LX=128,PS2_LY=128,PS2_RX=128,PS2_RY=128,PS2_KEY;     //PS2ң�����
u16 ADV[128]={0};              
u8 Bluetooth_Velocity=30,APP_RX;                 //����ң���ٶȺ�APP���յ�����
u8 CCD_Zhongzhi,CCD_Yuzhi,PID_Send,Flash_Send;   //����CCD FLASH���
int Sensor_Left,Sensor_Middle,Sensor_Right,Sensor;//���Ѳ�����
u16 PID_Parameter[10],Flash_Parameter[10];  //Flash������� 

	
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
//	while(select())	{	}	            //=====ѡ������ģʽ 
	Adc_Init();                     //=====��ص�ѹ����adc��ʼ��
	Servo_PWM_Init(9999,71);   		//=====��ʼ��PWM50HZ���� ���
	Motor_PWM_Init(7199,0);  				//=====��ʼ��PWM 10KHZ������������� 
	uart3_init(9600); 						//=====����3��ʼ�� ����

	while(1)
		{     

					if(Flag_Show==0)         //ʹ��MiniBalance APP��OLED��ʾ��
					{
  						APP_Show();	
						oled_show();          //===��ʾ����
					
					}
	
	}
}
