#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "BSL_MGR.h"
#include "HDL_MGR.h"
#include "event_queue.h"


int main(void)
{ 
	delay_init();		  	//��ʼ����ʱ����
	Init_event_queue();		//��ʼ���¼�����
	Bsl_Init();				//��ʼ����������
	Hdl_Mgr_Init();				//��ʼ��Ӳ������
	for(;;)
	{
	
	}
} 


