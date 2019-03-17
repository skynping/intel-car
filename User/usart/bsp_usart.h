#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f10x.h"
#include <stdio.h>
/******************此处只初始化了USART1，USART2的C文件********************/
#define DEBUG_USART1_ON      0
#define DEBUG_USART2_ON      0
#define DEBUG_USART3_ON      1
#define DEBUG_USART4_ON      0
#define DEBUG_USART5_ON      0

//// 串口1-USART1(默认)
//#define  DEBUG_USARTx                   USART1
//#define  DEBUG_USART_CLK                RCC_APB2Periph_USART1
//#define  DEBUG_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
//#define  DEBUG_USART_BAUDRATE           115200

//// USART GPIO 引脚宏定义
//#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
//#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
//    
//#define  DEBUG_USART_TX_GPIO_PORT       GPIOA   
//#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_9
//#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
//#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_10

//#define  DEBUG_USART_IRQ                USART1_IRQn
//#define  DEBUG_USART_IRQHandler         USART1_IRQHandler


//串口2-USART2
#define  DEBUG_USART2                    USART2
#define  DEBUG_USART2_CLK                RCC_APB1Periph_USART2
#define  DEBUG_USART2_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART2_BAUDRATE           9600

// USART GPIO 引脚宏定义
#define  DEBUG_USART2_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART2_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART2_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART2_TX_GPIO_PIN        GPIO_Pin_2
#define  DEBUG_USART2_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART2_RX_GPIO_PIN        GPIO_Pin_3

#define  DEBUG_USART2_IRQ                USART2_IRQn
#define  DEBUG_USART2_IRQHandler         USART2_IRQHandler


#if DEBUG_USART3_ON 
//串口3-USART3
#define  DEBUG_USARTx                   USART3
#define  DEBUG_USART_CLK                RCC_APB1Periph_USART3
#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOB)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT       GPIOB   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_10
#define  DEBUG_USART_RX_GPIO_PORT       GPIOB
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_11

#define  DEBUG_USART_IRQ                USART3_IRQn
#define  DEBUG_USART_IRQHandler         USART3_IRQHandler
#endif

#if DEBUG_USART4_ON 
//串口4-UART4
#define  DEBUG_USART4                   UART4
#define  DEBUG_USART4_CLK                RCC_APB1Periph_UART4
#define  DEBUG_USART4_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART4_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART4_GPIO_CLK           (RCC_APB2Periph_GPIOC)
#define  DEBUG_USART4_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART4_TX_GPIO_PORT       GPIOC   
#define  DEBUG_USART4_TX_GPIO_PIN        GPIO_Pin_10
#define  DEBUG_USART4_RX_GPIO_PORT       GPIOC
#define  DEBUG_USART4_RX_GPIO_PIN        GPIO_Pin_11

#define  DEBUG_USART4_IRQ                UART4_IRQn
#define  DEBUG_USART4_IRQHandler         UART4_IRQHandler
#endif

#if DEBUG_USART5_ON 
//串口5-UART5
#define  DEBUG_USART5                   UART5
#define  DEBUG_USART5_CLK                RCC_APB1Periph_UART5
#define  DEBUG_USART5_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART5_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART5_GPIO_CLK           (RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD)
#define  DEBUG_USART5_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART5_TX_GPIO_PORT       GPIOC   
#define  DEBUG_USART5_TX_GPIO_PIN        GPIO_Pin_12
#define  DEBUG_USART5_RX_GPIO_PORT       GPIOD
#define  DEBUG_USART5_RX_GPIO_PIN        GPIO_Pin_2

#define  DEBUG_USART5_IRQ                UART5_IRQn
#define  DEBUG_USART5_IRQHandler         UART5_IRQHandler

#endif

void USART_Config(void);
void Usart_SendByte(USART_TypeDef* pUSARTx, uint8_t data);
void Usart_SendHalfWord(USART_TypeDef* pUSARTx, uint16_t data);
void Usart_SendArray(USART_TypeDef* pUSARTx, uint8_t *array,uint8_t num);
void Usart_SendStr(USART_TypeDef* pUSARTx, uint8_t *str);

void USART2_Config(void);
#endif  /* __BSP_USART_H */

