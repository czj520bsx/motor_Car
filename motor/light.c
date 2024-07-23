#include "stm32f10x.h"                  // Device header
#include "light.h"

/**
 * @brief 光敏传感器初始化函数
 * @note  PA5
 * @param void
 * @return void
 */
void Light_Init(void)
{
	//打开ADC1 GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
	
	//设置PA5的引脚模式 -- 模拟输入
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//设置ADC1的时钟频率
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//12M 72/6
	
	//初始化ADC1
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //关闭连续转换，单次转换
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//数据右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//不使用外部触发，软件触发
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//工作在独立模式
	ADC_InitStructure.ADC_NbrOfChannel = 1;//需要转换的通道数量
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//关闭扫描模式
	ADC_Init(ADC1, &ADC_InitStructure);
	
	//ADC使能
	ADC_Cmd(ADC1, ENABLE);
	
	//复位校准，打开校准(注意，要先执行cmd再做校准)
	ADC_ResetCalibration(ADC1);
	while(RESET != ADC_GetResetCalibrationStatus(ADC1));
	
	ADC_StartCalibration(ADC1);
	while(RESET != ADC_GetCalibrationStatus(ADC1));

}

/**
 * @brief 获取光敏传感器的值
 * @note  PA5
 * @param *light 存放数据的变量的地址
 * @return void
 */
void Light_Get(int *light)
{
	//设置通道的转换顺序，采样周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_55Cycles5);
	
	//软件触发采样
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	//等待转换完成
	while(SET != ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
	
	//取出转换结果
	u16 lig = ADC_GetConversionValue(ADC1);
	
	*light = (100 - lig/41);
	
}
