#include "relay.h"

extern _Bool pump_status;

void Relay_Init(void)
{
	//ø™∆ÙGPIOA ±÷”
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//≈‰÷√GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Relay1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Relay_PROT, &GPIO_InitStructure);
	
	GPIO_ResetBits(Relay_PROT, Relay1);
}

void Relay_ON(void)
{	
	GPIO_SetBits(Relay_PROT, Relay1);
	pump_status=1;
}

void Relay_OFF(void)
{
	GPIO_ResetBits(Relay_PROT, Relay1);
	pump_status=0;
}
