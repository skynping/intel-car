#ifndef __BSP_DIGITAL_H
#define __BSP_DIGITAL_H

#include "stm32f10x.h"

/***********************本部分包含距离传感器，测速模块，黑白线识别模块***************************/

/*************测速 l:PB1,r:PB0****************/ 
#define SPEEDl_PIN     						GPIO_Pin_1
#define SPEEDr_PIN     						GPIO_Pin_0
#define SPEEDx_PORT								GPIOB
// 配置中断源IO脚
#define SPEEDx_CLK_PORT   				RCC_APB2Periph_GPIOB
#define SPEEDl_GPIO_PortSource    GPIO_PortSourceGPIOB
#define SPEEDl_GPIO_PinSource     GPIO_PinSource1
#define SPEEDr_GPIO_PortSource    GPIO_PortSourceGPIOB
#define SPEEDr_GPIO_PinSource     GPIO_PinSource0
// 配置中断
#define SPEEDl_LINE         			EXTI_Line1
#define SPEEDr_LINE         			EXTI_Line0
#define SPEEDx_LINE         			SPEEDl_LINE | SPEEDr_LINE
#define SPEEDl_EXTI1_IRQn    			EXTI1_IRQn
#define SPEEDl_EXTI1_IRQHandler   EXTI1_IRQHandler
#define SPEEDr_EXTI2_IRQn    			EXTI0_IRQn 
#define SPEEDr_EXTI2_IRQHandler   EXTI0_IRQHandler

/**************距离传感器 l:PA5,r:PA6*********************/ 
#define RANGEl_PIN     						GPIO_Pin_5
#define RANGEr_PIN     						GPIO_Pin_6
#define RANGEx_PORT								GPIOA
#define RANGEx_CLK_PORT   				RCC_APB2Periph_GPIOA
// 配置中断源IO脚
#define RANGEl_GPIO_PortSource    GPIO_PortSourceGPIOA
#define RANGEl_GPIO_PinSource     GPIO_PinSource5
#define RANGEr_GPIO_PortSource    GPIO_PortSourceGPIOA
#define RANGEr_GPIO_PinSource     GPIO_PinSource6
// 配置中断
#define RANGEl_LINE                EXTI_Line5
#define RANGEr_LINE                EXTI_Line6
#define RANGEx_LINE                RANGEl_LINE | RANGEr_LINE
#define RANGEx_EXTI9_5_IRQn        EXTI9_5_IRQn
#define RANGEx_EXTI9_5_IRQHandler  EXTI9_5_IRQHandler

/*****************黑白线识别 l:PA11,m:PA12,r:PA13********************/ 
#define MARKl_PIN     							GPIO_Pin_11
#define MARKm_PIN     							GPIO_Pin_12
#define MARKr_PIN     							GPIO_Pin_13
#define MARKx_PORT									GPIOA
#define MARKx_CLK_PORT   						RCC_APB2Periph_GPIOA
// 配置中断源IO脚
#define MARKl_GPIO_PortSource    		GPIO_PortSourceGPIOA
#define MARKl_GPIO_PinSource     		GPIO_PinSource11
#define MARKm_GPIO_PortSource    		GPIO_PortSourceGPIOA
#define MARKm_GPIO_PinSource     		GPIO_PinSource12
#define MARKr_GPIO_PortSource    		GPIO_PortSourceGPIOA
#define MARKr_GPIO_PinSource     		GPIO_PinSource13
// 配置中断
#define MARKl_LINE                 	EXTI_Line11
#define MARKm_LINE                 	EXTI_Line12
#define MARKr_LINE                 	EXTI_Line13
#define MARKx_LINE                 	MARKl_LINE | MARKm_LINE | MARKr_LINE
#define MARKx_EXTI15_10_IRQn       	EXTI15_10_IRQn
#define MARKx_EXTI15_10_IRQHandler  EXTI15_10_IRQHandler

void Digital_Init(void);

#endif /*__BSP_DIGITAL_H*/

