#include "stm32f10x.h"
#include "delay.h"
#include "soil_humi.h"
#include "adc.h"
 
void soil_humi_Init(void)
{    	 
	Adc_Init();
	GPIO_InitTypeDef GPIO_InitStructure;                     //定义一个设置GPIO的变量
	
	
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);   //使能GPIOA端口时钟
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;       //设置PA0
	//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   		   //下拉输入，默认状态是低电平
	//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   		   //上拉输入，默认状态是高电平 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //浮空输入
	 GPIO_Init(GPIOA, &GPIO_InitStructure);            		 //设置PA
	
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