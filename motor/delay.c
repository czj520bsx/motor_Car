#include "stm32f10x.h"                  // Device header
#include "delay.h"

static u8 fac_us;
static u16 fac_ms;

void delay_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//配置滴答定时器时钟频率为9MHz
	fac_us = SystemCoreClock/8000000;//确定1us下，计数器计的次数
	fac_ms = 1000 * fac_us;
}

void delay_us(u16 nus)
{
#if 1
	u32 temp;
	SysTick->LOAD = nus * fac_us;//确定计数器的次数
	SysTick->VAL = 0x00;//清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;//开启计数
	do{
		temp = SysTick->CTRL;
	}while((temp&0x01) && !(temp&(1<<16)));//判断时间到达
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;//关闭计数器
	SysTick->VAL = 0x00;//清空计数器
#else 
	int i = 4;
	while(nus--)
		while(i--);
	
#endif
}
void delay_ms(u16 nms)
{
#if 1
	u32 temp;
	SysTick->LOAD = nms * fac_ms;
	SysTick->VAL = 0x00;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	do{
		temp = SysTick->CTRL;
	}while((temp&0x01) && !(temp&(1<<16)));
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL = 0x00;
#else
	int i = 1000;
	while(nms--)
	{
		while(i--)
			delay_us(1);
	}
	
#endif
}
