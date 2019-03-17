#ifndef __BSP_TIM_H
#define __BSP_TIM_H

#include "stm32f10x.h"


// ʹ��ͨ�ö�ʱ��TIM3
#define            GENERAL_TIM                   TIM3
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM3
#define            GENERAL_TIM_Period            (1000-1) // 1KHZ
#define            GENERAL_TIM_Prescaler         (72-1)
#define            GENERAL_TIM_IRQ               TIM3_IRQn
#define            GENERAL_TIM_IRQHandler        TIM3_IRQHandler

// ʹ��ͨ�ö�ʱ��TIM4(����)
#define            GENERAL_TIM4                   TIM4
#define            GENERAL_TIM4_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM4_CLK               RCC_APB1Periph_TIM4
#define            GENERAL_TIM4_Period            (1000-1) // 1KHZ
#define            GENERAL_TIM4_Prescaler         (72-1)
#define            GENERAL_TIM4_IRQ               TIM4_IRQn
#define            GENERAL_TIM4_IRQHandler        TIM4_IRQHandler

// ʹ�ø߼���ʱ��TIM1���PWM���ƶ��
#define            ADVANCE_TIM1                   TIM1
#define            ADVANCE_TIM1_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            ADVANCE_TIM1_CLK               RCC_APB2Periph_TIM1
// PWM �źŵ�Ƶ�� F = TIM_CLK/{(ARR+1)*(PSC+1)},
// ���Ƶ��50HZ�����ռ�ձ����÷�Χ23-125���ֱ���Ϊ1.77�ȣ�ARR = 900
#define            ADVANCE_TIM1_Period            (900-1) //(200-1) //ARR
#define            ADVANCE_TIM1_Prescaler         (1600-1) //(7200-1) //PSC
#define            ADVANCE_TIM1_IRQ               TIM1_IRQn
#define            ADVANCE_TIM1_IRQHandler        TIM1_IRQHandler

// TIM1 CH1 PA8 �������
#define 						TIM1_CH1_PIN     							GPIO_Pin_8
#define 						TIM1_CH1_PORT									GPIOA
#define 						TIM1_CH1_CLK_PORT   					RCC_APB2Periph_GPIOA


//ʹ��ͨ�ö�ʱ��TIM2����������� �ֱ�ΪPA0-PA3��CH1-CH4�� 
#define            GENERAL_TIM2                   TIM2
#define            GENERAL_TIM2_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM2_CLK               RCC_APB1Periph_TIM2
#define            GENERAL_TIM2_Period            (720-1) //ARR
#define            GENERAL_TIM2_Prescaler         0 // PSC ��Ƶ��10KHZ
#define            GENERAL_TIM2_IRQ               TIM2_IRQn
#define            GENERAL_TIM2_IRQHandler        TIM2_IRQHandler

//D12-PD15��CH1-CH4��
#define 						TIM2_CH1_PIN     							GPIO_Pin_0
#define 						TIM2_CH2_PIN     							GPIO_Pin_1
#define 						TIM2_CH3_PIN     							GPIO_Pin_2
#define 						TIM2_CH4_PIN     							GPIO_Pin_3
#define 						TIM2_CHx_PORT									GPIOA
#define 						TIM2_CHx_CLK_PORT   					RCC_APB2Periph_GPIOA



void GENERAL_TIM_Init(void);
void Open_TIM(void);
void Close_TIM(void);
u32 Get_Timer(void);
void GENERAL_TIM4_Init(void);
void TIM1_PWM_OUT_Init(void);
void TIM2_PWM_OUT_Init(void);

#endif /*__BSP_TIM_H*/
