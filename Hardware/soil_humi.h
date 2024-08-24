#ifndef __SOIL_HUMI_H
#define __SOIL_HUMI_H 
 
#define gpio_readA  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)  //读取GPIOA的P0口电平（0/1）
 
void soil_humi_Init(void);         //延时初始化函数
int Gpio_read(void);        //读取A0口
uint16_t Get_soilhumi(void);
 
#endif
