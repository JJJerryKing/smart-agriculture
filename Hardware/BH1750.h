#ifndef __BH1750_H
#define __BH1750_H

#include "stm32f10x.h"

// 根据ADDR引脚的连接选择正确的I2C地址
 #define BH1750_ADDRESS 0x23  // 如果ADDR接GND
//#define BH1750_ADDRESS 0x5C  // 如果ADDR接VCC

// BH1750指令集
#define POWER_DOWN 0x00
#define POWER_ON 0x01
#define RESET 0x07
#define CONTINUOUS_HIGH_RES_MODE 0x10
#define CONTINUOUS_HIGH_RES_MODE_2 0x11
#define CONTINUOUS_LOW_RES_MODE 0x13
#define ONE_TIME_HIGH_RES_MODE 0x20
#define ONE_TIME_HIGH_RES_MODE_2 0x21
#define ONE_TIME_LOW_RES_MODE 0x23

void BH1750_Init(void);
void BH1750_WriteCmd(uint8_t cmd);
uint16_t BH1750_ReadLightIntensity(void);

#endif
