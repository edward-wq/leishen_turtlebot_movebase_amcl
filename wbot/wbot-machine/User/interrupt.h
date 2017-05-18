#ifndef __INTERRUPT_H
#define	__INTERRUPT_H

#include "main.h"
void USART1_IRQHandler(void);
void UART4_IRQHandler(void);
void SysTick_Init (void);
extern vu16 vu16_Freq_Value[4];
extern uchar uc_TrigFlag;
extern uchar CaptureEdgeFlag;

extern uchar USART1_RX_BUF[8];
extern u16 USART1_RX_STA;

extern uchar UART4_RX_BUF[5];
extern u16 UART4_RX_STA;

extern long int g_liTemp[4];
extern unsigned long int SYSTEMTIME; //系统时基
extern uchar UART4ReiFlag;
#endif /* __INTERRUPT_H */
