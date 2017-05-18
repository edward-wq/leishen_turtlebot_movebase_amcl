#ifndef __ASSIGNMENT1_H
#define __ASSIGNMENT1_H
#include "main.h"
/* 定义MPU6050内部地址*/
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)

#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)

#define	ACCEL_XOUT_H	0x3B//加速度计测量值寄存器地址
#define	ACCEL_XOUT_L	0x3C

#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E

#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
/********************/
#define	TEMP_OUT_H		0x41//温度测量值寄存器地址
#define	TEMP_OUT_L		0x42
/*********************/
#define	GYRO_XOUT_H		0x43//陀螺仪测量值寄存器地址
#define	GYRO_XOUT_L		0x44
	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46

#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
/**********************/
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		0x75	//IIC地址寄存器(默认数值0x68，只读)

#define	MPU_ADRESS 		0xD0   //IIC写入时的地址字节数据，+1为读取
#define I2C_Speed 		400000//IIC通讯速度400khz

extern float Angle;         //小车最终倾斜角度
extern short int Gyro_x;        //Y轴陀螺仪数据暂存
extern short int Gyro_y; 
extern short int Gyro_z; 
extern float Angle_az;	     //z轴加速度值暂存
extern float Angle_ay;	     //z轴加速度值暂存
extern float Angle_qingxie;	     //机器人倾斜角值暂存
extern short int Accel_x;
extern short int Accel_y;
extern short int Accel_z;

void I2C_MPU6050_Init(void);//重力传感器接口初始化
void InitMPU6050(void);     //初始化MPU6050
//void assignment1(void);//得出所需要的pwm
void Angle_Calcu(void);//角度计算
u16 GYRO_Data_Y(uint8_t YOUT_H);//y轴 陀螺仪
extern long int g_lnMmaOffset;
void Yijielvbo(float angle_m, float gyro_m);
extern float g_fGyroTemp;
#endif /* _ASSIGNMENT1_H */

