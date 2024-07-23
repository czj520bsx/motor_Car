#include "stm32f10x.h"                  // Device header
#include "delay.h"

static u8 fac_us;
static u16 fac_ms;

void delay_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//���õδ�ʱ��ʱ��Ƶ��Ϊ9MHz
	fac_us = SystemCoreClock/8000000;//ȷ��1us�£��������ƵĴ���
	fac_ms = 1000 * fac_us;
}

void delay_us(u16 nus)
{
#if 1
	u32 temp;
	SysTick->LOAD = nus * fac_us;//ȷ���������Ĵ���
	SysTick->VAL = 0x00;//��ռ�����
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;//��������
	do{
		temp = SysTick->CTRL;
	}while((temp&0x01) && !(temp&(1<<16)));//�ж�ʱ�䵽��
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;//�رռ�����
	SysTick->VAL = 0x00;//��ռ�����
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
