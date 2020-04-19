#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "BSL_MGR.h"
#include "HDL_MGR.h"
#include "event_queue.h"


int main(void)
{ 
	delay_init();		  	//初始化延时函数
	Init_event_queue();		//初始化事件队列
	Bsl_Init();				//初始化基础服务
	Hdl_Mgr_Init();				//初始化硬件驱动
	for(;;)
	{
	
	}
} 


