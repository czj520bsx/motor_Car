#include "tim.h"
#include "stm32f10x.h"                  // Device header
#include "stdio.h"


/**
 * @brief ��ʱ��2�ĳ�ʼ��
 * @note  ��ʱʱ��1s psc= arr=
 * @param void
 * @return void
 */
void Tim2_Init(void)
{
	//��TIM2��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//TIM2�ĳ�ʼ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10000;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	//����ʱ���ܹ����������ж�
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	//NVIC����
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
	
	//TIM2��ʹ��
	TIM_Cmd(TIM2, ENABLE);
}

//��д�жϴ�����
void TIM2_IRQHandler(void)
{
	//�ж��ж�Դ
	if(SET == TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		//����жϱ�־λ
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
		//����������
		
	}
}
