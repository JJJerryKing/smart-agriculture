#ifndef __SOIL_HUMI_H
#define __SOIL_HUMI_H 
 
#define gpio_readA  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)  //��ȡGPIOA��P0�ڵ�ƽ��0/1��
 
void soil_humi_Init(void);         //��ʱ��ʼ������
int Gpio_read(void);        //��ȡA0��
uint16_t Get_soilhumi(void);
 
#endif
