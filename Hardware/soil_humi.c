#include "stm32f10x.h"
#include "delay.h"
#include "soil_humi.h"
#include "adc.h"
 
void soil_humi_Init(void)
{    	 
	Adc_Init();
	GPIO_InitTypeDef GPIO_InitStructure;                     //����һ������GPIO�ı���
	
	
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);   //ʹ��GPIOA�˿�ʱ��
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;       //����PA0
	//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   		   //�������룬Ĭ��״̬�ǵ͵�ƽ
	//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   		   //�������룬Ĭ��״̬�Ǹߵ�ƽ 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //��������
	 GPIO_Init(GPIOA, &GPIO_InitStructure);            		 //����PA
	
}
 
int Gpio_read(void)
{
	if(gpio_readA == 1)
	{ 
		Delay_ms(100);
		return 1;
	}
	return 0;
}

uint16_t Get_soilhumi(void){
	
    float H_arg = Get_Adc_Average(1,20);
    uint16_t data = (4095 - H_arg) / 3292 * 100;
	return data;
}