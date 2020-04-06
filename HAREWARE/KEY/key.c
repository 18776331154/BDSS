#include "key.h"
#include "event_queue.h"
#include "control.h"
event_type_t LED_ON(event_type_t event)
{  
//	if(EVENT_CAR_RUN==event)
//	{
//	CAR_Dis(5);
//	}
//	
//	
//	return EVENT_CAR_RUN;

	
}

void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);              //使能 PORTA 时钟 
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;                       //上拉输入
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;                           // PA5 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	resgister_event_handle(LED_ON ,EVENT_KEY_PRESSED|EVENT_KEY_LONGPRESSED);//注册LED事件	
} 


/**************************************************************************
函数功能：按键扫描
入口参数：无
返回  值：按键状态 0：无动作 1：单击 
**************************************************************************/
u8 click(void)
{
			static u8 flag_key=1;//按键按松开标志
			if(flag_key&&KEY==0)
			{
			flag_key=0;
			return 1;	// 按键按下
			}
			else if(1==KEY)			flag_key=1;
			return 0;//无按键按下
}
/**************************************************************************
函数功能：按键修改小车运行状态 
入口参数：无
返回  值：无
**************************************************************************/
void Key(void)
{	
	u8 tmp,tmp2;
	tmp=click(); 
	if(tmp==1)Flag_Stop=!Flag_Stop;//单击控制小车的启停
	//if(tmp==2)Flag_Show=!Flag_Show;//双击控制小车的显示状态
	tmp2=Long_Press();          
  if(tmp2==1)Flag_Show=!Flag_Show;//控制小车的显示状态
}
/**************************************************************************
函数功能：长按检测
入口参数：无
返回  值：按键状态 0：无动作 1：长按2s
**************************************************************************/
u8 Long_Press(void)
{
			static u16 Long_Press_count,Long_Press;
	    if(Long_Press==0&&KEY==0)  Long_Press_count++;   //长按标志位未置1
      else                       Long_Press_count=0; 
		  if(Long_Press_count>200)		
			{
				Long_Press=1;
				Long_Press_count=0;
				return 1;
			}				
			 if(Long_Press==1)     //长按标志位置1
			{
				  Long_Press=0;
			}
			return 0;
}
u8  select(void)
{
	  int Angle=260;
	  static u8 flag=1;
	  int count;
	  oled_show_once();  //OLED显示
		Encoder_Temp=abs((short)TIM3->CNT);
    count=Encoder_Temp;
	  if(count<=Angle)								       Flag_Way=0;  //APP遥控模式
		else if(count>Angle&&count<=2*Angle)	 Flag_Way=1;  //PS2遥控模式
		else if(count>2*Angle&&count<=3*Angle) Flag_Way=2;	//CCD巡线模式
		else if(count>3*Angle&&count<=4*Angle) Flag_Way=3;	//电磁巡线模式
	  else TIM3->CNT=0;
	  if(Flag_Next==1)OLED_Clear(),flag=0;  //清除OLED屏幕 程序往下运行
	  return flag;	  
}

