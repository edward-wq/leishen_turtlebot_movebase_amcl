#ifndef __ASSIGNMENT5_H
#define __ASSIGNMENT5_H
#include "main.h"

extern uint32_t a,b,c;
extern uint32_t Fdcread; 

#define MEAS1_MSB    0x00
#define MEAS1_LSB    0x01
#define MEAS2_MSB    0x02
#define MEAS2_LSB    0x03
#define MEAS3_MSB    0x04
#define MEAS3_LSB    0x05
#define MEAS4_MSB    0x06
#define MEAS4_LSB    0x07


#define CONF_MEAS1   0x08
#define CONF_MEAS2   0x09
#define CONF_MEAS3   0x0A
#define CONF_MEAS4   0x0B

#define FDC_CONF     0x0C


#define OFFSET_CAL_CIN1 0x0D
#define OFFSET_CAL_CIN2 0x0E
#define OFFSET_CAL_CIN3 0x0F
#define OFFSET_CAL_CIN4 0x10

#define GAIN_CAL_CIN1 0x11
#define GAIN_CAL_CIN2 0x12
#define GAIN_CAL_CIN3 0x13
#define GAIN_CAL_CIN4 0x14


#define SLAVE_ADDRESS 0xA0

#define MID           0xFE
#define ID            0xFF    //fdc1004  ID号

////////////////////////////////////////////////////////////////////////////////
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入
///////////////////////////////////////////////////////////////////////////////////////
#define IIC_SCL    PEout(2) //SCL
#define IIC_SDA    PEout(3) //SDA	 
#define READ_SDA   PEin(3)  //输入SDA 

//#define SDA_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}   //定义SDA为输入
//#define SDA_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}   //定义SDA为输出

#define SDA_IN()  {GPIOE->CRL&=0XFFFF0FFF;GPIOE->CRL|=0X00008000;}   //定义SDA为输入
#define SDA_OUT() {GPIOE->CRL&=0XFFFF0FFF;GPIOE->CRL|=0X00003000;}   //定义SDA为输出

void Fdc_Init(void);
uint32_t Fdc_Read(void);
extern uint32_t g_uiFdc1Value;   
extern uint32_t g_uiFdc2Value;
extern uint32_t g_uiFdc3Value;   
extern uint32_t g_uiFdc4Value;
extern unsigned long int g_ulFdcTime;
extern uchar g_ucTch1Flag;
extern uchar g_ucTch2Flag;
extern uchar g_ucTch2Flag_EN;
extern uchar g_ucTch3Flag;
extern uchar g_ucTch4Flag;

void  InfradDisInit(void);
float GetInfrDis(void);
extern float g_fInfrDis ;

void Send2RK3288(int num);
void StepInfr_Gpio_Config(void);
void Step1_2Zero(void);
void EvadeBarrier(void);
void TchResp(void);
void RotaAngle(int g_iRotaAngle);
extern int g_iRotaAngle ;
extern uchar RotFlag ;
extern uchar RotFlag_init ;
extern uchar Rot_PIDFlag;
extern int s_iMileage1;
extern int s_iMileage2;

extern uchar DCReset_Count;//软复位计数	
void DCStallSolved(void);		//解决堵转问题
void speed_up_down();

extern void upload(int data,int flag);//下位机往上位机发数据
extern void su_zifu(int data,char*p);
extern void fall_down(void);//判断摔倒上传数据
extern int face_upward(int face_upward_Angle);//机器人开机先抬头一定角度

extern void Other_features(void);//功能集合
extern void Trouble_printf(void);
extern uchar Debug_printf_flage;//系统故障标志位


#endif


