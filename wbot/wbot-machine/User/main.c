/**
  ******************************************************************************
  * @file    main.c
  * @author  liu.c
  * @version V1.0
  * @date    2015年8月10日10:05:39
  * @brief   main.c
  ******************************************************************************
  * @attention
  *
  * 实验平台:STM32BOARDV1.0
	* 网址：www.aiiage.com
  *
  ******************************************************************************
  */
  
#include "main.h"
/**
  * @brief  主函数
  * @param  无
  * @retval 无
*/


int main(void)
{	
	int hehehe=1;	
	LED_GPIO_Config();	
	KEY_GPIO_Config();	
	Fdc_Init();   //触摸传感器初始化	
	//StepInfr_Gpio_Config();//步进电机位置检测	
	InfradDisInit(); //红外测距初始化	
	I2C_MPU6050_Init();//重力传感器接口初始化			
	InitMPU6050();  //初始化MPU6050 
	
	TIM3_PWM_Init();						//DC PWM
	DCMOTORCON_GPIO_Config();
	
	Encoder_Init_TIM2();
	Encoder_Init_TIM5();
	
	STEPMOTORCON_GPIO_Config();
	TIM6_Init();               //STEP1 、2 、3PWM
	
	USART1_Config();//无线 调参 
	NVIC_Configuration_UART1();
	
	UART4_Config(); //rk3288板通信
	NVIC_Configuration_UART4();
	
	N5110_Init();//测试显示数据
	
	//UITRASONIC_Config();//超声波测试
	
	PIDParaSet(2);//1:两轮车 2：三轮车 3：Knet  
	
	SysTick_Init(); //5ms进入中断一次
	
	//STEP2_Angle(360);//上下
	//STEP1_Angle(360);//左右
	
	
	//RotFlag = 1;
	//g_iRotaAngle =180;		 
	//g_fCarSpeedSet_temp = 10 ;
	
	//CCR2_Val = 500;
	//CCR3_Val = 500;
	while(1)
	{

#if 0  //步进电机
		STEP1_Angle( g_iStep1AngleCount ) ;

#elif 0
		scopetransport();				
// 			printf("%f \n",distance1);

#elif 0		//上位机协议				
		LCN5110shownum5(0,0,USART1_RX_BUF[0]);
		LCN5110shownum5(0,1,USART1_RX_BUF[1]);
		LCN5110shownum5(0,2,USART1_RX_BUF[2]);
		LCN5110shownum5(0,3,USART1_RX_BUF[3]);
		LCN5110shownum5(0,4,USART1_RX_BUF[4]);
		LCN5110shownum5(0,5,g_liTemp[3]);

#elif 1				
		Other_features();//开机抬头、触摸、红外、摔倒
	  	Trouble_printf();//打印系统运行故障信息
		
#elif 0
		upload(1,1); 
//          STEP2_Angle(45);//上下
// 		    STEP1_Angle(45);//左右
		Delay(6000000);				 
		Delay(6000000);
		Delay(6000000);
		//Delay(6000000);				 
		//Delay(6000000);
		//Delay(6000000);
		
#elif 0
		g_fCarSpeedSet_temp=5;
		Delay(6000000);				 
		Delay(6000000);			 
		//g_iRotaAngle = -45;
			
		g_fCarSpeedSet_temp=0;
		Delay(6000000);				 
		Delay(6000000);
		
#elif 0

	 	Delay(6000000);				 
		Delay(6000000);			 
		Delay(6000000);
	    if(hehehe==0)
		{
			hehehe=1;
			RotFlag = 1;
			g_iRotaAngle = 180;
		}
	
		//Delay(6000000);				 
		//Delay(6000000);			 
		//Delay(6000000);				 
		//Delay(6000000);
		//Delay(6000000);
#endif	
	};	  
}

/*********************************************END OF FILE**********************/

