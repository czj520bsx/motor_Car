#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "stdio.h"

/**
 * @brief DHT11 data��������Ϊ���
 * @note  PB1
 * @param void
 * @return void
 */
void DHT11_IO_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//ͨ���������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief DHT11��ʼ��
 * @note  PB1
 * @param void
 * @return void
 */
void DHT11_IO_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


/**
 * @brief DHT11��ʼ��
 * @note  PB1
 * @param void
 * @return void
 */
void DHT11_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//��GPIOBʱ��
	
	DHT11_IO_OUT();//����Ϊ���
	
	GPIO_SetBits(GPIOB, GPIO_Pin_1);//����ߵ�ƽ
	delay_ms(10); //����
}


/**
 * @brief DHT11��ȡ��ʪ������
 * @note  PB1
 * @param *hum ���ʪ�����ݵı�����ַ
 * @param *tem ����¶����ݵı�����ַ
 * @return void
 */
void DHT11_Get(int* hum, int* tem)
{
	u8 DHT11_Data[5] = "";
	int i = 0;
	
start:
	//������ʼ�ź�
	DHT11_IO_OUT();
	GPIO_SetBits(GPIOB, GPIO_Pin_1);//����ߵ�ƽ
	delay_ms(10);
	
	//18ms�ĵ͵�ƽ
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);//����͵�ƽ
	delay_ms(18);
	
	//20~40us�ĸߵ�ƽ
	GPIO_SetBits(GPIOB, GPIO_Pin_1);
	delay_us(30);
	//�л�Ϊ����
	DHT11_IO_IN();
	delay_us(40);

	//�ȴ���Ӧ�ź�
	if(RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
	{
		delay_us(20);
		while(RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1));//�ȴ�80us�͵�ƽ����
		delay_us(50);
		while(SET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1));//�ȴ�80us�ĸߵ�ƽ����
	}else{
		goto start;
	}
	
	//�������� 40��bit
	int num = 0;
	for(i=0; i<40; i++){
		num = 0;
		delay_us(10);
		while(RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1));//�ȴ�50us�ĵ͵�ƽ����
		while(SET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)){
			delay_us(10);
			num++;
		}
		if(num > 5){
			//����1
			DHT11_Data[i/8] |= (0x1 << (7 - i%8)); 
		}
	}
	//У������
	if(DHT11_Data[4] == DHT11_Data[0] + DHT11_Data[1] + DHT11_Data[2] + DHT11_Data[3])
	{
		//������ȷ
		//�ش�����
		*hum = DHT11_Data[0];
		*tem = DHT11_Data[2];
	}	
}
