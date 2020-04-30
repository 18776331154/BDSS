#include "sys.h"
#ifndef HDL_MOTOR_H
#define HDL_MOTOR_H
//-----------------OLED端口定义---------------- 
#define OLED_RST_Clr() PBout(3)=0   //RES
#define OLED_RST_Set() PBout(3)=1   //RES

#define OLED_RS_Clr() PAout(15)=0    //DC
#define OLED_RS_Set() PAout(15)=1    //DC

#define OLED_SCLK_Clr()  PBout(5)=0  //SCL
#define OLED_SCLK_Set()  PBout(5)=1   //SCL

#define OLED_SDIN_Clr()  PBout(4)=0   //SDA
#define OLED_SDIN_Set()  PBout(4)=1   //SDA

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void HDL_OLED_INIT(void);
void HDL_OLED_WR_BYTE(u8 dat,u8 cmd);
void HDL_OLED_REFRESH_GRAM(void);
void HDL_OLED_DISPLAY_ON(void);
void HDL_OLED_DISPLAY_OFF(void);

void HDL_OLED_CLEAR(void);

void HDL_OLED_DRAW_POINT(u8 x,u8 y,u8 t);

void HDL_OLED_SHOWNUMBER(u8 x,u8 y,u32 num,u8 len,u8 size);
void HDL_OLED_SHOWCHAR(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void HDL_OLED_SHOWSTRING(u8 x,u8 y,const u8 *p);


#endif