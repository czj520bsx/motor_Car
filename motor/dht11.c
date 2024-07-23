#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "stdio.h"

/**
 * @brief DHT11 data引脚设置为输出
 * @note  PB1
 * @param void
 * @return void
 */
void DHT11_IO_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//通用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief DHT11初始化
 * @note  PB1
 * @param void
 * @return void
 */
void DHT11_IO_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


/**
 * @brief DHT11初始化
 * @note  PB1
 * @param void
 * @return void
 */
void DHT11_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//打开GPIOB时钟
	
	DHT11_IO_OUT();//设置为输出
	
	GPIO_SetBits(GPIOB, GPIO_Pin_1);//输出高电平
	delay_ms(10); //消抖
}


/**
 * @brief DHT11获取温湿度数据
 * @note  PB1
 * @param *hum 存放湿度数据的变量地址
 * @param *tem 存放温度数据的变量地址
 * @return void
 */
void DHT11_Get(int* hum, int* tem)
{
	u8 DHT11_Data[5] = "";
	int i = 0;
	
start:
	//发送起始信号
	DHT11_IO_OUT();
	GPIO_SetBits(GPIOB, GPIO_Pin_1);//输出高电平
	delay_ms(10);
	
	//18ms的低电平
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);//输出低电平
	delay_ms(18);
	
	//20~40us的高电平
	GPIO_SetBits(GPIOB, GPIO_Pin_1);
	delay_us(30);
	//切换为输入
	DHT11_IO_IN();
	delay_us(40);

	//等待响应信号
	if(RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
	{
		delay_us(20);
		while(RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1));//等待80us低电平结束
		delay_us(50);
		while(SET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1));//等待80us的高电平结束
	}else{
		goto start;
	}
	
	//接收数据 40个bit
	int num = 0;
	for(i=0; i<40; i++){
		num = 0;
		delay_us(10);
		while(RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1));//等待50us的低电平结束
		while(SET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)){
			delay_us(10);
			num++;
		}
		if(num > 5){
			//数据1
			DHT11_Data[i/8] |= (0x1 << (7 - i%8)); 
		}
	}
	//校验数据
	if(DHT11_Data[4] == DHT11_Data[0] + DHT11_Data[1] + DHT11_Data[2] + DHT11_Data[3])
	{
		//数据正确
		//回传数据
		*hum = DHT11_Data[0];
		*tem = DHT11_Data[2];
	}	
}
