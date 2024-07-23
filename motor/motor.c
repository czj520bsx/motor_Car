#include "stm32f10x.h"                  // Device header
#include "motor.h"

/*********************

驱动板     stm32

  VM    --  5V  

  VCC   --  3.3V

  GND   --  GND 

  AIN1  --  PB12

  AIN2  --  PB13

  BIN1  --  PB14

  BIN2  --  PB15

  PWMA  --  PB8  定时器4 通道3    右轮

  PWMB  --  PB9  定时器4 通道4    左轮

***********************/

/**
 * @brief 电机初始化代码
 *
 */
void Motor_Init(void)
{
	//开GPIOB TIM4时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	//引脚的GPIO模式设置
	//PB12~PB15 通用推挽输出
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//PB8, PB9 PWM输出 复用推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//初始化TIM4 100us左右
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 1000 -1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7 -1;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	//初始化输出通道
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//PWM模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性，确定有效电平
	TIM_OCInitStructure.TIM_Pulse = 0;//CCR初始值
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//输出使能
	
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);//初始化通道3
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);//初始化通道4
	
	//定时器使能函数
	TIM_Cmd(TIM4, ENABLE);

}

void Motor_SpeedSet(int L_S, int R_S)
{
	if(L_S > 999)
		L_S = 999;
	if(R_S > 999)
		R_S = 999;
	
	TIM_SetCompare3(TIM4, R_S);//修改CCR比较值，修改占空比
	TIM_SetCompare4(TIM4, L_S);

}	
//直行
void Motor_Go(void)
{
	//12低，13高，14低，15高
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_15);	
}
//后退
void Motor_Back(void)
{
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_15);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
}


//右转
void Motor_Right(void)
{

  GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	GPIO_SetBits(GPIOB, GPIO_Pin_15);

}
//左转
void Motor_Left(void)
{
	
  GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_15);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
}

