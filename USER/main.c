#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "BSL_MGR.h"
#include "HDL_MGR.h"
#include "event_queue.h"
#include "APF_AUTORUN.h"
#include "HDL_OLED.h"
#include "GLOBAL.h"
#include "HDL_LED.h"
#include "BSL_ENCODER.h"
u8 t=0;
#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define JTAG_SWD_ENABLE    0X00	   
int average;
u8 distance;
int main(void)
{ 
	delay_init();		  	//初始化延时函数
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断分组为2
	JTAG_Set(SWD_ENABLE);     //关闭JTAG接口
	Init_event_queue();		//初始化事件队列
	APF_RUN30CM_INIT();
	Bsl_Init();				//初始化基础服务
	Hdl_Mgr_Init();				//初始化硬件驱动	
    
	while(1)
	{
		APF_AUTORUN_OLED_SHOW();

	}
} 


