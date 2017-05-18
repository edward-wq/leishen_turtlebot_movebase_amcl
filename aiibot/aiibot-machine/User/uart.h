#ifndef __UART_H
#define	__UART_H

#include "main.h"

void USART1_Config(void);
void NVIC_Configuration_UART1(void);

int fputc(int ch, FILE *f);
int fgetc(FILE *f);

void put_char(unsigned char ch,USART_TypeDef * uart);
void put_string(u8 *p,USART_TypeDef * uart);
void put_number(long int value,USART_TypeDef * uart);

void UART4_Config(void);
void NVIC_Configuration_UART4(void);


#endif
