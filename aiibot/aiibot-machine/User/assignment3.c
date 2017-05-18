//*******************************************************************************
//*  文件名称：5110.c
//*  修改日期：2011/08/30
//*  创建人：Changer
//*  编译环境: iccavr7.22
//*  描述: NOKIA5110液晶屏（48*84）驱动程序，液晶控制器PCD8544，MCU时钟8M，
///*****************************************************************************/

#include "assignment3.h"
//#include "zm.h"

void Write_Command(uchar Command)
{
    uchar i;
    CLR_OP_SCE;
    CLR_OP_DC;                  //Command
    
    for(i = 0; i < 8 ;i++)
    {
        CLR_OP_SCLK;
        if(Command & (1 << (7-i)))
            SET_OP_SDIN;
        else
            CLR_OP_SDIN;
        SET_OP_SCLK;    
    }
    SET_OP_SCE;
}

void Write_Data(uchar Data)
{
    uchar i;
    CLR_OP_SCE;
    SET_OP_DC;                  //Data
    for(i = 0; i < 8 ;i++)
    {
        CLR_OP_SCLK;
        if(Data & (1 << (7-i)))
            SET_OP_SDIN;
        else
            CLR_OP_SDIN;
        SET_OP_SCLK;    
    }
    SET_OP_SCE;
}


void Lcd_Clear(void)
{
    uint i;
    Write_Command(0x20);        //H = 0
    Write_Command(0x0c);        //普通模式
    Write_Command(0x80);        //水平起始
    for(i = 0; i < 504; i++)    //
    {
        Write_Data(0x00);
    }   
}

static void N5110_GPIO_Config(void)
{       
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*开启LED的外设时钟*/
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE ); 

    /*设置引脚模式为通用推挽输出*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
    
    /*设置引脚速率为50MHz */   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
        
    /*选择要控制的引脚*/                                                               
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;

    GPIO_Init(GPIOD, &GPIO_InitStructure);  
        
    /*设置*/
    GPIO_SetBits(GPIOD, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 );           
}

void N5110_Init(void)
{
    N5110_GPIO_Config();
    //RESET
    SET_OP_RST;
    CLR_OP_RST;
    Delay(72);
    SET_OP_RST;
    //SELECT LCD
    CLR_OP_SCE;
    Delay(72);
    //SET_OP_SCE;
    //delay_us(1);
    //WRITE COMMAND
    Write_Command(0x21);        //扩展指令
    Write_Command(0xc8);        //Vop
    Write_Command(0x06);        //temp
    Write_Command(0x13);        //1:48
    Write_Command(0x20);        //基础指令
    Lcd_Clear();                // 清屏
    Write_Command(0x0d);        // 设定显示模式，正常显示 d可以设置成反显 
    CLR_OP_SCE;        
}

void Set_XY(uchar x,uchar y)
{
    Write_Command(0x40 | y);    // column 0-5
    Write_Command(0x80 | x);    // row 0-83
}

/*------------------------------------------------------
函数： 显示英文字符串
参数： uchar *s    字符指针
       uchar x     起始位置横坐标 0-83
       uchar y     起始位置纵坐标 0-5
       uchar num   字符个数
------------------------------------------------------*/
void Write_English_Spring(uchar x,uchar y,uchar *s,uchar num)
{
    uchar i,j;
    Set_XY(x,y);
    for(i = 0; i < num; i++)
    {
        //*s -= 32;
        for(j = 0;j < 6; j++)
        {
            Write_Data(font6x8[*s-32][j]);
        }
        s++;
    }
}

/*------------------------------------------------------
函数：  显示BMP图像
参数：  uchar X,Y   ：位图绘制的起始X、Y坐标；
        uchar *map    ：位图点阵数据；
        uchar Pix_x   ：位图像素（长）
        uchar Pix_y   ：位图像素（宽）
------------------------------------------------------*/
void Draw_Bmp_Pic(uchar X,uchar Y,uchar *map,uchar Pix_x,uchar Pix_y)
{
    unsigned int i,n;
    unsigned char row;
    if (Pix_y%8==0){
        row=Pix_y/8;             //计算位图所占行数
    }else{
        row=Pix_y/8+1;
    }
    for (n=0;n<row;n++){
        Set_XY(X,Y);
        for(i=0; i<Pix_x; i++){
            Write_Data(map[i+n*Pix_x]);
        }
        Y++;                     //换行
    }      
}

/*void write_hz(uchar X,uchar Y,uchar hz[][24], uchar num)
{
    uchar i;
    uchar x=0,y=0;
    uchar k;    //the k num;
    for(k=0;k<num;k++)
    {
        for(i=0;i<24;i++)
        {
            Set_XY(X+x,Y+y);
            Write_Data(hz[k][i]);
            x++;
            if(x==12)
            {
                x=0;
                y=1; //change a row
            }
        }
        y=0;
        X+=13; //change a lin
        if(X>71)
        {
            X=0;
            Y+=2;
        }   
    }   
}*/
void n5110_display_init(void)
{
    //Write_English_Spring(0,0,"EncOff:",7);
    //LCN5110shownum(40,0,g_lnEncOffset);
    //Write_English_Spring(0,1,"EncRf:",6); 
}

//time:43584
void LCN5110shownum5(uchar x,uchar y,long int value)  
{
    u8 w,q,b,s,g,p[7]=" ";
    value=value%100000;
    if(value>=0)
    {    
        w=value/10000+48;
        q=value%10000/1000+48;
        b=value%1000/100+48;
        s=value%100/10+48;
        g=value%10+48;
        p[0]=' ';
        p[1]=w;
        p[2]=q;
        p[3]=b;
        p[4]=s;
        p[5]=g;
    }
    else
    {
        value=-value;
        w=value/10000+48;
        q=value%10000/1000+48;
        b=value%1000/100+48;
        s=value%100/10+48;
        g=value%10+48;
        p[0]='-';
        p[1]=w;
        p[2]=q;
        p[3]=b;
        p[4]=s;
        p[5]=g;
    }
    Write_English_Spring(x,y,p,6);
}

void LCN5110ShowNum3(uchar x,uchar y,uint value)  
{
    u8 b,s,g,p[3]=" ";
    value=value%1000;
    b=value/100+48;
    s=value/10%10+48;
    g=value%10+48;
    p[0]=b;
    p[1]=s;
    p[2]=g;
    
    Write_English_Spring(x,y,p,3); 
}
//画一条竖线
//2013年3月6日11:20:00
//liucheng
//time:23389coreclk
void LC_DrawLine(uchar x,uchar y)
{
    Set_XY(x,y);
    Write_Data(0xFF);
}
//清空一行8*84
//2013年3月6日11:20:49
//liucheng
void LC_ClearRow(uchar y)
{
    uchar i=0;
    Set_XY(0,y);
    for(i=0;i<84;i++)
        Write_Data(0);
}
//画一个点
//2013年3月8日19:14:06
//liucheng
void LC_DrawDot(uchar x,uchar y)
{
    Set_XY(x,y);
    Write_Data(0x18);
    Write_Data(0x18);
}

const unsigned char font6x8[][6] =
{
    
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // sp
    { 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 },   // !
    { 0x00, 0x00, 0x07, 0x00, 0x07, 0x00 },   // "
    { 0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 },   // #
    { 0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   // $
    { 0x00, 0x62, 0x64, 0x08, 0x13, 0x23 },   // %
    { 0x00, 0x36, 0x49, 0x55, 0x22, 0x50 },   // &
    { 0x00, 0x00, 0x05, 0x03, 0x00, 0x00 },   // '
    { 0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 },   // (
    { 0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 },   // )
    { 0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 },   // *
    { 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 },   // +
    { 0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 },   // ,
    { 0x00, 0x08, 0x08, 0x08, 0x08, 0x08 },   // -
    { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 },   // .
    { 0x00, 0x20, 0x10, 0x08, 0x04, 0x02 },   // /
    { 0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0
    { 0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1
    { 0x00, 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2
    { 0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3
    { 0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4
    { 0x00, 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5
    { 0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6
    { 0x00, 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7
    { 0x00, 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8
    { 0x00, 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9
    { 0x00, 0x00, 0x36, 0x36, 0x00, 0x00 },   // :
    { 0x00, 0x00, 0x56, 0x36, 0x00, 0x00 },   // ;
    { 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 },   // <
    { 0x00, 0x14, 0x14, 0x14, 0x14, 0x14 },   // =
    { 0x00, 0x00, 0x41, 0x22, 0x14, 0x08 },   // >
    { 0x00, 0x02, 0x01, 0x51, 0x09, 0x06 },   // ?
    { 0x00, 0x32, 0x49, 0x59, 0x51, 0x3E },   // @
    { 0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C },   // A
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C
    { 0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D
    { 0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F
    { 0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G
    { 0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H
    { 0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I
    { 0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J
    { 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K
    { 0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L
    { 0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M
    { 0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N
    { 0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O
    { 0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P
    { 0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q
    { 0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R
    { 0x00, 0x46, 0x49, 0x49, 0x49, 0x31 },   // S
    { 0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T
    { 0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U
    { 0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V
    { 0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W
    { 0x00, 0x63, 0x14, 0x08, 0x14, 0x63 },   // X
    { 0x00, 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y
    { 0x00, 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z
    { 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [
    { 0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55 },   // 55
    { 0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ]
    { 0x00, 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^
    { 0x00, 0x40, 0x40, 0x40, 0x40, 0x40 },   // _
    { 0x00, 0x00, 0x01, 0x02, 0x04, 0x00 },   // '
    { 0x00, 0x20, 0x54, 0x54, 0x54, 0x78 },   // a
    { 0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x20 },   // c
    { 0x00, 0x38, 0x44, 0x44, 0x48, 0x7F },   // d
    { 0x00, 0x38, 0x54, 0x54, 0x54, 0x18 },   // e
    { 0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f
    { 0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C },   // g
    { 0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h
    { 0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i
    { 0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 },   // j
    { 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k
    { 0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l
    { 0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n
    { 0x00, 0x38, 0x44, 0x44, 0x44, 0x38 },   // o
    { 0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 },   // p
    { 0x00, 0x18, 0x24, 0x24, 0x18, 0xFC },   // q
    { 0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r
    { 0x00, 0x48, 0x54, 0x54, 0x54, 0x20 },   // s
    { 0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t
    { 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u
    { 0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v
    { 0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w
    { 0x00, 0x44, 0x28, 0x10, 0x28, 0x44 },   // x
    { 0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C },   // y
    { 0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 },   // z
    { 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 }    // horiz lines
};


unsigned int CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp=0xffff;

    for (i=0;i<CRC_CNT; i++)
    {      
        CRC_Temp ^= Buf[i];//^:??
        for (j=0;j<8;j++) 
        {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
} 


void scopetransport (void)   //
 {  
    uint crc_temp;  //
    uchar i = 0;

    uchar TxBuf[10] = {0};       //
//    float Accel_z=Accel_x=Gyro_y=Angle_az=65000;      
//    TxBuf[0] =   (int)Accel_z%256;     //g_fGyroTemp
//    TxBuf[1] =  (int)Accel_z/256;
#ifdef BALANCE
    TxBuf[0] = (uchar)(g_fCarSpeedSet+100)%256;
    TxBuf[1] = (uchar)((g_fCarSpeedSet+100)/256);
    
    TxBuf[2] = (uchar)(g_fCarSpeed+100)%256;
    TxBuf[3] = (uchar)((g_fCarSpeed+100)/256);
    
    TxBuf[4] = (uchar)(g_fCarSpeedSet+100)%256;
    TxBuf[5] = (uchar)((g_fCarSpeedSet+100)/256);

    TxBuf[6] = (uchar)(g_fCarSpeedSet+100)%256;
    TxBuf[7] = (uchar)((g_fCarSpeedSet+100)/256);
#else
    TxBuf[0] = (uchar)(g_fCarSpeedSet+100)%256;
    TxBuf[1] = (uchar)((g_fCarSpeedSet+100)/256);
    
    TxBuf[2] = (uchar)(g_fCarSpeedL+100)%256;
    TxBuf[3] = (uchar)((g_fCarSpeedL+100)/256);
    
    TxBuf[4] = (uchar)(g_fCarSpeedSet+100)%256;
    TxBuf[5] = (uchar)((g_fCarSpeedSet+100)/256);

    TxBuf[6] = (uchar)(g_fCarSpeedR+100)%256;
    TxBuf[7] = (uchar)((g_fCarSpeedR+100)/256);
#endif
    
    
    crc_temp=CRC_CHECK(TxBuf,8); //  0x4001244C DMA_Mode_Circular; DMA_InitStructure. DMA_InitTypeDef
    TxBuf[8]=crc_temp%256;
    TxBuf[9]=crc_temp/256;
    for(i=0;i<10;i++){ 
            put_char(TxBuf[i],USART1);  //
    }        
}


/*
void scopetransport (void)   //
{  
    uint crc_temp;  //
    uchar i = 0;

    uchar TxBuf[10] = {0};       //
    
    TxBuf[0] = (uchar)(g_fCarSpeedSet+100)%256;
    TxBuf[1] = (uchar)((g_fCarSpeedSet+100)/256);
    
    TxBuf[2] = (uchar)(g_fCarSpeedL+100)%256;
    TxBuf[3] = (uchar)((g_fCarSpeedL+100)/256);
    
    TxBuf[4] = (uchar)(g_fCarSpeedSet+100)%256;
    TxBuf[5] = (uchar)((g_fCarSpeedSet+100)/256);

    //TxBuf[6] = (uchar)(g_fCarSpeedR+100)%256;
    //TxBuf[7] = (uchar)((g_fCarSpeedR+100)/256);

    TxBuf[6] = (uchar)(g_fDirectionPwm+100)%256;
    TxBuf[7] = (uchar)((g_fDirectionPwm+100)/256);
    
    
    crc_temp=CRC_CHECK(TxBuf,8); //  0x4001244C DMA_Mode_Circular; DMA_InitStructure. DMA_InitTypeDef
    TxBuf[8]=crc_temp%256;
    TxBuf[9]=crc_temp/256;
    for(i=0;i<10;i++)
    {             
        //put_char(TxBuf[i],USART1);  //
        put_char(TxBuf[i],UART4);  //
    }

}
*/











