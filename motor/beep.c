#include "stm32f10x.h"                  // Device header
#include "beep.h"

//PA6
void Beep_Init(void)
{
		//打开TIM3的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//TIM2的初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 1000;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 500;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	
	//TIM3的使能
	TIM_Cmd(TIM3, DISABLE);

}
void Beep_On(void)
{
	TIM_Cmd(TIM3, ENABLE);
}
void Beep_Off(void)
{
	TIM_Cmd(TIM3, DISABLE);
}
