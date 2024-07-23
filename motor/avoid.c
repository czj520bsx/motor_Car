#include "stm32f10x.h"  
  
#include "delay.h"  
#include "usart.h"
#include "motor.h"  
#include "stdio.h"
#include "avoid.h"  
void Avoid_init(void)  
{  
    GPIO_InitTypeDef GPIO_InitStructure;  
  
    // 初始化GPIOA12（Echo）  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; // 上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
  
    // 初始化GPIOA11（Trig）  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
}  
  
uint32_t Get_Distance(void)  
{  
    uint32_t  distance;
		u16 count = 0; 
    GPIO_SetBits(GPIOA, GPIO_Pin_11); // 发送10us的高电平触发信号  
    delay_us(15);                   // 延时10us  
    GPIO_ResetBits(GPIOA, GPIO_Pin_11); // 发送低电平信号  
  
    // 读取Echo引脚返回的高电平时间  
    while (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)); // 等待上升沿  
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12))
		{
			delay_us(8);
			count++;
		}
  
    // 计算距离（单位：厘米）
    distance = count*3/20; 
  
    return distance;  
}  
  
void Avoid(u16 speed)  
{  
    // 配置GPIO  
        uint32_t distance = Get_Distance(); // 获取距离  
				Serial_SendNumber(distance);  
        if (distance < 20) // 如果距离小于20厘米  
        {  
            Motor_Back(); // 后退  
            Motor_SpeedSet(600, speed); 
            delay_ms(500); // 等待一段时间  
            Motor_Go(); // 前进  
            Motor_SpeedSet(speed, speed); // 设置电机速度  
        }  
        else  
        {  
            Motor_Go(); // 直接前进  
            Motor_SpeedSet(speed, speed); // 设置电机速度  
        }  
}
