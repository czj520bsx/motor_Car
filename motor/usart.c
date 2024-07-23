#include "usart.h"
#include "stm32f10x.h"                  // Device header
#include "stdio.h"

//��дfputc��ʵ��printf�������ض���
int fputc(int ch, FILE* file)
{
	//ʹ���Լ���װ�Ĵ��ڷ��ͺ���
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
	//��GPIOA��USART1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_USART1, ENABLE);

	//��������GPIOģʽ
	//A9 -- TX -- �����������
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//A10 -- RX -- ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//��ʼ��USART1
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = baud; //������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ����λ
	USART_InitStructure.USART_Parity = USART_Parity_No;//��У��
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//1λֹͣλ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//���ͽ���ʹ��
	USART_Init(USART1, &USART_InitStructure);
	
	//�������ܹ������ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�
	
	//NVIC�ж�������������ʼ��
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ͨ��ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//��Ӧ���ȼ�
	NVIC_Init(&NVIC_InitStructure);
	
	//USART1��ʹ�ܣ��򿪴���1
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
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // ʹ��GPIOBʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); // ʹ��USART3ʱ��

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
	USART_SendData(USART1, data);//����һ���ֽ�
	while(SET != USART_GetFlagStatus(USART1, USART_FLAG_TXE));//�ȴ��������
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
	USART_SendData(USART2, data);//����һ���ֽ�
	while(SET != USART_GetFlagStatus(USART2, USART_FLAG_TXE));//�ȴ��������
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
u8 USART3_RX_STA = 0;     //����3����״̬���
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

void USART3_SendByte(uint8_t  Data)                                 //���ڷ���һ���ֽڣ��ֽ� (byte)    1byte=8bit
{
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);    //USART_FLAG_TXE���ͼĴ�����

    USART_SendData(USART3, Data);                                   //�Ӵ���2���ʹ��������

    while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	    //USART_FLAG_TC������ɱ�־
}
static int Send_buf[10] = {0} ;
void Uart3_K210_SendCmd(int len)
{
  int i = 0 ;

    USART3_SendByte(0xB1);       //��ʼ
    USART3_SendByte(0x1B);

    for(i = 0; i < len; i++)     //����
    {
        USART3_SendByte(Send_buf[i]);   //len Ϊ8 �����ν�Send_buf[0]��Send_buf[1]~Send_buf[8]  ���ͳ���
    }

}
void Uart3_K210_SendCMD1(int dat1, int dat2)
{
    Send_buf[0] = (int)(dat1);         //datal
    Send_buf[1] = (int)(dat2);         //data2
    Uart3_K210_SendCmd(2);            //���ʹ�֡����
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;	//���ý����ֵΪ1
	while (Y --)			//ִ��Y��
	{
		Result *= X;		//��X�۳˵����
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
