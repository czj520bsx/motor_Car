#include "stm32f10x.h"  
  
#include "delay.h"  
#include "usart.h"
#include "motor.h"  
#include "stdio.h"
#include "avoid.h"  
void Avoid_init(void)  
{  
    GPIO_InitTypeDef GPIO_InitStructure;  
  
    // ��ʼ��GPIOA12��Echo��  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; // ��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
  
    // ��ʼ��GPIOA11��Trig��  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // �������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
}  
  
uint32_t Get_Distance(void)  
{  
    uint32_t  distance;
		u16 count = 0; 
    GPIO_SetBits(GPIOA, GPIO_Pin_11); // ����10us�ĸߵ�ƽ�����ź�  
    delay_us(15);                   // ��ʱ10us  
    GPIO_ResetBits(GPIOA, GPIO_Pin_11); // ���͵͵�ƽ�ź�  
  
    // ��ȡEcho���ŷ��صĸߵ�ƽʱ��  
    while (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)); // �ȴ�������  
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12))
		{
			delay_us(8);
			count++;
		}
  
    // ������루��λ�����ף�
    distance = count*3/20; 
  
    return distance;  
}  
  
void Avoid(u16 speed)  
{  
    // ����GPIO  
        uint32_t distance = Get_Distance(); // ��ȡ����  
				Serial_SendNumber(distance);  
        if (distance < 20) // �������С��20����  
        {  
            Motor_Back(); // ����  
            Motor_SpeedSet(600, speed); 
            delay_ms(500); // �ȴ�һ��ʱ��  
            Motor_Go(); // ǰ��  
            Motor_SpeedSet(speed, speed); // ���õ���ٶ�  
        }  
        else  
        {  
            Motor_Go(); // ֱ��ǰ��  
            Motor_SpeedSet(speed, speed); // ���õ���ٶ�  
        }  
}
