#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/

u8 Flag_Way=0,Flag_Show=0,Flag_Stop=1,Flag_Next;                 //停止标志位和 显示标志位 默认停止 显示打开
int Encoder_Left,Encoder_Right;             //左右编码器的脉冲计数
int Encoder_A_EXTI,Flag_Direction;  
int Encoder_Temp;
float Velocity,Velocity_Set,Angle,Angle_Set;
int Motor_A,Motor_B,Servo,Target_A,Target_B;  //电机舵机控制相关           
int Voltage;                                //电池电压采样相关的变量
float Show_Data_Mb;                         //全局显示变量，用于显示需要查看的数据
u8 delay_50,delay_flag; 										//延时变量
float Velocity_KP=12,Velocity_KI=12;	       //速度控制PID参数
int PS2_LX=128,PS2_LY=128,PS2_RX=128,PS2_RY=128,PS2_KEY;     //PS2遥控相关
u16 ADV[128]={0};              
u8 Bluetooth_Velocity=30,APP_RX;                 //蓝牙遥控速度和APP接收的数据
u8 CCD_Zhongzhi,CCD_Yuzhi,PID_Send,Flash_Send;   //线性CCD FLASH相关
int Sensor_Left,Sensor_Middle,Sensor_Right,Sensor;//电磁巡线相关
u16 PID_Parameter[10],Flash_Parameter[10];  //Flash相关数组 

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
//    while(select())	{	}	 ;           //=====选择运行模式 	
	Adc_Init();                     //=====电池电压采样adc初始化
	Servo_PWM_Init(9999,71);   		//=====初始化PWM50HZ驱动 舵机
	Motor_PWM_Init(7199,0);  				//=====初始化PWM 10KHZ，用于驱动电机 
    uart3_init(9600); 						//=====串口3初始化 蓝牙
	Flash_Read();	
	while(1)
				{     
//				if(Flash_Send==1)        //写入PID参数到Flash,由app控制该指令
//				{
//				Flash_Write();	
//				Flash_Send=0;	
//				}	
				if(Flag_Show==0)         //使用MiniBalance APP和OLED显示屏
				{
				APP_Show();	
				oled_show();          //===显示屏打开
				}
//				else                      //使用MiniBalance上位机 上位机使用的时候需要严格的时序，故此时关闭app监控部分和OLED显示屏
//				{
//				DataScope();          //开启MiniBalance上位机
//				}	
//				delay_flag=1;	
//				delay_50=0;
//				while(delay_flag);	     //通过定时中断实现的50ms精准延时
				}
}
