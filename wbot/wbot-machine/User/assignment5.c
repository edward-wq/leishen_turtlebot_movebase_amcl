/**
  ******************************************************************************
  * @file    assignment5.c
  * @author  liu.c
  * @version V1.0
  * @date    2015年10月20日10:25:05
  * @brief   模拟IIC调用函数、触摸电容函数 、硬件iicDMA配置、上传数据上位机、数字转字符、机器人倾斜角度时
  ******************************************************************************
  * @attention
  *
  * 实验平台:STM32BOARDV1.0
	* 网址：www.aiiage.com
  *
  ******************************************************************************
  */
	
#include "assignment5.h"




uint32_t a=0,b=0,c=0;
uint32_t g_uiFdc1Value = 0;   
uint32_t g_uiFdc2Value = 0; 
uint32_t g_uiFdc3Value = 0;   
uint32_t g_uiFdc4Value = 0; 
uint32_t k;
uchar g_ucTch1Flag = 0;
uchar g_ucTch2Flag = 0;
uchar g_ucTch3Flag = 0;
uchar g_ucTch4Flag = 0;
uchar g_ucTch1Flag_EN=0;
uchar g_ucTch2Flag_EN=0;
uchar g_ucTch3Flag_EN=0;
uchar g_ucTch4Flag_EN=0;
//////////////////////////////////////////////////////////////////////////////////
//设定延时

void delay_uss(u16 n)
{
	u8 k=0;
  for(k=0;k<n*5;k++);
}

//初始化IIC
void IIC_Init(void)
{					     
 	RCC->APB2ENR|=1<<6;//先使能外设IO PORTE时钟 							 
	GPIOE->CRL&=0XFFFF00FF;//PE2/3 推挽输出
	GPIOE->CRL|=0X00003300;	   
	GPIOE->ODR|=3<<2;     //PE2,3 输出高
}
//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_uss(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_uss(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;
 	delay_uss(4); 
	IIC_SCL=1;//STOP:when CLK is high DATA change form low to high
 	delay_uss(4); 
	IIC_SDA=1;//发送I2C总线结束信号 						   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;delay_uss(1);	   
	IIC_SCL=1;delay_uss(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_uss(2);
	IIC_SCL=1;
	delay_uss(2);
	IIC_SCL=0;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_uss(2);
	IIC_SCL=1;
	delay_uss(2);
	IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_uss(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_uss(2); 
		IIC_SCL=0;	
		delay_uss(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，      ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_uss(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_uss(1); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}
//发送数据到寄存器
void Signal_Send(unsigned char addr,unsigned char data1,unsigned char data2)
{
	  IIC_Start();
	
	  IIC_Send_Byte(SLAVE_ADDRESS);    //写命令
	  IIC_Wait_Ack();
	
	
	  IIC_Send_Byte(addr);       //发送寄存器地址
		IIC_Wait_Ack();
	
	  IIC_Send_Byte(data1);      //发送高位地址
		IIC_Wait_Ack();
	
	  IIC_Send_Byte(data2);      //发送低位地址
		IIC_Wait_Ack();
	
	  IIC_Stop();
}
//从寄存器中读取数据
u16 Signal_Read(unsigned char readaddr)
{   
	  u16 reg_data,reg_data1,reg_data2;
	
    IIC_Start();
    IIC_Send_Byte(SLAVE_ADDRESS);        //写命令
	  IIC_Wait_Ack();
	  IIC_Send_Byte(readaddr);
	  IIC_Wait_Ack();
	
	  IIC_Start();
	  IIC_Send_Byte(SLAVE_ADDRESS+1);      //读命令
	  IIC_Wait_Ack();
	
	  reg_data1=IIC_Read_Byte(1);          //读取高位数据
	
	  reg_data2=IIC_Read_Byte(0);          //读取低位数据

	  IIC_Stop();
	  reg_data=(reg_data1<<8)+reg_data2;
	 
	  return reg_data;  //返回从寄存器中读取的数据   
}
void FDC1004_Init1(void)   //FDC1004初始化函数
{
      Signal_Send(CONF_MEAS1,0x1C,0x00);
			Signal_Send(FDC_CONF,0x04,0x80);
}

u32 FDC1004_Read1(void)  //FDC1004 读取电容值函数
{
      a=Signal_Read(MEAS1_MSB);
			b=Signal_Read(MEAS1_LSB);
			c=(a<<8)+(b>>8);
      return c;
}
void FDC1004_Init2(void)   //FDC1004初始化函数
{
      Signal_Send(CONF_MEAS2,0x3C,0x00);
			Signal_Send(FDC_CONF,0x04,0x40);
}
u32 FDC1004_Read2(void)  //FDC1004 读取电容值函数
{
      a=Signal_Read(MEAS2_MSB);
			b=Signal_Read(MEAS2_LSB);
			c=(a<<8)+(b>>8);
      return c;
}
void FDC1004_Init3(void)   //FDC1004初始化函数
{
      Signal_Send(CONF_MEAS3,0x5C,0x00);
		  Signal_Send(FDC_CONF,0x04,0x20);
}
u32 FDC1004_Read3(void)  //FDC1004 读取电容值函数
{
      a=Signal_Read(MEAS3_MSB);
			b=Signal_Read(MEAS3_LSB);
			c=(a<<8)+(b>>8);
      return c;
}
void FDC1004_Init4(void)   //FDC1004初始化函数
{
      Signal_Send(CONF_MEAS4,0x7C,0x00);
		  Signal_Send(FDC_CONF,0x04,0x10);
}
u32 FDC1004_Read4(void)  //FDC1004 读取电容值函数
{
      a=Signal_Read(MEAS4_MSB);
			b=Signal_Read(MEAS4_LSB);
			c=(a<<8)+(b>>8);
      return c;
}



void Fdc_Init(void)
{
		IIC_Init();
}

uint32_t Fdc_ReadCh1(void)
{
			//延时一段时间
	    FDC1004_Init1(); 
      return FDC1004_Read1();   //读取电容值			
}
uint32_t Fdc_ReadCh2(void)
{
			//延时一段时间
	    FDC1004_Init2(); 
      return FDC1004_Read2();   //读取电容值			
}
uint32_t Fdc_ReadCh3(void)
{
			//延时一段时间
	    FDC1004_Init3(); 
      return FDC1004_Read3();   //读取电容值			
}
uint32_t Fdc_ReadCh4(void)
{
			//延时一段时间
	    FDC1004_Init4(); 
      return FDC1004_Read4();   //读取电容值			
}

unsigned long int g_ulFdcTime = 0;
/*
 * 函数名：adc_init
 * 描述  ：adc 初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void ADC1_Init(void)
{		
	//PA4 ,通道4，ADC1
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStrucutre;
	
	/* 1 */
  //GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//PA.4配置成模拟输入引脚
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	/* 2*/
	//开启ADC1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );
	//6分频
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); 
	
	//复位ADC1，将外设ADC1的全部寄存器重设为缺省值
	ADC_DeInit(ADC1); 
	
	ADC_InitStrucutre.ADC_ContinuousConvMode=DISABLE;//模数转换工作在单通道模式
	ADC_InitStrucutre.ADC_DataAlign=ADC_DataAlign_Right;//ADC数据右对齐
	ADC_InitStrucutre.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//转换由软件而不是外部触发
	ADC_InitStrucutre.ADC_Mode=ADC_Mode_Independent;//ADC工作在独立模式中
	ADC_InitStrucutre.ADC_NbrOfChannel=1;//顺序进行转换的工作模式
	ADC_InitStrucutre.ADC_ScanConvMode=DISABLE;//模数转换工作在单通道模式
	ADC_Init(ADC1,&ADC_InitStrucutre);
	
	//使能指定的ADC1
	ADC_Cmd(ADC1, ENABLE);	
	
	//校准
	ADC_ResetCalibration(ADC1); //使能复位校准
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	ADC_StartCalibration(ADC1);	 //开启AD校准
	while(ADC_GetCalibrationStatus(ADC1));	//使能指定的ADC1的软件转换启动功能	
	
}	

/*
 * 函数名：Get_Adc           
 * 描述  : 获得原始Adc值  
 * 输入  ：无  
 * 输出  ：单次adc  
 * 调用  ：内部调用
 */	
//获得ADC的值，ch为通道 PA4为通道4
  u16 Get_Adc(void)
	{
		//设置指定的ADC的规则通道组，一个序列，采样时间
		ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1,ADC_SampleTime_239Cycles5 );		    
		//使能制定的ADC1的软件转换启动功能
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);	
		//等待转换结束
			while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
		//返回最近一次的ADC1规则组的转换结果
		return ADC_GetConversionValue(ADC1);
	}

/*
 * 函数名：Get_adc_average        
 * 描述  : 获得平均处理后的adc值
 * 输入  ：进行平均的次数
 * 输出  ：平均的adc值
 * 调用  ：内部调用
 */
	
	u16 Get_adc_average(u8 times)
	{
		u32 temp_val=0;
		u8 t;
		for(t=0;t<times;t++)
		{
			temp_val+=Get_Adc();
			//Delay(50000);
			Delay(59000);//10ms
		}
		return temp_val/times;
	} 	 
	
	void  InfradDisInit(void)
	{//红外测距功能 初始化
			ADC1_Init();
	}
/*
 * 函数名：Get_distance        
 * 描述  : 获取红外测距值
 * 输入  ：无
 * 输出  ：float
 */
	float g_fInfrDis =0;
	float GetInfrDis(void)
	{
		u16 value;
	  float voltage;
	  float distance;
	  //得到输入端ADC值
		value=Get_adc_average(4);
		//ADC值转化为电压值
		voltage=value*3.3/4096;
		//根据datasheet上电压值和距离对应的曲线，进行近似线性拟合得到的电压值和距离的关系
		distance=1/((voltage-0.179922)/22.081450);
		
		return distance;
	}
	
	void Send2RK3288_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED的外设时钟*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE ); 
	
		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
		
		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
			
		/*选择要控制的引脚*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	
		GPIO_Init(GPIOE, &GPIO_InitStructure);
	
		GPIO_ResetBits(GPIOE, GPIO_Pin_15);	
}
		
	void Send2RK3288(int num)
	{	
				static uchar i;
				i = sizeof(num);
	}
	
	
void StepInfr_Gpio_Config(void)
{		

		GPIO_InitTypeDef GPIO_InitStructure;
		
		/*开启按键端口（PD）的时钟*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
				
			/*选择要控制的引脚*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_15; 	
		
		GPIO_Init(GPIOE, &GPIO_InitStructure);			
			/*选择要控制的引脚*/	

////////////////////////////////////////////////////////			
			/*开启按键端口（PA）的时钟*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
				
			/*选择要控制的引脚*/
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 | GPIO_Pin_12; 	
		
		GPIO_Init(GPIOA, &GPIO_InitStructure);			

}
//PA12 左右步进 上层 
// PA11 左右步进 下层
// 0: 挡着 
// 1: 不挡 
void Step1_2Zero(void)
{
		char i = 0;
	
		if( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) == 0 && GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == 1 )
				  STEP1_Angle(i++) ;	
		else
		if( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) == 1 && GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == 0 )
			    STEP1_Angle(i--) ;
		else
		if( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) == 1 && GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == 1)
					g_iStep1PresentPulseCount = 0;
		
		
}
void Step2_2Zero(void)
{
//		if( GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15) == 0 && GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7) == 1 )
				 				
}

void EvadeBarrier(void)
{
		static float fInfrDis_Speed = 0;
		static uchar fInfrDis_Flag = 0;
	  static uchar fInfrDis_Flag2 = 0;
	  static long int fInfrDis_Flag_time=0;
	
		g_fInfrDis   =  GetInfrDis();
	
		if(g_fInfrDis <= 10)
		{			
			 if(fInfrDis_Flag == 0)
			 {
					fInfrDis_Speed = g_fCarSpeedSet_temp;
			 }			
			 g_fCarSpeedSet_temp = -4;
			 fInfrDis_Flag = 1;				 
		}
		else if( fInfrDis_Flag == 1 )
		{
			 if(g_fInfrDis > 10)
			 {
				 g_fCarSpeedSet_temp = fInfrDis_Speed ;
				 fInfrDis_Flag = 0;
			 }			
		}
}


void TchResp(void)
{
	//Fdc1取平均值
	uint32_t Fdc1_count=0;
	uint32_t Fdc1Value_count=0;
	uint32_t Fdc1Value=0;
	uint32_t Fdc1_time=0;
	
	//Fdc2取平均值
	uint32_t Fdc2_count=0;
	uint32_t Fdc2Value_count=0;
	uint32_t Fdc2Value=0;
	uint32_t Fdc2_time=0;
	
	//Fdc3取平均值
	uint32_t Fdc3_count=0;
	uint32_t Fdc3Value_count=0;
	uint32_t Fdc3Value=0;
	uint32_t Fdc3_time=0;	
	
// 		g_uiFdc1Value = Fdc_ReadCh1();
// 		Delay(50000);
	
	 // g_uiFdc2Value = Fdc_ReadCh2();
	//  Delay(50000);
	
// 		g_uiFdc3Value = Fdc_ReadCh3();
// 		Delay(50000);
// 		g_uiFdc4Value = Fdc_ReadCh4();
// 		Delay(50000);
	/*
		if(g_uiFdc1Value>500000 || g_uiFdc3Value>500000)//摸两边耳朵
		{
			
				int temp = Step1PresAngle();//当前角度对应的脉冲数
			
				if(  temp <= -28 )//若当前机器人已转左转？角度大于28度
						STEP1_Angle(30);//则向右？转头30度
				else
				if( (temp >= 28) || ((!g_ucTch1Flag)&&(!g_ucTch3Flag)) ) 	
						STEP1_Angle(-30);
				
				g_ucTch1Flag = 1;
				g_ucTch3Flag = 1;
		}
		else//没有摸耳朵
		if(g_ucTch1Flag == 1||g_ucTch3Flag == 1)
		{
				g_ucTch1Flag = 0;
				g_ucTch3Flag = 0;		
				STEP1_Angle(0);
			
		}
		*/
		
#if 0
		//Fdc1取平均值 2016.4.6
		for(Fdc1_count=0;Fdc1_count<5;Fdc1_count++)
		{
			Fdc1Value = Fdc_ReadCh1();
			Fdc1Value_count=Fdc1Value_count+Fdc1Value;
		  Delay(295000);	//延时50ms ，不能太小，太小频繁的用IIC去读数据容易出错		
    }
		g_uiFdc1Value=(int)(Fdc1Value_count/5);
		
		//Fdc2取平均值 2016.4.6
		for(Fdc2_count=0;Fdc2_count<5;Fdc2_count++)
		{
			Fdc2Value = Fdc_ReadCh2();
			Fdc2Value_count=Fdc2Value_count+Fdc2Value;
		  Delay(295000);	//延时50ms ，不能太小，太小频繁的用IIC去读数据容易出错		
    }
		g_uiFdc2Value=(int)(Fdc2Value_count/5);
		
	  //Fdc3取平均值 2016.4.6
		for(Fdc3_count=0;Fdc3_count<5;Fdc3_count++)
		{
			Fdc3Value = Fdc_ReadCh3();
			Fdc3Value_count=Fdc3Value_count+Fdc3Value;
		  Delay(295000);	//延时50ms ，不能太小，太小频繁的用IIC去读数据容易出错		
    }
		g_uiFdc3Value=(int)(Fdc3Value_count/5);
					
#endif
		
#if 1
		//一起取平均值 2016.4.6
		for(Fdc1_count=0;Fdc1_count<3;Fdc1_count++)
		{
			Fdc1Value = Fdc_ReadCh1();
			Fdc1Value_count=Fdc1Value_count+Fdc1Value;
		  Delay(295000);	//延时50ms ，不能太小，太小频繁的用IIC去读数据容易出错	
			
			Fdc2Value = Fdc_ReadCh2();
			Fdc2Value_count=Fdc2Value_count+Fdc2Value;
		  Delay(295000);	//延时50ms ，不能太小，太小频繁的用IIC去读数据容易出错
			
			Fdc3Value = Fdc_ReadCh3();
			Fdc3Value_count=Fdc3Value_count+Fdc3Value;
		  Delay(295000);	//延时50ms ，不能太小，太小频繁的用IIC去读数据容易出错
    }
		g_uiFdc1Value=(int)(Fdc1Value_count/3);
		g_uiFdc2Value=(int)(Fdc2Value_count/3);
		g_uiFdc3Value=(int)(Fdc3Value_count/3);		
					
#endif	
/**************摸头顶处理程序*************/
	  if( (g_uiFdc2Value>1000000) && (g_ucTch2Flag_EN==0) )//摸头顶,g_ucTch2Flag_EN作用是只让进来一次
	  {
				g_ulFdcTime = SYSTEMTIME;
			
			  if( (Step2PresAngle()) >= (-10) )//当前头的角度处于至少-10度状态以上 不然再低头可能会卡到轴
				{
					 upload(1,1);//若摸了头上传数据到上位机
					 Delay(600000);//100ms
					
					 g_ucTch2Flag = 1;
					 g_ucTch2Flag_EN=1;	
				   STEP2_Angle( (Step2PresAngle()-20) );//在当前的角度下低头20度				     
				}
		}
		else if( (g_ucTch2Flag==1) && ((SYSTEMTIME-g_ulFdcTime)>500) && (g_uiFdc2Value<1000000) )//g_uiFdc2Value<500000 等待手放开
		{
			  upload(2,1);//若抬了头上传数据到上位机
			  Delay(600000);//100ms
			
				g_ucTch2Flag = 0;
			  g_ucTch2Flag_EN=0;	
				STEP2_Angle( (Step2PresAngle()+20) );//在当前的角度下抬头20度			  
		}
		
/**************摸右耳（面对机器人）处理程序******初步定为持续抬头*************/
	  //if( (g_uiFdc1Value>1000000) && (g_ucTch1Flag_EN==0) )//摸头顶,g_ucTch1Flag_EN作用是只让进来一次
		
		if( (g_uiFdc1Value>1000000) )//摸右耳
	  {
				//g_ulFdcTime = SYSTEMTIME;
			
			  //if( (Step2PresAngle()) <= 20 )//当前头的角度处于至少45度(开机已经抬了25度 所以后面只能抬20度)状态以下 不然再抬头可能会卡到轴
				{
					 //upload(1,1);//若摸了头上传数据到上位机
					// Delay(600000);//100ms
					
					 g_ucTch1Flag = 1;
					 g_ucTch1Flag_EN=1;
					
				   g_iStep2PlanThres=0;// 默认500
           g_uiStep2LowSpeed=400;//默认15000
           g_uiStep2HighSpeed=800;//默认800
					
				   STEP2_Angle( (Step2PresAngle()+5) );//在当前的角度抬头5度	
					
				}
		}
		//else if( (g_ucTch1Flag==1) && ((SYSTEMTIME-g_ulFdcTime)>700) && (g_uiFdc1Value<1000000) )//g_uiFdc1Value<500000 等待手放开		
		else if( (g_ucTch1Flag==1) && (g_uiFdc1Value<1000000) )//g_uiFdc1Value<500000 等待手放开
		{
			  //upload(2,1);//若抬了头上传数据到上位机
			  //Delay(600000);//100ms
			
				g_ucTch1Flag = 0;
			  g_ucTch1Flag_EN=0;	
				//STEP2_Angle( (Step2PresAngle()+20) );//在当前的角度下抬头20度		

				g_iStep2PlanThres=500;// 默认500
        g_uiStep2LowSpeed=15000;//默认15000
        g_uiStep2HighSpeed=500;//默认800
		}
		
/**************摸左耳（面对机器人）处理程序******初步定为持续低头*************/
		
		if( (g_uiFdc3Value>1000000) )//摸左耳
	  {
				//g_ulFdcTime = SYSTEMTIME;
			
			  //if( (Step3PresAngle()) <= 20 )//当前头的角度处于至少45度(开机已经抬了25度 所以后面只能抬20度)状态以下 不然再抬头可能会卡到轴
				{
					 //upload(1,1);//若摸了头上传数据到上位机
					// Delay(600000);//100ms
					
					 g_ucTch3Flag = 1;
					 g_ucTch3Flag_EN=1;
					
				   g_iStep2PlanThres=0;// 默认500
           g_uiStep2LowSpeed=400;//默认15000
           g_uiStep2HighSpeed=800;//默认800
					
				   STEP2_Angle( (Step2PresAngle()-5) );//在当前的角度抬头5度	
					
				}
		}
		//else if( (g_ucTch3Flag==1) && ((SYSTEMTIME-g_ulFdcTime)>700) && (g_uiFdc3Value<1000000) )//g_uiFdc1Value<500000 等待手放开		
		else if( (g_ucTch3Flag==1) && (g_uiFdc3Value<1000000) )//g_uiFdc1Value<500000 等待手放开
		{
			  //upload(2,1);//若抬了头上传数据到上位机
			  //Delay(600000);//100ms
			
				g_ucTch3Flag = 0;
			  g_ucTch3Flag_EN=0;	
				//STEP2_Angle( (Step2PresAngle()-20) );//在当前的角度下抬头20度		

				g_iStep2PlanThres=500;// 默认500
        g_uiStep2LowSpeed=15000;//默认15000
        g_uiStep2HighSpeed=500;//默认800
		}
	

}


int g_iRotaAngle = 0;
uchar RotFlag = 0;
uchar RotFlag_init = 0;
uchar Rot_PIDFlag = 0;
int s_iMileage1 =0 ,s_iMileage2 = 0;

#if 0 //要切换PID
void RotaAngle(int Spanangle)
{   

	
	  if(Rot_PIDFlag!=0)//切换PID
	  {
			Rot_PIDFlag++;
			if(Rot_PIDFlag==10)//10*20ms
			{
	  	  g_fSpeed_PL=5;  g_fSpeed_IL=0.8; g_fSpeed_DL = 0.55 ;
				g_fSpeed_PR=5;  g_fSpeed_IR=0.8; g_fSpeed_DR = 0.55;
				Rot_PIDFlag = 0;
			}
    }
		
		if(RotFlag)//转动角度标志位
		{		
			  						
			 /////////切换PID 转角度的PID ////////			 
			 g_fSpeed_PL=15;  g_fSpeed_IL=8; g_fSpeed_DL = 0.5 ;
			 g_fSpeed_PR=15;  g_fSpeed_IR=8; g_fSpeed_DR = 0.5;				
        ///////////////////////		
				
			 
				s_iMileage1 += g_iEncoderSigmaL;
				s_iMileage2 += g_iEncoderSigmaR;
				if(Spanangle > 0)  //若转动角度大于0
				{
						g_fDirectionPwm = 2;
						if((s_iMileage1-s_iMileage2) >= 5.28 * Spanangle)
						{
								s_iMileage1 = 0;
								s_iMileage2 = 0;
								g_fDirectionPwm = 0;
								RotFlag = 0;
							
							  Rot_PIDFlag = 1;//切换PID标志												
						}			
				}
				else   //若转动角度小于0
				{
					 g_fDirectionPwm = -2;	
					 if((s_iMileage2 - s_iMileage1) >= 5.28 * (-Spanangle))
					 {
								s_iMileage1 = 0;
								s_iMileage2 = 0;
								g_fDirectionPwm = 0;
								RotFlag = 0;
						 
						    Rot_PIDFlag = 1;//切换PID标志
					 }
				}
		}
}
#endif

#if 0 //无速度规划
//不用切换PID
void RotaAngle(int Spanangle)
{   
		if(RotFlag)//转动角度标志位
		{
				s_iMileage1 += g_iEncoderSigmaL;
				s_iMileage2 += g_iEncoderSigmaR;
				if(Spanangle > 0)  //若转动角度大于0
				{
						g_fDirectionPwm = 5;
						if((s_iMileage1-s_iMileage2) >= 5.2864 * Spanangle)
						{
								s_iMileage1 = 0;
								s_iMileage2 = 0;
								g_fDirectionPwm = 0;
								RotFlag = 0;
						}			
				}
				else   //若转动角度小于0
				{
					 g_fDirectionPwm = -2;	
					 if((s_iMileage2-s_iMileage1) >= 5.2864 * (-Spanangle))
					 {
								s_iMileage1 = 0;
								s_iMileage2 = 0;
								g_fDirectionPwm = 0;
								RotFlag = 0;
					 }
				}
		}
}
#endif 

#if 1 //尝试速度规划
/*
delt = g_iSpeedControlValueNew - g_iSpeedControlValueOld ;
			g_fSpeedPwm = delt*count/20. + g_iSpeedControlValueOld ;
			if(count == 20)
				count=0;
*/


//不用切换PID
void RotaAngle(int Spanangle)
{
  static int RotaAngle_count=0,RotaAngle_count_old=0;
	static float xi_shu=0.;
	
	if(RotFlag_init == 1 )//为了在转角度的过程中再次来了新的角度值时初始化上一次的参数
	{
		RotFlag_init = 0;
		
	  xi_shu=0.;
		s_iMileage1 = 0; 
		s_iMileage2 = 0;
		g_fDirectionPwm = 0;
		g_fDirectionPwm_old=0;		
		RotaAngle_count=0;
		RotaAngle_count_old=0;
	}
	
	if( (RotFlag==1) && (RotFlag_init==0) )//转动角度标志位
	{			
		s_iMileage1 += g_iEncoderSigmaL;
		s_iMileage2 += g_iEncoderSigmaR;
	
		if( (Spanangle>=10 && Spanangle<=360) || (Spanangle<=-10 && Spanangle>=-360))//转动大于10度就为前20%和后20%为速度规划
			xi_shu=0.2;
		else            //否则一半加速一半减速
			xi_shu=0.5;
		
		if(Spanangle > 0)  //若转动角度大于0
		{				
				if((s_iMileage1-s_iMileage2) <= (5.2864 * Spanangle*xi_shu))//开始20%加速
				{							
					 RotaAngle_count++;
					 g_fDirectionPwm=RotaAngle_count*0.1;//y=k*x
					 g_fDirectionPwm_old=g_fDirectionPwm;
					 RotaAngle_count_old=RotaAngle_count;
				}
				if( (s_iMileage1-s_iMileage2) > (5.2864 * Spanangle*(1-xi_shu)) )//80%以后为减速
				{
					 if((s_iMileage1-s_iMileage2) >= (5.2864 * Spanangle) )//判断转动角度是否到达
					 {
							s_iMileage1 = 0;
							s_iMileage2 = 0;
							g_fDirectionPwm = 0;
							g_fDirectionPwm_old=0;
							RotFlag = 0;
							RotaAngle_count=0;
							RotaAngle_count_old=0;							
					 }
					 else	//否则80%-100%之间为减速
					 {	
						 RotaAngle_count--;
						 g_fDirectionPwm=g_fDirectionPwm_old-(RotaAngle_count_old-RotaAngle_count)*0.1;
						 if(g_fDirectionPwm<=0)
							 g_fDirectionPwm=0;
					 }							
				}		
		}
		else if(Spanangle < 0)   //若转动角度小于0
		{			
			 if((s_iMileage2 - s_iMileage1) <= (5.2864 * (-Spanangle)*xi_shu))//开始20%加速
				{					
					 RotaAngle_count--;
					 g_fDirectionPwm=RotaAngle_count*0.1;//y=k*x
					 g_fDirectionPwm_old=g_fDirectionPwm;
					 RotaAngle_count_old=RotaAngle_count;
				}
				if((s_iMileage2 - s_iMileage1) > (5.2864 * (-Spanangle)*(1-xi_shu)))//80%以后为减速
				{
					 if((s_iMileage2 - s_iMileage1) >= (5.2864 * (-Spanangle)) )//判断转动角度是否到达
					 {
							s_iMileage1 = 0;
							s_iMileage2 = 0;
							g_fDirectionPwm = 0;
							g_fDirectionPwm_old=0;
							RotFlag = 0;
							RotaAngle_count=0;
							RotaAngle_count_old=0;
					 }
					 else//否则80%-100%之间为减速
					 {						 
						 RotaAngle_count++;
						 g_fDirectionPwm=g_fDirectionPwm_old-(RotaAngle_count_old-RotaAngle_count)*0.1;
						 if(g_fDirectionPwm>=0)
								g_fDirectionPwm=0;
						}
				 }
			}
	}
}
#endif 


//利用复位sleep，解决堵转问题
uchar DCReset_Count=0;   //软复位计数	
uchar DCshutdown_Count=0; //防止电机编码器的线接触不良或者断了导致PID积分一直累加到满速转
void DCStallSolved(void) //解决堵转问题
{
		static uchar StallFlag = 1;  //堵转标志位，判断给定速度和编码器返回速度是否一直不一致
	
		if( (g_fCarSpeedSetL!=0 && g_fCarSpeedL==0)|| (g_fCarSpeedSetR!=0 &&  g_fCarSpeedR==0 ))							
			 StallFlag = 1;
		else
			 StallFlag = 0;	
		
		if(StallFlag)
		{
			 DCReset_Count++;
			 DCshutdown_Count++;
		}
		else
		{
			 DCReset_Count = 0;
			 DCshutdown_Count=0;	
		}		
		 //if(DCReset_Count >= 25)//20*25=500ms
		if(DCReset_Count >= 10)//20*10=200ms 
		 //if(DCReset_Count >= 2)//20*2=40ms
		 {
					DCReset_Count=0;
			 
					DCMOTOR1_DERCTION(BACK);
					DCMOTOR2_DERCTION(BACK);
					DCMOTOR_NSLEEP(ON);
					Delay(10);
					DCMOTOR1_DERCTION(FORWARD);
					DCMOTOR2_DERCTION(FORWARD);
					DCMOTOR_NSLEEP(OFF);
			 
// 					g_fSpeedIntegralR=0;//将PID累加的积分置0
// 					g_fSpeedIntegralL=0;
			 
// 					g_iRotaAngle =0;//清除转向的角度
// 					RotFlag = 0;
// 					RotFlag_init=1;
					
					Debug_printf_flage=1;//若出故障打印错误信息				    
		 }
		 if(DCshutdown_Count>=150)//3S内编码器一直没有返回数值则使得速度变0 防止机器人一直高速转,但是在这3S内积分还是会一直累加从而使得电机还是会高速旋转
		 {
			 DCshutdown_Count=0;
			 
			 g_fCarSpeedSet_temp=0;
			 g_fCarSpeedSet=0; 
			 g_fDirectionPwm=0;
			 g_fSpeedIntegralR=0;//将PID累加的积分置0
			 g_fSpeedIntegralL=0;//将PID累加的积分置0
			 
			 g_iRotaAngle =0;//清除转向的角度
			 RotFlag = 0;
			 RotFlag_init=1;
			 
			 Debug_printf_flage=2;//若出故障打印错误信息				
			 
		 }
		 
}



//下位机上传数据给上位机协议 :有效数据位data（4个字节）+功能标志位flag（1个字节）+两个结束符（2个字节）
void upload(int data,int flag)
{
	char data_char[5]="0000";
	char flag_char[5]="0000";
	char end_char[5]="1411";
  char zheng_he[20]={0};
	
	su_zifu(data,data_char);//数字转字符
	su_zifu(flag,flag_char);//数字转字符

#if 1
	zheng_he[0]=data_char[0];
  zheng_he[1]=data_char[1];
	zheng_he[2]=data_char[2];
  zheng_he[3]=data_char[3];

	zheng_he[4]=flag_char[0];
  zheng_he[5]=flag_char[1];
	zheng_he[6]=flag_char[2];
  zheng_he[7]=flag_char[3];

	zheng_he[8]=end_char[0];
  zheng_he[9]=end_char[1];
	zheng_he[10]=end_char[2];
  zheng_he[11]=end_char[3];
	
  zheng_he[12]=0x0d;
  zheng_he[13]=0x0a;
	
	put_string((u8*)zheng_he,UART4);//发送结束符字符串
  //zheng_he[20]=0;
	
#endif	


#if 0	
/*串口4*/	
	put_string((u8*)data_char,UART4);//发送数据字符串
	put_string((u8*)flag_char,UART4);//发送标识符字符串
	put_string((u8*)end_char,UART4);//发送结束符字符串
		
	put_char(0x0d,UART4); 
	put_char(0x0a,UART4);
	
#endif	
	
/*串口1*/
//   put_string((u8*)data_char,USART1);//发送数据字符串
// 	put_string((u8*)flag_char,USART1);//发送标识符字符串
// 	put_string((u8*)end_char,USART1);//发送结束符字符串
// 	
// 	put_char(0x0d,USART1); 
// 	put_char(0x0a,USART1); 
}

//数字转字符
void su_zifu(int data,char*p)
{
	 int i=0;
	 while(data>0)
	 {
			p[3-(i++)]=(data%10)+48;
		  data=data/10;
		}
		p[3-i]=data+48;	
}

 static uchar fall_down_flag=0;
//当机器人倾斜水平面大概20度时
void fall_down(void)
{

	if( (Angle_qingxie>20) && (fall_down_flag==0) )//当机器人倾斜水平面大概20度时 往上位机传数据
	{
		fall_down_flag=1;
		upload(1,2);//往上位机传数据
  }
	Delay(600000);//100ms
	if( (Angle_qingxie<20) && (fall_down_flag==1) )//恢复直立时
	{
		fall_down_flag=0;
		upload(2,2);//往上位机传数据
  }
	Delay(600000);//100ms

}

//机器人开机先抬头一定角度
int face_upward(int face_upward_Angle)
{
	static uchar face_upward_flag=0;
	
	if(face_upward_flag==0)
	{
		 STEP2_Angle(face_upward_Angle);
		 face_upward_flag=1;
	}
	if((g_iStep2PresentPulseCount>=g_iStep2TargetPulseNum) && face_upward_flag==1)//当抬头的角度达到一定角度时 重新定位为0度
  {
		face_upward_flag=2;
		g_iStep2PresentPulseCount=0;
		g_iStep2TargetPulseNum=	0;
    return 1;		
  }
	return 0;

}



//功能集合
static uchar Other_features_flag=0;
void Other_features(void)
{
	
	if( Other_features_flag==1)
	{		
		TchResp(); //触摸		
		//EvadeBarrier(); //红外
		fall_down(); //判断机器人是否摔倒
	}	
	else if( Other_features_flag==0 )//开机先抬头一定角度，抬完头才能进行下一步功能的实现
	{
		face_upward(25);
		Other_features_flag=1;
  }	
	
}

uchar Debug_printf_flage=0;
//系统故障检测并打印信息
void Trouble_printf(void)
{
	
#ifdef Debug_printf //关闭或者打开系统运行调试信息	
	
	switch(Debug_printf_flage)
	{
		 case 1:
			     put_string((u8*)"DCReset_Count---DC---duzhuan \r\n",USART1);break;//点击堵转，所在函数DCStallSolved
		 case 2: 
			     put_string((u8*)"DCshutdown_Count---DC---bianmaqi_broken \r\n",USART1);break;//电机编码器接线不良或者断开，所在函数DCStallSolved
		 //default:
  }
	
#endif
}






