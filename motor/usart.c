#include "usart.h"
#include "stm32f10x.h"                  // Device header
#include "stdio.h"

//重写fputc，实现printf函数的重定向
int fputc(int ch, FILE* file)
{
	//使用自己封装的串口发送函数
	Usart2_Send_Byte(ch);
	return ch;
}
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
 GPIO_Init(GPIOC, &GPIO_InitStructure);				
 
  
}
void	Usart1_Init(int baud)
{
	//打开GPIOA，USART1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_USART1, ENABLE);

	//设置引脚GPIO模式
	//A9 -- TX -- 复用推挽输出
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//A10 -- RX -- 浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//初始化USART1
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = baud; //波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8位数据位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无校验
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//1位停止位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//发送接收使能
	USART_Init(USART1, &USART_InitStructure);
	
	//允许串口能够产生中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能接收中断
	
	//NVIC中断向量控制器初始化
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//通道使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//响应优先级
	NVIC_Init(&NVIC_InitStructure);
	
	//USART1的使能，打开串口1
	USART_Cmd(USART1, ENABLE);
}

void Usart2_Init(int baud)
{
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;  // TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;  // RX
    GPIO_Init(GPIOA, &GPIO_InitStructure);

   
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);

    
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);


    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);


    USART_Cmd(USART2, ENABLE);
}
void Usart3_Init(int baud)
{
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使用GPIOB时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); // 使用USART3时钟

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  // TX
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;  // RX
    GPIO_Init(GPIOB, &GPIO_InitStructure);

   
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);

    
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);


    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);


    USART_Cmd(USART3, ENABLE);
}
int global_flag_recv = 0;
u8 global_recv_buff[6] = "";


void USART2_IRQHandler(void)
{
    static int flag_head = 0, i = 0;

  
    if (SET == USART_GetITStatus(USART2, USART_IT_RXNE))
    {
        if (0 == global_flag_recv)
        {
            uint8_t recvdata = USART_ReceiveData(USART2);

         
            if ((0 == flag_head) && (0xAA == recvdata))
            {
                global_recv_buff[0] = recvdata;
                flag_head = 1;
                i = 0;
            }
            else if ((1 == flag_head) && (i < 5))
            {
                i++;
                global_recv_buff[i] = recvdata;
                if (5 == i)
                {
                    // Check for the packet footer
                    if (0xBB == recvdata)
                    {
                        global_flag_recv = 1;
                    }
                    flag_head = 0;
                }
            }
        }
        else
        {
          
            USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        }
    }
}

void Usart1_Send_Byte(u8 data)
{
	USART_SendData(USART1, data);//发送一个字节
	while(SET != USART_GetFlagStatus(USART1, USART_FLAG_TXE));//等待发送完成
}

void Usart1_Send_Str(char* str, int len)
{
	while(len)
	{
		Usart1_Send_Byte(*str);
		str++;
		len--;
	}
}
void Usart2_Send_Byte(u8 data)
{
	USART_SendData(USART2, data);//发送一个字节
	while(SET != USART_GetFlagStatus(USART2, USART_FLAG_TXE));//等待发送完成
}

void Usart2_Send_Str(char* str, int len)
{
	while(len)
	{
		Usart2_Send_Byte(*str);
		str++;
		len--;
	}
}
u8 USART3_RX_STA = 0;     //串口3接收状态标记
u8 USART3_RX_CMD;

void USART3_IRQHandler(void)                           	 
{
  
  
    u8 Res = 0;

    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  
    {
        Res = USART_ReceiveData(USART3);	               
        USART3_RX_CMD = Res;                               
        USART3_RX_STA = 1;	
        
    }
}

void USART3_SendByte(uint8_t  Data)                                 //串口发送一个字节；字节 (byte)    1byte=8bit
{
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);    //USART_FLAG_TXE发送寄存器空

    USART_SendData(USART3, Data);                                   //从串口2发送传入的数据

    while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	    //USART_FLAG_TC发送完成标志
}
static int Send_buf[10] = {0} ;
void Uart3_K210_SendCmd(int len)
{
  int i = 0 ;

    USART3_SendByte(0xB1);       //起始
    USART3_SendByte(0x1B);

    for(i = 0; i < len; i++)     //数据
    {
        USART3_SendByte(Send_buf[i]);   //len 为8 ；依次将Send_buf[0]、Send_buf[1]~Send_buf[8]  发送出来
    }

}
void Uart3_K210_SendCMD1(int dat1, int dat2)
{
    Send_buf[0] = (int)(dat1);         //datal
    Send_buf[1] = (int)(dat2);         //data2
    Uart3_K210_SendCmd(2);            //发送此帧数据
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;	//设置结果初值为1
	while (Y --)			//执行Y次
	{
		Result *= X;		//将X累乘到结果
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number)
{
	while(Number){
		Usart2_Send_Byte((Number%10) + 48);
		Number /= 10;
	}
}
