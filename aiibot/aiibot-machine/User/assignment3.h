#ifndef __ASSIGNMENT3_H
#define __ASSIGNMENT3_H
#include "main.h"

/*****************************************************/
#define SCLK    GPIO_Pin_2
#define SDIN    GPIO_Pin_3
#define DC      GPIO_Pin_4
#define SCE     GPIO_Pin_5
#define RST     GPIO_Pin_6

//#define SET_DIR_SCLK GPIO_SetBits(PORTA,SCLK)
//#define CLR_DIR_SCLK GPIO_SetBits(PORTA,SCLK,0)
#define SET_OP_SCLK  GPIO_SetBits(GPIOD,SCLK)
#define CLR_OP_SCLK  GPIO_ResetBits(GPIOD,SCLK)

//#define SET_DIR_SDIN GPIO_DDR_1bit(PORTA,SDIN,1)
//#define CLR_DIR_SDIN GPIO_DDR_1bit(PORTA,SDIN,0)
#define SET_OP_SDIN  GPIO_SetBits(GPIOD,SDIN)
#define CLR_OP_SDIN  GPIO_ResetBits(GPIOD,SDIN)

//#define SET_DIR_DC GPIO_DDR_1bit(PORTA,DC,1)
//#define CLR_DIR_DC GPIO_DDR_1bit(PORTA,DC,0)
#define SET_OP_DC  GPIO_SetBits(GPIOD,DC)
#define CLR_OP_DC  GPIO_ResetBits(GPIOD,DC)

//#define SET_DIR_SCE GPIO_DDR_1bit(PORTA,SCE,1)
//#define CLR_DIR_SCE GPIO_DDR_1bit(PORTA,SCE,0)
#define SET_OP_SCE  GPIO_SetBits(GPIOD,SCE)
#define CLR_OP_SCE  GPIO_ResetBits(GPIOD,SCE)

//#define SET_DIR_RST GPIO_DDR_1bit(PORTA,RST,1)
//#define CLR_DIR_RST GPIO_DDR_1bit(PORTA,RST,0)
#define SET_OP_RST  GPIO_SetBits(GPIOD,RST)
#define CLR_OP_RST  GPIO_ResetBits(GPIOD,RST)
/*****************************************************/

extern void N5110_Init(void);
extern void Write_Command(uchar Command);
extern void Write_Data(uchar Command);
extern void Lcd_Clear(void);
extern void Set_XY(uchar x,uchar y);
extern void Write_English_Spring(uchar x,uchar y,uchar *s,uchar num);
extern void Draw_Bmp_Pic(uchar X,uchar Y,uchar *map,uchar Pix_x,uchar Pix_y);

extern void n5110_display_init(void);
//void write_hz(uchar X,uchar Y,uchar hz[][24], uchar num);
extern void LCN5110shownum5(uchar x,uchar y,long int value) ;
extern void LCN5110ShowNum3(uchar x,uchar y,uint value);
extern void LC_DrawLine(uchar x,uchar y);
extern void LC_ClearRow(uchar y);
extern void LC_DrawDot(uchar x,uchar y);

extern const unsigned char font6x8[][6];

void scopetransport (void);   //????????
#endif


