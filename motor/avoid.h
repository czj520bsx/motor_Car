#ifndef __AVOID_H
#define __AVOID_H
 
#include "stm32f10x.h"
#include "delay.h"
void Avoid_init(void);
uint32_t Get_Distance(void);
void Avoid(u16 speed);
#endif
