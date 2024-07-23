#include "stm32f10x.h"                  // Device header
#include "motor.h"

/*********************

������     stm32

  VM    --  5V  

  VCC   --  3.3V

  GND   --  GND 

  AIN1  --  PB12

  AIN2  --  PB13

  BIN1  --  PB14

  BIN2  --  PB15

  PWMA  --  PB8  ��ʱ��4 ͨ��3    ����

  PWMB  --  PB9  ��ʱ��4 ͨ��4    ����

***********************/

/**
 * @brief �����ʼ������
 *
 */
void Motor_Init(void)
{
	//��GPIOB TIM4ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	//���ŵ�GPIOģʽ����
	//PB12~PB15 ͨ���������
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//PB8, PB9 PWM��� �����������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//��ʼ��TIM4 100us����
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 1000 -1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7 -1;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	//��ʼ�����ͨ��
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//PWMģʽ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//������ԣ�ȷ����Ч��ƽ
	TIM_OCInitStructure.TIM_Pulse = 0;//CCR��ʼֵ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//���ʹ��
	
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);//��ʼ��ͨ��3
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);//��ʼ��ͨ��4
	
	//��ʱ��ʹ�ܺ���
	TIM_Cmd(TIM4, ENABLE);

}

void Motor_SpeedSet(int L_S, int R_S)
{
	if(L_S > 999)
		L_S = 999;
	if(R_S > 999)
		R_S = 999;
	
	TIM_SetCompare3(TIM4, R_S);//�޸�CCR�Ƚ�ֵ���޸�ռ�ձ�
	TIM_SetCompare4(TIM4, L_S);

}	
//ֱ��
void Motor_Go(void)
{
	//12�ͣ�13�ߣ�14�ͣ�15��
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_15);	
}
//����
void Motor_Back(void)
{
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_15);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
}


//��ת
void Motor_Right(void)
{

  GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_15);

}
//��ת
void Motor_Left(void)
{
	
  GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_15);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
}

