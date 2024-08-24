#include "BH1750.h"
#include "MyI2C.h"
#include "Delay.h"

void BH1750_Init(void) {
    MyI2C_Init(); // 初始化软件I2C
    BH1750_WriteCmd(POWER_ON); // 打开电源
    BH1750_WriteCmd(RESET); // 重置传感器
    BH1750_WriteCmd(CONTINUOUS_HIGH_RES_MODE); // 设置连续高分辨率模式
}

void BH1750_WriteCmd(uint8_t cmd) {
    MyI2C_Start(); // 启动I2C通信
    MyI2C_SendByte(BH1750_ADDRESS << 1); // 发送设备地址和写位
    MyI2C_ReceiveAck(); // 接收应答
    MyI2C_SendByte(cmd); // 发送命令
    MyI2C_ReceiveAck(); // 接收应答
    MyI2C_Stop(); // 停止I2C通信
}

uint16_t BH1750_ReadLightIntensity(void) {
    uint16_t value = 0;

    MyI2C_Start(); // 启动I2C通信
    MyI2C_SendByte(BH1750_ADDRESS << 1 | 0x01); // 发送设备地址和读位
    MyI2C_ReceiveAck(); // 接收应答

    value = MyI2C_ReceiveByte(); // 接收高8位数据
    MyI2C_SendAck(0); // 发送应答
    value = (value << 8) | MyI2C_ReceiveByte(); // 接收低8位数据
    MyI2C_SendAck(1); // 发送非应答

    MyI2C_Stop(); // 停止I2C通信

    return value; // 返回读取的光强数据
}
