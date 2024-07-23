#include "tim.h"
#include "stm32f10x.h"                  // Device header
#include "stdio.h"


/**
 * @brief 定时器2的初始化
 * @note  定时时间1s psc= arr=
 * @param void
 * @return void
 */
void Tim2_Init(void)
{
	//打开TIM2的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//TIM2的初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10000;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	//允许定时器能够产生更新中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	//NVIC设置
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
	
	//TIM2的使能
	TIM_Cmd(TIM2, ENABLE);
}

//编写中断处理函数
void TIM2_IRQHandler(void)
{
	//判断中断源
	if(SET == TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		//清除中断标志位
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
		//你想做的事
		
	}
}
