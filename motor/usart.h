#ifndef __USART_H//防止头文件被重复的包含引用
#define __USART_H

#include "stm32f10x.h"                  // Device header

void	Usart1_Init(int baud);
void Usart1_Send_Byte(u8 data);
void Usart1_Send_Str(char* str, int len);
void	Usart2_Init(int baud);
void Usart2_Send_Byte(u8 data);
void Usart2_Send_Str(char* str, int len);
extern int global_flag_recv;
extern u8 global_recv_buff[6];

uint32_t Serial_Pow(uint32_t X, uint32_t Y);
extern void Serial_SendNumber(uint32_t Number);

void Usart3_Init(int baud);
void USART3_SendByte(uint8_t  Data);
void Uart3_K210_SendCMD1(int dat1, int dat2);
void Uart3_K210_SendCmd(int len);

#endif
