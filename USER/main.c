#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "HDL_MGR.h"
#include "event_queue.h"


int main(void)
{ 
	delay_init();		  //��ʼ����ʱ����
	Init_event_queue();
	Hdl_Init();
	while(1)
	{
             
	}
} 


