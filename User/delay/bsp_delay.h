#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H

#include "stm32f10x.h"
#include "core_cm3.h"

void SysTick_Delay_us(uint32_t us);
void SysTick_Delay_ms(uint32_t ms);
void Delay_us(uint16_t time);
void Delay_ms(uint16_t time);

#endif /* __BSP_DELAY_H*/

