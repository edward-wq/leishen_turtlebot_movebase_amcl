/**
    ******************************************************************************
    * @file    assignment2.c
    * @author  liu.c
    * @version V1.0
    * @date    2015年8月10日10:05:39
    * @brief   led配置、按键配置
    ******************************************************************************
    * @attention
    *
    * 实验平台:STM32BOARDV1.0
    * 网址：www.aiiage.com
    *
    ******************************************************************************
    */
    
#include "assignment2.h"  
 /**
    * @brief  初始化控制LED的IO
    * @param  无
    * @retval 无
    */
void LED_GPIO_Config(void)
{       
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*开启LED的外设时钟*/
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE ); 
    
    /*设置引脚模式为通用推挽输出*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
        
    /*设置引脚速率为50MHz */   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
            
    /*选择要控制的引脚*/                                                               
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    
    GPIO_Init(GPIOC, &GPIO_InitStructure);
        
    /*选择要控制的引脚*/    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    
    GPIO_Init(GPIOC, &GPIO_InitStructure);  
            
    /*关闭LED灯*/
    GPIO_SetBits(GPIOC, GPIO_Pin_12|GPIO_Pin_13);    
        
/////////////////////////////测试用代码/////////////////////////////////////////////////////        
//      /*开启LED的外设时钟*/
//      RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); 

//      /*选择要控制的GPIOB引脚*/                                                              
//      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  

//      /*设置引脚模式为通用推挽输出*/
//      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

//      /*设置引脚速率为50MHz */   
//      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//      
//      /*调用库函数，初始化GPIOB0*/
//      GPIO_Init(GPIOA, &GPIO_InitStructure);  
//      
//              /*选择要控制的GPIOB引脚*/                                                              
//      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;   

//      /*设置引脚模式为通用推挽输出*/
//      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

//      /*设置引脚速率为50MHz */   
//      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

//      /*调用库函数，初始化GPIOA9\10*/
//      GPIO_Init(GPIOA, &GPIO_InitStructure);
//      
//      GPIO_SetBits(GPIOA, GPIO_Pin_9|GPIO_Pin_10);    
//      GPIO_ResetBits(GPIOA, GPIO_Pin_9|GPIO_Pin_10);  
}

 /**
    * @brief  初始化KEY1、KEY2
    * @param  无
    * @retval 无
    */
void KEY_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /*开启按键端口（PD）的时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
            
        /*选择要控制的引脚*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;   
    
    GPIO_Init(GPIOD, &GPIO_InitStructure);          
        /*选择要控制的引脚*/    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;   
    
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}   

/**
    * @brief   检测是否有按键按下
    * @param   具体的端口和端口位
    *     @arg GPIOx: x可以是（A...G） 
    *     @arg GPIO_PIN 可以是GPIO_PIN_x（x可以是1...16）
    *   @arg Down_state:按键按下时的电平，1为高电平，0为低电平
    * @retval  按键的状态
    *     @arg KEY_ON:按键按下
    *     @arg KEY_OFF:按键没按下
    */
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin,uint8_t Down_state)
{           
    /*检测是否有按键按下 */
    if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == Down_state ) 
    {      
        /*延时消抖*/
        Delay(10000);       
        if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == Down_state )  
        {    
            /*等待按键释放 */
            while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == Down_state);   
            return  KEY_ON;  
        }
        else
            return KEY_OFF;
    }
    else
        return KEY_OFF;
}

/*-----------------------------------------------------------------*/
uchar Key1Count=0;
void Key_Test(void)
{
        /*config key*/
//      LED1( ON ); 
    if( Key_Scan(GPIOD,GPIO_Pin_0,0) == KEY_ON ) // KEY1
    {
        /*LED1反转*/
        LED2_TOGGLE;
        Key1Count++;
        if(Key1Count%2==0)//为偶数的时候睡眠
            DCMOTOR_NSLEEP(OFF);
        else
            DCMOTOR_NSLEEP(ON);
    } 
    else if( Key_Scan(GPIOD,GPIO_Pin_1,0) == KEY_ON ) // KEY1
    {
        /*LED1反转*/
        LED2_TOGGLE;
    } 

}

/**
    * @brief  配置TIM3复用输出PWM时用到的I/O
    * @param  无
    * @retval 无
    */
static void TIM3_GPIO_Config(void) 
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 设置TIM3CLK 为 72MHZ */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 

    /* GPIOA and GPIOB clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); 

    /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*GPIOB Configuration: TIM3 channel 3 and 4 as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 ;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
    * @brief  配置TIM3输出的PWM信号的模式，如周期、极性、占空比
    * @param  无
    * @retval 无
    */
/*
 * TIMxCLK/CK_PSC --> TIMxCNT --> TIMx_ARR --> TIMxCNT 重新计数
 *                    TIMx_CCR(电平发生变化)
 * 信号周期=(TIMx_ARR +1 ) * 时钟周期
 * 占空比=TIMx_CCR/(TIMx_ARR +1)
 */

    /* PWM信号电平跳变值 */
//  u16 CCR1_Val = 500;        
    u16 CCR2_Val = 0;
    u16 CCR3_Val = 0;
//  u16 CCR4_Val = 125;
static void TIM3_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;


/* ----------------------------------------------------------------------- 
    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR+1)* 100% = 50%
    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR+1)* 100% = 37.5%
    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR+1)* 100% = 25%
    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR+1)* 100% = 12.5%
    ----------------------------------------------------------------------- */

    /* Time base configuration */      
    TIM_TimeBaseStructure.TIM_Period = 999;       //当定时器从0计数到999，即为1000次，为一个定时周期
    TIM_TimeBaseStructure.TIM_Prescaler =3 ;      //设置预分频：
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;  //设置时钟分频系数：不分频(这里用不到)
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

//  /* PWM1 Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;     //配置为PWM模式1 
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   
//  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;      //设置跳变值，当计数器计数到这个值时，电平发生跳变
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  //当定时器计数值小于CCR1_Val时为高电平
//  TIM_OC1Init(TIM3, &TIM_OCInitStructure);     //使能通道1
//  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    /* PWM1 Mode configuration: Channel2 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR2_Val;   //设置通道2的电平跳变值，输出另外一个占空比的PWM
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);    //使能通道2
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

    /* PWM1 Mode configuration: Channel3 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR3_Val; //设置通道3的电平跳变值，输出另外一个占空比的PWM
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);   //使能通道3
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

//  /* PWM1 Mode configuration: Channel4 */
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;   //设置通道4的电平跳变值，输出另外一个占空比的PWM
//  TIM_OC4Init(TIM3, &TIM_OCInitStructure);    //使能通道4
//  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
//  TIM_ARRPreloadConfig(TIM3, ENABLE);          // 使能TIM3重载寄存器ARR

    /* TIM3 enable counter */
    TIM_Cmd(TIM3, ENABLE);                   //使能定时器3    
}

/**
    * @brief  TIM3 输出PWM信号初始化，只要调用这个函数
    *         TIM3的四个通道就会有PWM信号输出
    * @param  无
    * @retval 无
    */
void TIM3_PWM_Init(void)
{
    TIM3_GPIO_Config();
    TIM3_Mode_Config(); 
}
/**
    * @brief  drv8829控制脚初始化
    * @param  无
    * @retval 无
    */
void DCMOTORCON_GPIO_Config(void)
{       
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*开启外设时钟*/
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC , ENABLE ); 
    
    /*设置引脚模式为通用推挽输出*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
        
    /*设置引脚速率为50MHz */   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
            
    /*选择要控制的引脚*/                                                               
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    
    GPIO_Init(GPIOA, &GPIO_InitStructure);
        
    /*选择要控制的引脚*/    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    
    GPIO_Init( GPIOC, &GPIO_InitStructure); 
            
    /*初始电机状态*/
    DCMOTOR1_DERCTION(FORWARD);
    DCMOTOR2_DERCTION(FORWARD);
    DCMOTOR_NSLEEP(OFF);
}

/**
    * @brief  drv8829控制脚初始化
    * @param  无
    * @retval 无
    */
void STEPMOTORCON_GPIO_Config(void)
{       
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*开启LED的外设时钟*/
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE , ENABLE ); 
    
    /*设置引脚模式为通用推挽输出*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
        
    /*设置引脚速率为50MHz */   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//          
//      /*STEP1要配置的引脚*/                                                              
//      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 ;
//  
//      GPIO_Init(GPIOE, &GPIO_InitStructure);
//  
    /*STEP1、2、3要配置的引脚*/                                                            
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_11 ;
    
    GPIO_Init(GPIOE, &GPIO_InitStructure);

            
    /*初始电机状态*/
    STEPMOTOR1_DIRCTION(LEFT);
    STEPMOTOR1_NSLEEP(OFF);
        
    STEPMOTOR2_DIRCTION(LEFT);
    STEPMOTOR2_NSLEEP(OFF);
        
    STEPMOTOR3_DIRCTION(LEFT);
    STEPMOTOR3_NSLEEP(OFF);

}

/**
    * @brief  产生控制步进电机的可调的定时器
    * @param  无
    * @retval 无
    */
void TIM6_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
//  TIM6->CR1&=0xFE; //关闭定时器6，需要计数时再打开，PWM波频率=72M/((ARR+1)*(PSC+1))

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); 
    TIM6->PSC = 72 - 1; // 分频后的时钟为 1000KHz
    TIM6->ARR = 200-1; // 10000 Hz  
    TIM6->CR1 = 0x0004 +0x0001; // URS = 1 //CEN = 1
    TIM6->DIER = 0x0001; // 使能更新中断
}
/**
    * @brief  步进速度调试函数
    * @param  无
    * @retval 无
    */
void STEP1_SPEED(unsigned long speed)
{
    if(0<speed<500000)
        TIM6->ARR = speed; //
        //TIM6->ARR = 500000/speed-1; //
}


/**
    * @brief  步进角度调试函数
    * @param  无
    * @retval 无
    */
int g_iStep1TargetPulseNum=0; //目标角度对应的脉冲数
int g_iStep1PresentPulseCount=0; //当前角度对应的脉冲数
uchar g_ucStep1TurnFlag=0;
void STEP1_Angle(float angle)
{
//      TIM6->ARR =  150-1; //控制频率设定
    g_ucStep1TurnFlag = 1;
    if(angle>=0)
    {
        if(angle >= 45)
            angle = 45;
        g_iStep1TargetPulseNum=angle*92.088;//92.088=1.8*32*5.18     1°  代表的脉冲个数,32是驱动芯片的MO、M1引脚接3.3V设定的
        //g_iStep1TargetPulseNum=angle*1105.92;//1105.92=1.8*32*19.2    1°  代表的脉冲个数,32是驱动芯片的MO、M1引脚接3.3V设定的
        //STEPMOTOR1_DIRCTION(RIGHT);
    }
    else
    {
        if(angle <= -45)
            angle = -45;
        g_iStep1TargetPulseNum=angle*92.088;//  /1.8*32*5.18;
//              STEPMOTOR1_DIRCTION(LEFT);
    }         
//      TIM6->CR1|=0x01; //打开定时器6，开始计数
    STEPMOTOR1_NSLEEP(OFF); // 唤醒步进电机
}

///**
//  * @brief  步进角度调试函数
//  * @param  无
//  * @retval 无
//  */
int g_iStep2TargetPulseNum=0; //目标角度对应的脉冲数
int g_iStep2PresentPulseCount=0; //当前角度对应的脉冲数
uchar g_ucStep2TurnFlag=0;
void STEP2_Angle(float angle)
{
//      TIM6->ARR = 60-1;
    g_ucStep2TurnFlag=1;
        
    if(angle>=0)
    {
        if(angle>=45)
            angle = 45;
        g_iStep2TargetPulseNum = angle*92.088;// /1.8*32*17;
        //STEPMOTOR2_DIRCTION(RIGHT);
    }
    else
    {       
        if(angle<=-20)
            angle = -20;
        g_iStep2TargetPulseNum = angle*92.088; ///1.8*32*17;
        //STEPMOTOR2_DIRCTION(LEFT);
    }
//      TIM6->CR1|=0x01; //打开定时器6，开始计数
//      STEPMOTOR2_NSLEEP(OFF); // 唤醒步进电机
}

//void TIM6_IRQHandler(void)
//{
//  LED2(ON);
//  TIM6->SR=0x0000;//清中断标志
//} 

static void UITRASONIC_GPIO_Config(void)
{       
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*开启外设时钟*/
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO , ENABLE ); 

    
    //开启TIM4的重映射功能，映射到PD12-PD15，中文数据手册p119
    GPIO_PinRemapConfig(GPIO_Remap_TIM4 , ENABLE);
    
    /*设置引脚模式为通用推挽输出*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
        
    /*设置引脚速率为50MHz */   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

            /*TRIG 要配置的引脚*/                                                              
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_ResetBits(GPIOD, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11);
        
    /*设置引脚模式为通用推挽输出*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//浮空输入， 这里为下拉输入
        
    /*设置引脚速率为50MHz */   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

    /*脉冲输入 要配置的引脚*/                                                              
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

    GPIO_Init(GPIOD, &GPIO_InitStructure);

    
}
/// 配置TIM4中断
void NVIC_Configuration_TIM4(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =10;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
/**
    * @brief 超声波脉冲宽度捕获中断初始化
    * @param  无
    * @retval 无
    */
static void TIM4_Mode_Configuration(void)
{
    
    
    TIM_ICInitTypeDef  TIM_ICInitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; // TIM4 时基
    TIM_DeInit(TIM4); //释放TIM4
    
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4 , ENABLE );
    
    TIM_TimeBaseStructure.TIM_Period = 0xffff;                  //自动预装载值
    TIM_TimeBaseStructure.TIM_Prescaler = 72-1;                 //预分频值 TIMx_CLK=1MHz     
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //输入时钟不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
                                                             
    //TIM4_TimeBase 
        
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //| TIM_Channel_2 ;       //输入通道
    TIM_ICInitStructure.TIM_ICPolarity =    TIM_ICPolarity_Rising;     //bu捉上升
    TIM_ICInitStructure.TIM_ICSelection =   TIM_ICSelection_DirectTI;    //
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;       //捕捉不分频
    TIM_ICInitStructure.TIM_ICFilter = 0x0;          //捕捉输入不滤波
    TIM_ICInit(TIM4, &TIM_ICInitStructure); 
    
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;       //输入通道
    TIM_ICInitStructure.TIM_ICPolarity =    TIM_ICPolarity_Rising;     //bu捉上升
    TIM_ICInitStructure.TIM_ICSelection =   TIM_ICSelection_DirectTI;    //
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;       //捕捉不分频
    TIM_ICInitStructure.TIM_ICFilter = 0x0;          //捕捉输入不滤波
    TIM_ICInit(TIM4, &TIM_ICInitStructure); 
    
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;       //输入通道
    TIM_ICInitStructure.TIM_ICPolarity =    TIM_ICPolarity_Rising;     //bu捉上升
    TIM_ICInitStructure.TIM_ICSelection =   TIM_ICSelection_DirectTI;    //
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;       //捕捉不分频
    TIM_ICInitStructure.TIM_ICFilter = 0x0;          //捕捉输入不滤波
    TIM_ICInit(TIM4, &TIM_ICInitStructure); 
    
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;       //输入通道
    TIM_ICInitStructure.TIM_ICPolarity =    TIM_ICPolarity_Rising;     //bu捉上升
    TIM_ICInitStructure.TIM_ICSelection =   TIM_ICSelection_DirectTI;    //
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;       //捕捉不分频
    TIM_ICInitStructure.TIM_ICFilter = 0x0;          //捕捉输入不滤波
    TIM_ICInit(TIM4, &TIM_ICInitStructure); 
    
    
    
    /* Enable the CCx Interrupt Request */
    NVIC_Configuration_TIM4();
    
    TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);
//      TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE); 
//      TIM_ITConfig(TIM4, TIM_IT_CC3, ENABLE);
//      TIM_ITConfig(TIM4, TIM_IT_CC4, ENABLE);
    
    TIM_Cmd(TIM4, ENABLE);
        
}

void UITRASONIC_Config(void)
{
    UITRASONIC_GPIO_Config();
    TIM4_Mode_Configuration();
}

uchar flag_srf=0;
float distance1=0; 
float distance2=0; 
float distance3=0; 
float distance4=0; 
void UITRA_Measure(void)
{
    uint i=0;
    //每次测速前初始化一些值
    flag_srf=START;  //

    TRIG1_HIGH;      //trig SRF05
    Delay(70);/////
    TRIG1_LOW;

    while((flag_srf!=FINISH)&&(i++<40))  //wait transfer over
        Delay(120);
    distance1 = vu16_Freq_Value[0]/5.8; //transfer to real distance cm
    flag_srf = START;  //
    

//       TRIG2_HIGH;      //trig SRF05
//       Delay(70);/////
//       TRIG2_LOW;
//       
//       while( (flag_srf!= FINISH)&&(i++<40))  //wait transfer over
//           Delay(120);
//       distance2 = vu16_Freq_Value[1]/58.; //transfer to real distance cm
//           flag_srf = START;  //
//           

//           TRIG3_HIGH;      //trig SRF05
//       Delay(70);/////
//       TRIG3_LOW;
//       
//       while( (flag_srf!= FINISH)&&(i++<40))  //wait transfer over
//           Delay(120);
//       distance3 = vu16_Freq_Value[2]/58.; //transfer to real distance cm
//           flag_srf = START;  //
//           

//           TRIG4_HIGH;      //trig SRF05
//       Delay(70);/////
//       TRIG4_LOW;
//       
//       while( (flag_srf!= FINISH)&&(i++<40))  //wait transfer over
//           Delay(120);
//       distance4 = vu16_Freq_Value[3]/58.; //transfer to real distance cm
//           flag_srf = START;  //
}


/**************************************************************************
函数功能：把TIM2初始化为编码器接口模式
入口参数：无
返回  值：无
**************************************************************************/
void Encoder_Init_TIM2(void)
{
    RCC->APB1ENR|=1<<0;     //TIM2时钟使能
    RCC->APB2ENR|=1<<2;    //使能PORTA时钟
    GPIOA->CRL&=0XFFFFFFF0;//PA0
    GPIOA->CRL|=0X00000004;//浮空输入
    /* 把定时器初始化为编码器模式 */ 
    TIM2->PSC = 0x0;//预分频器
    TIM2->ARR = 65535;
    TIM2->SMCR |= 7<<0;
    TIM2->SMCR |= 5<<4;
    TIM2->CCMR1 |= 1<<0;
    TIM2->CCER |= 0<<1;
    TIM2->CR1 |= 0x01;    //CEN=1，使能定时器   
}
/**************************************************************************
函数功能：把TIM5初始化为编码器接口模式
入口参数：无
返回  值：无
**************************************************************************/
void Encoder_Init_TIM5(void)
{
    RCC->APB1ENR|=1<<3;     //TIM5时钟使能
    RCC->APB2ENR|=1<<2;    //使能PORTa时钟
    GPIOA->CRL&=0XFFFFFF0F;//PA1
    GPIOA->CRL|=0X00000040;//浮空输入
    /* 把定时器初始化为编码器模式 */ 
    TIM5->PSC = 0x0;//预分频器
    TIM5->ARR = 65535;
    TIM5->CCMR1 |= 1<<8;
    TIM5->CCER |= 0<<5;
    TIM5->SMCR |= 7<<0;
    TIM5->SMCR |= 6<<4;
    TIM5->CR1 |= 0x01;    //CEN=1，使能定时器   
}
/**************************************************************************
函数功能：单位时间读取编码器计数
入口参数：定时器
返回  值：速度值
**************************************************************************/
int g_iEncoderSigmaL=0;
int g_iEncoderSigmaR=0;
u16  EncoderValueL=0;
u16  EncoderValueR=0;
void Read_Encoder(void)
{
    EncoderValueL = TIM5 -> CNT;  
    TIM5 -> CNT=0;      
    EncoderValueR= TIM2 -> CNT;  
    TIM2 -> CNT= 0 ;

//    EncoderValueL = TIM2 -> CNT;  
//    TIM2 -> CNT=0;      
//    EncoderValueR= TIM5 -> CNT;  
//    TIM5 -> CNT= 0 ;

    if(Encoder1Flag==FORWARD)
        g_iEncoderSigmaL += EncoderValueL;
    else
        g_iEncoderSigmaL -= EncoderValueL;

    if(Encoder2Flag == FORWARD)
        g_iEncoderSigmaR += EncoderValueR;
    else
        g_iEncoderSigmaR -= EncoderValueR;
}


/**************************************************************************
函数功能：当车速要停下来的时候使得车子缓慢停止
入口参数：无
返回  值：无
**************************************************************************/

u8 Speed_down_flage=0;
float Speed_down_intSpeed=0;
u8 Speed_down_intSpeed_flage=0;
unsigned long int Speed_down_time=0;

//检测速度停下来的时候缓慢停下
void Speed_down(void)
{
    if( (g_fCarSpeedSet!=0) && (Speed_down_intSpeed_flage==0) )//检测到速度不为0时
    {
        Speed_down_flage=1;
        Speed_down_intSpeed=g_fCarSpeedSet;//将当前的速度值赋值给这个变量
    } 
    
    if( (g_fCarSpeedSet==0) && (Speed_down_flage==1) )//检测到要车停止的时候
    {
        Speed_down_flage=2;
        Speed_down_intSpeed_flage=1;
        Speed_down_time=SYSTEMTIME;
        
        //pid切换回去
        g_fSpeed_PL=5;  g_fSpeed_IL=0.8; g_fSpeed_DL = 0.55 ;
        g_fSpeed_PR=5;  g_fSpeed_IR=0.8; g_fSpeed_DR = 0.55;
        
        //清除转弯
        RotFlag = 0;
        g_iRotaAngle =0;
        g_fDirectionPwm = 0;
    } 
    
    if( Speed_down_flage==2 )//当要停止的时候
    {
        if( (SYSTEMTIME-Speed_down_time) >30 )//g_fCarSpeedSet速度慢慢减下来
        {
            Speed_down_time=SYSTEMTIME;
            
            if(Speed_down_intSpeed>0)//车速为正
            {
                g_fCarSpeedSet=Speed_down_intSpeed--;
                if(Speed_down_intSpeed <=0 )
                {
                    g_fCarSpeedSet=0;
                    Speed_down_flage=0;
                    Speed_down_intSpeed_flage=0;
                    Speed_down_time=0;
                }
            }
            else if(Speed_down_intSpeed<0)//车速为负
            {
                g_fCarSpeedSet=Speed_down_intSpeed++;
                if(Speed_down_intSpeed >=0 )
                {
                    g_fCarSpeedSet=0;
                    Speed_down_flage=0;
                    Speed_down_intSpeed_flage=0;
                    Speed_down_time=0;
                }
            }      
        }
    }
}








/*********************************************END OF FILE**********************/
