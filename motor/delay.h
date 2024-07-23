#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"                  // Device header

void delay_init(void);
void delay_us(u16 nus);
void delay_ms(u16 nms);

#endif
