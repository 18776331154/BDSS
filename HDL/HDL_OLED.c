#include "HDL_OLED.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "delay.h"
 /**************************************************************************
���ߣ�ƽ��С��֮�� 
�Ա����̣�http://shop114407458.taobao.com/
**************************************************************************/		   
u8 OLED_GRAM[128][8];	   
void HDL_OLED_REFRESH_GRAM(void) //ˢ����ʾ
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		HDL_OLED_WR_BYTE (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		HDL_OLED_WR_BYTE (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		HDL_OLED_WR_BYTE (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)HDL_OLED_WR_BYTE(OLED_GRAM[n][i],OLED_DATA); 
	}   
}
/**************************************************************************
�������ܣ���OLEDд��һ���ֽ�
��ڲ�����dat:Ҫд�������/����  ��cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
�� �� ֵ����
**************************************************************************/
void HDL_OLED_WR_BYTE(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_RS_Set();
	else 
	  OLED_RS_Clr();		  
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
	OLED_RS_Set();   	  
} 
//////////////////////////////////////////////////////////////////////////////      
void HDL_OLED_DISPLAY_ON(void)//����OLED��ʾ
{
	HDL_OLED_WR_BYTE(0X8D,OLED_CMD);  //SET DCDC����
	HDL_OLED_WR_BYTE(0X14,OLED_CMD);  //DCDC ON
	HDL_OLED_WR_BYTE(0XAF,OLED_CMD);  //DISPLAY ON
}
//////////////////////////////////////////////////////////////////////////////     
void HDL_OLED_DISPLAY_OFF(void)//�ر�OLED��ʾ
{
	HDL_OLED_WR_BYTE(0X8D,OLED_CMD);  //SET DCDC����
	HDL_OLED_WR_BYTE(0X10,OLED_CMD);  //DCDC OFF
	HDL_OLED_WR_BYTE(0XAE,OLED_CMD);  //DISPLAY OFF
}	
////////////////////////////////////////////////////////////////////////////////
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void HDL_OLED_CLEAR(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM[n][i]=0X00;  
	HDL_OLED_REFRESH_GRAM();//������ʾ
}
/**************************************************************************
�������ܣ���OLED�л���
��ڲ���������:x��0~127��y:0~63  ��t:1 ��� 0,���		
�� �� ֵ����
**************************************************************************/
void HDL_OLED_DRAW_POINT(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//������Χ��.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}
/**************************************************************************
�������ܣ���ָ����λ����ʾһ���ַ�
��ڲ���������:x��0~127��y:0~63 ��mode:0,������ʾ;1,������ʾ	��size:ѡ������ 12-16		
�� �� ֵ����
**************************************************************************/
void HDL_OLED_SHOWCHAR(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{      			    
	u8 temp,t,t1;
	u8 y0=y;
	chr=chr-' ';//�õ�ƫ�ƺ��ֵ				   
    for(t=0;t<size;t++)
    {   
		if(size==12)temp=oled_asc2_1206[chr][t];  //����1206����
		else temp=oled_asc2_1608[chr][t];		 //����1608���� 	                          
        for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)HDL_OLED_DRAW_POINT(x,y,mode);
			else HDL_OLED_DRAW_POINT(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}

//m^n����
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	
/**************************************************************************
�������ܣ���ʾ2������
��ڲ���������:x��0~127��y:0~63 ��num:��ֵ(0~4294967295)��mode:0,���ģʽ 1,����ģʽ�� size:ѡ������ 12-16		
�� �� ֵ����
**************************************************************************/  
void HDL_OLED_SHOWNUMBER(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				HDL_OLED_SHOWCHAR(x+(size/2)*t,y,' ',size,1);
				continue;
			}else enshow=1; 
		 	 
		}
	 	HDL_OLED_SHOWCHAR(x+(size/2)*t,y,temp+'0',size,1); 
	}
} 
/**************************************************************************
�������ܣ���ʾ�ַ���
��ڲ���������:x��0~127��y:0~63 ��*p:�ַ�����ʼ��ַ��
�� �� ֵ����
**************************************************************************/  
void HDL_OLED_SHOWSTRING(u8 x,u8 y,const u8 *p)
{
#define MAX_CHAR_POSX 122
#define MAX_CHAR_POSY 58          
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX){x=0;y+=16;}
        if(y>MAX_CHAR_POSY){y=x=0;HDL_OLED_CLEAR();}
        HDL_OLED_SHOWCHAR(x,y,*p,12,1);	 
        x+=8;
        p++;
    }  
}	
/**************************************************************************
�������ܣ���ʼ��OLED
��ڲ�������
�� �� ֵ����
**************************************************************************/ 
void HDL_OLED_INIT(void)
{ 	 	 
  GPIO_InitTypeDef GPIO_InitStruct;
                                                      //ʹ��GPIOA GPIOBʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE); 
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;        //PB3 4 5�������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;       //PA15 �������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
		

	OLED_RST_Clr();
	delay_ms(100);
	OLED_RST_Set();   //OLED��λ
					  
	HDL_OLED_WR_BYTE(0xAE,OLED_CMD); //�ر���ʾ
	HDL_OLED_WR_BYTE(0xD5,OLED_CMD); //����ʱ�ӷ�Ƶ����,��Ƶ��
	HDL_OLED_WR_BYTE(80,OLED_CMD);   //[3:0],��Ƶ����;[7:4],��Ƶ��
	HDL_OLED_WR_BYTE(0xA8,OLED_CMD); //��������·��
	HDL_OLED_WR_BYTE(0X3F,OLED_CMD); //Ĭ��0X3F(1/64) 
	HDL_OLED_WR_BYTE(0xD3,OLED_CMD); //������ʾƫ��
	HDL_OLED_WR_BYTE(0X00,OLED_CMD); //Ĭ��Ϊ0

	HDL_OLED_WR_BYTE(0x40,OLED_CMD); //������ʾ��ʼ�� [5:0],����.
													    
	HDL_OLED_WR_BYTE(0x8D,OLED_CMD); //��ɱ�����
	HDL_OLED_WR_BYTE(0x14,OLED_CMD); //bit2������/�ر�
	HDL_OLED_WR_BYTE(0x20,OLED_CMD); //�����ڴ��ַģʽ
	HDL_OLED_WR_BYTE(0x02,OLED_CMD); //[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
	HDL_OLED_WR_BYTE(0xA1,OLED_CMD); //���ض�������,bit0:0,0->0;1,0->127;
	HDL_OLED_WR_BYTE(0xC0,OLED_CMD); //����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��
	HDL_OLED_WR_BYTE(0xDA,OLED_CMD); //����COMӲ����������
	HDL_OLED_WR_BYTE(0x12,OLED_CMD); //[5:4]����
		 
	HDL_OLED_WR_BYTE(0x81,OLED_CMD); //�Աȶ�����
	HDL_OLED_WR_BYTE(0xEF,OLED_CMD); //1~255;Ĭ��0X7F (��������,Խ��Խ��)
	HDL_OLED_WR_BYTE(0xD9,OLED_CMD); //����Ԥ�������
	HDL_OLED_WR_BYTE(0xf1,OLED_CMD); //[3:0],PHASE 1;[7:4],PHASE 2;
	HDL_OLED_WR_BYTE(0xDB,OLED_CMD); //����VCOMH ��ѹ����
	HDL_OLED_WR_BYTE(0x30,OLED_CMD); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	HDL_OLED_WR_BYTE(0xA4,OLED_CMD); //ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
	HDL_OLED_WR_BYTE(0xA6,OLED_CMD); //������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ	    						   
	HDL_OLED_WR_BYTE(0xAF,OLED_CMD); //������ʾ	 
	HDL_OLED_CLEAR();                //����
}  


void  tuatu(void)
{


}

