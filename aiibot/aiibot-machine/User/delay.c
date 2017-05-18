/**
  ******************************************************************************
  * @file    delay.c
  * @author  liu.c
  * @version V1.0
  * @date    2015年8月5日09:58:24
  * @brief   all delay code
  ******************************************************************************
  * @attention
  *
  * 实验平台:stm32Board
  * 论坛    :http://www.aiiage.com
  *
  ******************************************************************************
  */
	
#include "delay.h"
//nCount=6时，大约1us,nCount=5900时，大约1ms;nCount=5900000,为1秒
void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
 	for(; nCount != 0; nCount--);
}
