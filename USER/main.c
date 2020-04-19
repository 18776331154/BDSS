#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "HDL_MGR.h"
#include "event_queue.h"


int main(void)
{ 
	delay_init();		  //初始化延时函数
	Init_event_queue();
	Hdl_Init();
	while(1)
	{
             
	}
} 


