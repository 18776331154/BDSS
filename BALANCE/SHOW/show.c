#include "show.h"
#include "control.h"	
unsigned char i;          //��������
unsigned char Send_Count; //������Ҫ���͵����ݸ���
float Vol;





void oled_show(void)
{
	
	ENCODER_T *encoder=control_return_to_show();
	
	OLED_ShowNumber(0,0, encoder->angle,5,16);
	OLED_ShowNumber(0,10, encoder->angle_speed,5,16);
	OLED_ShowNumber(0,20, encoder->angle_acceleration,5,16);
	OLED_ShowNumber(95,30,encoder->quanshu,5,12);	

	OLED_Refresh_Gram();	
	}

