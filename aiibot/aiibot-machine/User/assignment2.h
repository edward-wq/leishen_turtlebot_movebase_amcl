#ifndef __ASSIGNMENT2_H
#define	__ASSIGNMENT2_H

#include "main.h"


/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define RIGHT  0
#define LEFT 1
#define FORWARD 0
#define BACK 1
#define ON  0
#define OFF 1	
#define Rising 0
#define Falling 1
#define START 0
#define FINISH 1

/* 带参宏，可以像内联函数一样使用 */
#define LED1(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_12)

#define LED2(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_13)
					
/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)			{p->BSRR=i;}			//设置为高电平		
#define digitalLo(p,i)			{p->BRR=i;}				//输出低电平
#define digitalToggle(p,i)		{p->ODR ^=i;}			//输出反转状态


/* 定义控制IO的宏 */
#define LED1_TOGGLE		digitalToggle(GPIOC,GPIO_Pin_12)
#define LED1_OFF		digitalHi(GPIOC,GPIO_Pin_12)
#define LED1_ON			digitalLo(GPIOC,GPIO_Pin_12)

#define LED2_TOGGLE		digitalToggle(GPIOC,GPIO_Pin_13)
#define LED2_OFF		digitalHi(GPIOC,GPIO_Pin_13)
#define LED2_ON			digitalLo(GPIOC,GPIO_Pin_13)

void LED_GPIO_Config(void);
					
#define KEY_ON	0
#define KEY_OFF	1

void KEY_GPIO_Config(void);
void Key_Test(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin,uint8_t Down_state);					

	/* PWM信号电平跳变值 */
// 	u16 CCR1_Val = 500;        
extern 	u16 CCR2_Val;
extern 	u16 CCR3_Val;
// 	u16 CCR4_Val = 125;
void TIM3_PWM_Init(void);

#define MOTOR1_PULSE TIM3->CCR3
#define MOTOR2_PULSE TIM3->CCR2


//#define MOTOR1_PULSE TIM3->CCR2
//#define MOTOR2_PULSE TIM3->CCR3

/* 带参宏，可以像内联函数一样使用 */
#define DCMOTOR1_DERCTION(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_5)



#define DCMOTOR2_DERCTION(a)	if (a)	\
					GPIO_ResetBits(GPIOA,GPIO_Pin_6);\
					else		\
					GPIO_SetBits(GPIOA,GPIO_Pin_6)


//#define DCMOTOR1_DERCTION(a)	if (a)	\
//					GPIO_ResetBits(GPIOA,GPIO_Pin_6);\
//					else		\
//					GPIO_SetBits(GPIOA,GPIO_Pin_6)
//
//#define DCMOTOR2_DERCTION(a)	if (a)	\
//					GPIO_SetBits(GPIOC,GPIO_Pin_5);\
//					else		\
//					GPIO_ResetBits(GPIOC,GPIO_Pin_5)
								
#define DCMOTOR_NSLEEP(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_4)
					
void DCMOTORCON_GPIO_Config(void);

					
/* 带参宏，可以像内联函数一样使用 */
#define STEPMOTOR1_DIRCTION(a)	if (a)	\
					GPIO_ResetBits(GPIOE,GPIO_Pin_10);\
					else		\
					GPIO_SetBits(GPIOE,GPIO_Pin_10)
					
#define STEPMOTOR1_NSLEEP(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_8)					
/* 定义控制IO的宏 */
#define STEPMOTOR1_STEP		digitalToggle(GPIOE,GPIO_Pin_9)

#define STEPMOTOR2_DIRCTION(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_14);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_14)
					
#define STEPMOTOR2_NSLEEP(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_12)					
/* 定义控制IO的宏 */
#define STEPMOTOR2_STEP		digitalToggle(GPIOE,GPIO_Pin_13)

#define STEPMOTOR3_DIRCTION(a)	if (a)	\
					GPIO_ResetBits(GPIOE,GPIO_Pin_6);\
					else		\
					GPIO_SetBits(GPIOE,GPIO_Pin_6)
					
#define STEPMOTOR3_NSLEEP(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_4)					
/* 定义控制IO的宏 */
#define STEPMOTOR3_STEP		digitalToggle( GPIOE,GPIO_Pin_11 )		
					
void STEPMOTORCON_GPIO_Config(void);

void TIM6_Init(void);
void STEP1_SPEED(unsigned long  ui_frq);	
void STEP1_Angle(float angle);
void STEP2_Angle(float angle);					
 
extern int g_iStep1TargetPulseNum;
extern int g_iStep1PresentPulseCount;
extern uchar g_ucStep1TurnFlag;					

extern int g_iStep2TargetPulseNum;
extern int g_iStep2PresentPulseCount;
extern uchar g_ucStep2TurnFlag;	

					
void UITRASONIC_Config(void);	
#define UITRA1_TRIG		digitalToggle(GPIOD ,GPIO_Pin_8)	
#define TRIG1_LOW GPIO_ResetBits(GPIOD,GPIO_Pin_8)
#define TRIG1_HIGH GPIO_SetBits(GPIOD,GPIO_Pin_8)	
#define TRIG2_LOW GPIO_ResetBits(GPIOD,GPIO_Pin_9)
#define TRIG2_HIGH GPIO_SetBits(GPIOD,GPIO_Pin_9)	
#define TRIG3_LOW GPIO_ResetBits(GPIOD,GPIO_Pin_10)
#define TRIG3_HIGH GPIO_SetBits(GPIOD,GPIO_Pin_10)	
#define TRIG4_LOW GPIO_ResetBits(GPIOD,GPIO_Pin_11)
#define TRIG4_HIGH GPIO_SetBits(GPIOD,GPIO_Pin_11)						
void UITRA_Measure(void);
extern float distance1;
extern float distance2;
extern float distance3;	
extern float distance4;	
extern uchar flag_srf;


#define ENCODER_TIM_PERIOD (u16)(65534)   //不可大于65535 因为F103的定时器是16位的。
void Encoder_Init_TIM2(void);
void Encoder_Init_TIM5(void);
void Read_Encoder(void);
extern int g_iEncoderSigmaL;
extern int g_iEncoderSigmaR;
extern u16  EncoderValueL;
extern u16  EncoderValueR;

extern void Speed_down(void);

#endif /* __ASSIGNMENT2_H */

