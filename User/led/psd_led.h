#ifndef PSD_LED_H
#define PSD_LED_H

#include "stm32f10x.h"

#define LED2_PIN        GPIO_Pin_12
#define LED2_PORT		    GPIOB
#define LED2_RCC_PORT   RCC_APB2Periph_GPIOB
#define LED2_ON        GPIO_SetBits(LED2_PORT, LED2_PIN);
#define LED2_OFF         GPIO_ResetBits(LED2_PORT, LED2_PIN);
 
void LED_GPIO_Config(void);

#endif

