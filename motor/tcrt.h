#ifndef _TCRT_H
#define _TCRT_H

#include "stm32f10x.h"                  // Device header

#define R1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
#define M1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define L1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)

//#define TC 100*L1+10*M1+1*R1
void Tracing_Init(void);
void Track(u16 speed);

extern 	int Line;
#endif
