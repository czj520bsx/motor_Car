#include "stm32f10x.h"                  // Device header
#include "light.h"

/**
 * @brief ������������ʼ������
 * @note  PA5
 * @param void
 * @return void
 */
void Light_Init(void)
{
	//��ADC1 GPIOA��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
	
	//����PA5������ģʽ -- ģ������
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//����ADC1��ʱ��Ƶ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//12M 72/6
	
	//��ʼ��ADC1
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //�ر�����ת��������ת��
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�����Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//��ʹ���ⲿ�������������
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//�����ڶ���ģʽ
	ADC_InitStructure.ADC_NbrOfChannel = 1;//��Ҫת����ͨ������
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//�ر�ɨ��ģʽ
	ADC_Init(ADC1, &ADC_InitStructure);
	
	//ADCʹ��
	ADC_Cmd(ADC1, ENABLE);
	
	//��λУ׼����У׼(ע�⣬Ҫ��ִ��cmd����У׼)
	ADC_ResetCalibration(ADC1);
	while(RESET != ADC_GetResetCalibrationStatus(ADC1));
	
	ADC_StartCalibration(ADC1);
	while(RESET != ADC_GetCalibrationStatus(ADC1));

}

/**
 * @brief ��ȡ������������ֵ
 * @note  PA5
 * @param *light ������ݵı����ĵ�ַ
 * @return void
 */
void Light_Get(int *light)
{
	//����ͨ����ת��˳�򣬲�������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_55Cycles5);
	
	//�����������
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	//�ȴ�ת�����
	while(SET != ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
	
	//ȡ��ת�����
	u16 lig = ADC_GetConversionValue(ADC1);
	
	*light = (100 - lig/41);
	
}
