#include "stm32f10x.h"
#include "delay.h"

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable the GPIO  Clock */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 						 		
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //�������
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOC , GPIO_Pin_13);   //��ʼ״̬��Ϩ��ָʾ��
}

void IO_control(void)
{
	GPIO_SetBits(GPIOC , GPIO_Pin_13);   //�պ�
	Delay_ms(5000); 
	GPIO_ResetBits(GPIOC , GPIO_Pin_13); //�ر�
	Delay_ms(5000); 
}

extern _Bool spray_status;

void spray_ON(void){
	GPIO_SetBits(GPIOC , GPIO_Pin_13);   //�պ�
	spray_status=1;
}

void spray_OFF(void){
	GPIO_ResetBits(GPIOC , GPIO_Pin_13); //�ر�
	spray_status=0;
}