#ifndef __BSP_ULTRASONIC_H
#define __BSP_ULTRASONIC_H

#include "stm32f10x.h"
#include "bsp_delay.h"
#include "bsp_tim.h"


//hcsr04������ģ�飬Trig-->PB8,Echo-->PB6
#define TRIG_PIN     			GPIO_Pin_8
#define TRIG_PORT					GPIOB
#define TRIG_CLK_PORT   	RCC_APB2Periph_GPIOB

#define ECHO_PIN     			GPIO_Pin_6
#define ECHO_PORT					GPIOB
#define ECHO_CLK_PORT   	RCC_APB2Periph_GPIOB

// ���� trig ���ŵ�ƽ
#define TRIG_HIGH         GPIO_SetBits(TRIG_PORT, TRIG_PIN);
#define TRIG_LOW          GPIO_ResetBits(TRIG_PORT, TRIG_PIN);

// ��ȡ echo ���ŵ�ƽ
#define ECHO_READ         GPIO_ReadInputDataBit(ECHO_PORT, ECHO_PIN)
#define ECHO_LOW 					GPIO_ResetBits(ECHO_PORT, ECHO_PIN);  

void ULTRASONIC_Init(void);
float Get_Length(void);

#endif /*__BSP_ULTRASONIC_H*/
