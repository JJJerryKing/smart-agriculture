#include "stm32f10x.h"    //������Ҫ��ͷ�ļ�
#include "delay.h"	      //������Ҫ��ͷ�ļ�
 
 
/*����������ʼ��ADC */									   
void Adc_Init(void)
{    
	GPIO_InitTypeDef      GPIO_InitStructure;                             //����һ������GPIO�ı���
	ADC_InitTypeDef       ADC_InitStructure;                              //����һ������ADC�ı���
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE );	              //ʹ��GPIOAͨ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );	              //ʹ��ADC1ͨ��ʱ��
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);                                      //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;        //׼������PA1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		                   //ģ����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			// ����IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);                                 //����PA5
    	
	ADC_DeInit(ADC1);                                                      //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	                   //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	                       //ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	                   //ģ��ת��������������ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	   //ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	               //ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	                               //˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);                                    //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
 
	ADC_Cmd(ADC1, ENABLE);	                                               //ʹ��ָ����ADC1	
	ADC_ResetCalibration(ADC1);	                                           //ʹ�ܸ�λУ׼  	 
	while(ADC_GetResetCalibrationStatus(ADC1));                     	   //�ȴ���λУ׼����	
	ADC_StartCalibration(ADC1);	                                           //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC1));	                               //�ȴ�У׼����
}
 
/*-------------------------------------------------*/
/*�����������ADC���                              */
/*��  ����ch: ͨ����                               */
/*-------------------------------------------------*/	

uint16_t Get_Adc(int ch)   
{	
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		                        //ʹ��ָ����ADC1�����ת����������	
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));                     //�ȴ�ת������
	return ADC_GetConversionValue(ADC1);	                            //�������һ��ADC1�������ת�����
}
/*-------------------------------------------------*/
/*��������ƽ�����ADC�������߾���                */
/*��  ����channel: ͨ����                               */
/*��  ����count: ƽ������                          */
/*-------------------------------------------------*/	

float Get_Adc_Average(int channel,int count)
{
	uint32_t sum_val=0;
	char t;
	
	for(t=0;t<count;t++)             //ѭ����ȡtimes��
	{
		sum_val+=Get_Adc(channel);       //������ֵ
		Delay_ms(5);                 //��ʱ
	}
	return sum_val/count;           //����ƽ��ֵ
} 