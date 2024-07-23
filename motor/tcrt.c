#include "TCRT.h"
#include "usart.h"
#include "motor.h"
#include "stm32f10x.h"  // Device header
#include "delay.h"

#include "stm32f10x.h"                  // Device header 
#include "motor.h"
#include "stdio.h"

#define left  GPIO_Pin_4              //定义左边的模块接A4
#define middle GPIO_Pin_5             //定义中间的模块接A5 
#define right  GPIO_Pin_1             //定义右边的模块接B1
 
//----------初始
void Tracing_Init(void)
{
	//结构体初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);              //开启外设时钟B
	GPIO_InitTypeDef GPIO_InitTypeStructure;
 
	GPIO_InitTypeStructure.GPIO_Mode=GPIO_Mode_IPU;                   //使用上拉输入模式
	GPIO_InitTypeStructure.GPIO_Pin=right ;               //绑定引脚
	GPIO_InitTypeStructure.GPIO_Speed=GPIO_Speed_10MHz;               //设置IO口速度
	GPIO_Init(GPIOB,&GPIO_InitTypeStructure);                         //绑定B通道
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);              //开启外设时钟A
	GPIO_InitTypeDef GPIO_InitTypeS;
 
	GPIO_InitTypeS.GPIO_Mode=GPIO_Mode_IPU;                   //使用上拉输入模式
	GPIO_InitTypeS.GPIO_Pin=middle|left ;               //绑定引脚
	GPIO_InitTypeS.GPIO_Speed=GPIO_Speed_10MHz;               //设置IO口速度
	GPIO_Init(GPIOA,&GPIO_InitTypeS);                         //绑定A通道
}
 
//----------通过识别黑白线来输入高低电平的部分-------- 
int Get_State(int choice)
{
	int get=0;                                           
	switch(choice)
	{
		case 1: get= GPIO_ReadInputDataBit(GPIOA,left);break;    //获取左边的电平
		case 2: get=GPIO_ReadInputDataBit(GPIOA,middle);break;   //获取中间的电平
		case 3: get=GPIO_ReadInputDataBit(GPIOB,right);break;    //获取右边的电平
	}
	return get;
}

int Line=0;
int start_flag=1;
int flag=0;

void Track(u16 speed)
{
    int state1 = Get_State(1);
    int state2 = Get_State(2);
    int state3 = Get_State(3);
    Motor_Go();
    if (Line == 0&&start_flag)
        {
					GPIO_SetBits(GPIOC,GPIO_Pin_13);
          Uart3_K210_SendCMD1(0x11, 0x00); 
          start_flag=0;
        }
    if (state1 == 0 && state2 == 1 && state3 == 0)
    {
        Motor_SpeedSet(speed, speed);
    }
    else if (state1 == 1 && state2 == 0 && state3 == 0)
    {
        Motor_SpeedSet(speed, 0);
    }
    else if (state1 == 0 && state2 == 0 && state3 == 1)
    {
        Motor_SpeedSet(0, speed);
    }
    else if (state1 == 0 && state2 == 1 && state3 == 1)
    {
        Motor_SpeedSet(0, speed);
    }
    else if (state1 == 0 && state2 == 0 && state3 == 0)
    {
        Motor_SpeedSet(speed, speed);
    }
    else if (state1 == 1 && state2 == 1 && state3 == 1)
    {
			/*Motor_SpeedSet(0, 0);
			if(Line < 4 && flag == 0)
			{
		     Line++;
				Uart3_K210_SendCMD1(0x11, 0x02);
				flag=1;
			}
			else if(Line >=4)
			{
        Line=0;			
			}
			delay_ms(5000);
			if(USART_GetFlagStatus(USART3,USART_FLAG_TC)== SET)
			{
			   Motor_SpeedSet(speed, speed);
				delay_ms(300);
			}*/
			delay_ms(10);
        Line++; 				
			Motor_SpeedSet(speed, speed);
    }
		if(Line)
		{
		Uart3_K210_SendCMD1(0x22, Line);
		}
}
/*void Track(void)
{
	
	
    if(Get_State(1)==1&&Get_State(2)==0&&Get_State(3)==1)
    {
            Motor_Go();
			Motor_SpeedSet(200, 200);
        	
    }	           
   
}*/
