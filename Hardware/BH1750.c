#include "BH1750.h"
#include "MyI2C.h"
#include "Delay.h"

void BH1750_Init(void) {
    MyI2C_Init(); // ��ʼ�����I2C
    BH1750_WriteCmd(POWER_ON); // �򿪵�Դ
    BH1750_WriteCmd(RESET); // ���ô�����
    BH1750_WriteCmd(CONTINUOUS_HIGH_RES_MODE); // ���������߷ֱ���ģʽ
}

void BH1750_WriteCmd(uint8_t cmd) {
    MyI2C_Start(); // ����I2Cͨ��
    MyI2C_SendByte(BH1750_ADDRESS << 1); // �����豸��ַ��дλ
    MyI2C_ReceiveAck(); // ����Ӧ��
    MyI2C_SendByte(cmd); // ��������
    MyI2C_ReceiveAck(); // ����Ӧ��
    MyI2C_Stop(); // ֹͣI2Cͨ��
}

uint16_t BH1750_ReadLightIntensity(void) {
    uint16_t value = 0;

    MyI2C_Start(); // ����I2Cͨ��
    MyI2C_SendByte(BH1750_ADDRESS << 1 | 0x01); // �����豸��ַ�Ͷ�λ
    MyI2C_ReceiveAck(); // ����Ӧ��

    value = MyI2C_ReceiveByte(); // ���ո�8λ����
    MyI2C_SendAck(0); // ����Ӧ��
    value = (value << 8) | MyI2C_ReceiveByte(); // ���յ�8λ����
    MyI2C_SendAck(1); // ���ͷ�Ӧ��

    MyI2C_Stop(); // ֹͣI2Cͨ��

    return value; // ���ض�ȡ�Ĺ�ǿ����
}
