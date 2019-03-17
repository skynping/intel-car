#include "psd_led.h"

void LED_GPIO_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(LED2_RCC_PORT,ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin = LED2_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED2_PORT,&GPIO_InitStructure);
	
	LED2_OFF
}

