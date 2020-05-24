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
	delay_init();		  	//��ʼ����ʱ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����жϷ���Ϊ2
	JTAG_Set(SWD_ENABLE);     //�ر�JTAG�ӿ�
	Init_event_queue();		//��ʼ���¼�����
	APF_RUN30CM_INIT();
	Bsl_Init();				//��ʼ����������
	Hdl_Mgr_Init();				//��ʼ��Ӳ������	
    
	while(1)
	{
		APF_AUTORUN_OLED_SHOW();

	}
} 


