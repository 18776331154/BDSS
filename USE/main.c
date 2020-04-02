#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/

u8 Flag_Way=0,Flag_Show=0,Flag_Stop=1,Flag_Next;                 //停止标志位和 显示标志位 默认停止 显示打开
int Encoder_Left,Encoder_Right;             //左右编码器的脉冲计数
int Motor_A,Motor_B,Servo,Target_A,Target_B;  //电机舵机控制相关           
int Voltage;                                //电池电压采样相关的变量
u8 delay_50,delay_flag; 										//延时变量
float Velocity_KP=12,Velocity_KI=12;	       //速度控制PID参数	
u16 ADV[128]={0}; 
float Velocity,Angle;
FlagStatus  Dis_Arrive_Flag=SET;	
FlagStatus  CAR_Run_Flag=RESET;		
FlagStatus  Dis_PID_Flag=RESET;							            //车辆运动使能标志位
FlagStatus  Yaw_PID_Flag=RESET;		
int  			  CAR_Velocity=0,CAR_Yaw=0,CAR_Distance=0;				            //车辆目标速度和偏航角

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断分组为2
	delay_init(72);                 //=====延时初始化
	JTAG_Set(JTAG_SWD_DISABLE);     //=====关闭JTAG接口
	LED_Init();                     //=====初始化与 LED 连接的硬件接口
	KEY_Init();
	OLED_Init();                    //=====OLED初始化
	Encoder_Init_TIM2();            //=====初始化编码器（TIM2的编码器接口模式） 
	Encoder_Init_TIM3();            //=====初始化编码器（TIM3的编码器接口模式） 
	EXTIX_Init();                    //=====按键初始化(外部中断的形式)	 
	Adc_Init();                     //=====电池电压采样adc初始化
	Servo_PWM_Init(9999,71);   		//=====初始化PWM50HZ驱动 舵机
	Motor_PWM_Init(7199,0);  				//=====初始化PWM 10KHZ，用于驱动电机 
	
	while(1)
		{     

					if(Flag_Show==0)         //使用MiniBalance APP和OLED显示屏
					{

						oled_show();          //===显示屏打开
					
					}
	
	}
}
