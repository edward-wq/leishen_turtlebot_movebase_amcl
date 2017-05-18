#ifndef __ASSIGNMENT4_H
#define __ASSIGNMENT4_H
#include "main.h"
void BalanceControlOut(void);
void  MotorControl(void);
void SpeedControl(void);
void SpeedControlOut(void);
void DirControl(void);
void DirControlOut(void);
extern float g_fDirectionPwm;
extern float g_fDirectionPwm_old;
extern float g_fDirectionValueNew ;
extern float g_fDirectionValueOld;
extern uchar MotorDeadValue;
extern float g_fCarSpeedSet;
extern int Spanangle_old;

extern uchar Encoder1Flag;
extern uchar Encoder2Flag;

extern int pwmleft_temp;
extern int pwmright_temp;

#ifdef BALANCE
extern float g_fCarSpeed;
extern float g_fSpeed_P;
extern float g_fSpeed_I;
extern float g_fSpeed_D;
extern float g_fBlancePwm;
extern float g_fBlance_P ;
extern float g_fBlance_D ;
extern float g_fSpeedPwm;
#else
extern float g_fSpeedPwmL;
extern float g_fSpeed_PL;
extern float g_fSpeed_IL;
extern float g_fSpeed_DL;
extern float g_fCarSpeedL;
extern float g_fCarSpeedSetL;
extern float g_fCarSpeedSetOldL;
extern float g_fCarSpeedSetLTemp;
extern float g_fSpeedIntegralL;
extern int   g_iSpeedControlValueNewL;

extern float g_fSpeedPwmR;
extern float g_fSpeed_PR;
extern float g_fSpeed_IR;
extern float g_fSpeed_DR;
extern float g_fCarSpeedR;
extern float g_fCarSpeedSetR;
extern float g_fCarSpeedSetOldR;
extern float g_fCarSpeedSetRTemp;
extern float g_fSpeedIntegralR;
extern int   g_iSpeedControlValueNewR;

extern float g_fCarSpeedSet_temp;

extern int g_iStep1PlanThres;
extern uint g_uiStep1LowSpeed;
extern uint g_uiStep1HighSpeed;

extern int g_iStep2PlanThres;
extern uint g_uiStep2LowSpeed;
extern uint g_uiStep2HighSpeed;

#endif

void Step1SpeedPlan(int delt) ;
void Step2SpeedPlan(int delt);
int Step1PresAngle(void);
int Step2PresAngle(void);
uint32_t Fdc_ReadCh1(void);
uint32_t Fdc_ReadCh2(void);
uint32_t Fdc_ReadCh3(void);
uint32_t Fdc_ReadCh4(void);
void PIDParaSet(uchar i);

void Updata_Encoder_Data(void);

#endif //__ASSIGNMENT4_H







