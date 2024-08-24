#include "stm32f10x.h"
#include "delay.h"

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable the GPIO  Clock */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 						 		
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOC , GPIO_Pin_13);   //初始状态，熄灭指示灯
}

void IO_control(void)
{
	GPIO_SetBits(GPIOC , GPIO_Pin_13);   //闭合
	Delay_ms(5000); 
	GPIO_ResetBits(GPIOC , GPIO_Pin_13); //关闭
	Delay_ms(5000); 
}

extern _Bool spray_status;

void spray_ON(void){
	GPIO_SetBits(GPIOC , GPIO_Pin_13);   //闭合
	spray_status=1;
}

void spray_OFF(void){
	GPIO_ResetBits(GPIOC , GPIO_Pin_13); //关闭
	spray_status=0;
}