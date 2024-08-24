#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "dht11.h"
#include "BH1750.h"
#include "soil_humi.h"
#include "usart.h"
#include "esp8266.h"
#include "onenet.h"
#include "Motor.h"
#include "key.h"
#include "Relay.h"
#include "spray.h"
//C库
#include <string.h>

#define ESP8266_ONENET_INFO		"AT+CIPSTART=\"TCP\",\"mqtts.heclouds.com\",1883\r\n"

uint8_t KeyNum;		//定义用于接收按键键码的变量
int flag;			//事件读取传感器数据

void display1(void);
void Timer3_Init(void);

int main(void)
{	
//	IO_control();
	unsigned short timeCount = 0;	//发送间隔变量
	unsigned char *dataPtr = NULL;
	
	//硬件初始化
	Usart1_Init(115200);
	Timer3_Init();
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	DHT11_Init();       //DHT11初始化
	BH1750_Init();      //BH1750初始化
	soil_humi_Init();   //土壤湿度传感器初始化
	ESP8266_Init();		//wifi模块初始化
	Motor_Init();		//直流电机初始化
	Relay_Init();//水泵初始化
	GPIO_Configuration();//喷雾装置初始化

	
	
	
	//UsartPrintf(USART_DEBUG, "Connect MQTTs Server...\r\n");
	OLED_Clear(); OLED_ShowString(1,1,"Connect MQTT...");
	while(ESP8266_SendCmd(ESP8266_ONENET_INFO, "CONNECT"))
	Delay_ms(500);
//	UsartPrintf(USART_DEBUG, "Connect MQTT Server Success\r\n");
	OLED_ShowString(2,1,"Success"); Delay_ms(500);
	
	while(OneNet_DevLink());			//接入OneNET
	Delay_ms(1000);
	
	OneNET_Subscribe();
//	
	display1();
//	
	extern	u8 humi;
	extern	u8 temp;
	extern uint16_t light;
	extern uint16_t soil_humi;
	extern _Bool motor_status;
	extern _Bool spray_status;
	extern _Bool pump_status;
	
	while (1)
	{	
		if(flag==1){
			for(int j=0;j<4;j++){
				DHT11_Read_Data(&humi, &temp);
			}
			light=BH1750_ReadLightIntensity()/1.2;// 将BH1750的返回值转换为实际的lux值
			//float lightInLux = light / 1.2;// 将BH1750的返回值转换为实际的lux值
			soil_humi=Get_soilhumi();
			//显示环境温度数据
			OLED_ShowNum(1, 10, temp, 2);
		
			//显示环境湿度数据
			OLED_ShowNum(2, 10, humi, 2);
			
			//显示环境光照数据
			OLED_ShowNum(3, 6, light, 5);
			
			//显示土壤湿度数据
			OLED_ShowNum(4,10,soil_humi,2);
			
			OneNet_SendData();									//发送数据
			ESP8266_Clear();
			
			flag=0;
		}
		
//		if(++timeCount >= 20)									//发送间隔5s
//		{
////			DHT11_Read_Data(&humi,&temp);
////			light=BH1750_ReadLightIntensity()/1.2;// 将BH1750的返回值转换为实际的lux值
////			soil_humi=Get_soilhumi();
//			
////			UsartPrintf(USART_DEBUG, "OneNet_SendData\r\n");
//			OneNet_SendData();									//发送数据
//			
//			timeCount = 0;
//			ESP8266_Clear();
//		}
		
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL )
			OneNet_RevPro(dataPtr);
//		
		
	}
}

void display1(void){
	//OLED显示
	//显示“环境温度：  C”
	OLED_ShowChinese(1, 1, 13);
	OLED_ShowChinese(1, 2, 14);
	OLED_ShowChinese(1, 3, 8);
	OLED_ShowChinese(1, 4, 9);	
	OLED_ShowChar(1, 9, ':');
	OLED_ShowChar(1, 12, 'C');
	
	//显示“环境湿度：  %”
	OLED_ShowChinese(2, 1, 13);
	OLED_ShowChinese(2, 2, 14);
	OLED_ShowChinese(2, 3, 10);
	OLED_ShowChinese(2, 4, 9);	
	OLED_ShowChar(2, 9, ':');
	OLED_ShowChar(2, 12, '%');		
	
	//显示“光照：  lx”
	OLED_ShowChinese(3, 1, 15);
	OLED_ShowChinese(3, 2, 16);
	OLED_ShowChar(3, 5, ':');
	OLED_ShowChar(3, 12, 'l');
	OLED_ShowChar(3, 13, 'u');
	OLED_ShowChar(3, 14, 'x');
	
	//显示“土壤湿度：  %”
	OLED_ShowChinese(4, 1, 11);
	OLED_ShowChinese(4, 2, 12);
	OLED_ShowChinese(4, 3, 10);
	OLED_ShowChinese(4, 4, 9);	
	OLED_ShowChar(4, 9, ':');
	OLED_ShowChar(4, 12, '%');	
}

void Timer3_Init(void)
{
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);			//开启TIM2的时钟
	
	/*配置时钟源*/
	TIM_InternalClockConfig(TIM3);		//选择TIM2为内部时钟，若不调用此函数，TIM默认也为内部时钟
	
	/*时基单元初始化*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//定义结构体变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 15000 - 1;				//计数周期，即ARR的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;				//预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;			//重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);				//将结构体变量交给TIM_TimeBaseInit，配置TIM2的时基单元	
	
	/*中断输出配置*/
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);						//清除定时器更新标志位
																//TIM_TimeBaseInit函数末尾，手动产生了更新事件
																//若不清除此标志位，则开启中断后，会立刻进入一次中断
																//如果不介意此问题，则不清除此标志位也可
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);					//开启TIM2的更新中断
	
	/*NVIC中断分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//配置NVIC为分组2
																//即抢占优先级范围：0~3，响应优先级范围：0~3
																//此分组配置在整个工程中仅需调用一次
																//若有多个中断，可以把此代码放在main函数内，while循环之前
																//若调用多次配置分组的代码，则后执行的配置会覆盖先执行的配置
	
	/*NVIC配置*/
	NVIC_InitTypeDef NVIC_InitStructure;						//定义结构体变量
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;				//选择配置NVIC的TIM2线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//指定NVIC线路的抢占优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);								//将结构体变量交给NVIC_Init，配置NVIC外设
	
	/*TIM使能*/
	TIM_Cmd(TIM3, ENABLE);			//使能TIM2，定时器开始运行
}

void TIM3_IRQHandler(void) {
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
        // 清除中断标志
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        // 在这里添加你的中断处理代码
		flag=1;
    }
}