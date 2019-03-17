#include "bsp_ultrasonic.h"

// 超声波模块使用HC-SR04型号，5V供电

// 初始化配置
static void ULTRASONIC_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( TRIG_CLK_PORT | ECHO_CLK_PORT,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = TRIG_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // trig引脚设置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TRIG_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ECHO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // echo引脚设置为浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ECHO_PORT, &GPIO_InitStructure);
}


void ULTRASONIC_Init(void)
{
	ULTRASONIC_Config();
	TRIG_LOW;
	ECHO_LOW;
}

float Get_Length(void)
{
	uint16_t taken_time = 0; // 保存超声波单次往返花费的时间
	float length = 0; // 保存距离
	int i = 5; // 总共测量5次
	float sum_length = 0; // 五次总距离
	
	for(;i>0;i--)
	{
		
		// 开始采集数据，根本模块时序图操作如下
		TRIG_HIGH; // trig引脚输出高电平
		Delay_us(20); // 延迟 20us
		TRIG_LOW; // trig引脚输出低电平
		while(ECHO_READ == RESET); // 等待echo引脚由0变为1
		Open_TIM();
		while(ECHO_READ != RESET); // 等待echo引脚由1变为0
		Close_TIM();
		taken_time = Get_Timer(); // 获取时间，分辨率为1us
		length = ((float)taken_time/58.0);	 // 计算距离，单位cm
		sum_length += length; //计算总距离
	}
	
	
	return sum_length/5.0; // 返回平均值
}

