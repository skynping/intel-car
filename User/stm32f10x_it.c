/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_usart.h"
#include "bsp_tim.h"
#include "bsp_digital.h"
#include "bsp_usart.h"


// 定时器TIM3计数
extern uint16_t time; 

uint16_t time_SPEEDl=0;
uint16_t time_SPEEDr=0;
uint16_t time_RANGEl=0;
uint16_t time_RANGEr=0;
uint16_t time_MARKl=0;
uint16_t time_MARKm=0;
uint16_t time_MARKr=0;

uint16_t speedl_CNT = 0; // 左轮脉冲计数
uint16_t speedl_CNT_sum = 0; // 每个周期脉冲数
uint16_t speedr_CNT = 0; // 右轮脉冲计数
uint16_t speedr_CNT_sum = 0; // 每个周期脉冲数

char USART1_RECV_data; // USART1收到的信息
char USART2_RECV_data; // USART2收到的信息

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/


// 通用定时器TIM3中断函数
void GENERAL_TIM_IRQHandler(void)
{
	if ( TIM_GetITStatus( GENERAL_TIM, TIM_IT_Update) != RESET ) 
	{	
		time++;
		TIM_ClearITPendingBit(GENERAL_TIM , TIM_FLAG_Update);  		 
	}		 	
}

// 通用定时器TIM4中断函数
void GENERAL_TIM4_IRQHandler(void)
{
	if ( TIM_GetITStatus( GENERAL_TIM4, TIM_IT_Update) != RESET ) 
	{	
		TIM_ClearITPendingBit(GENERAL_TIM4 , TIM_FLAG_Update);
		time_SPEEDl++;
		time_SPEEDr++;
		time_RANGEl++;
		time_RANGEr++;
		time_MARKl++;
		time_MARKm++;
		time_MARKr++;
		// 左轮每500ms，记一次总脉冲
		if(time_SPEEDl>=500){
			time_SPEEDl = 0;
			speedl_CNT_sum = speedl_CNT;
			speedl_CNT = 0;
		}
		// 右轮
		if(time_SPEEDr>=500){
			time_SPEEDr = 0;
			speedr_CNT_sum = speedr_CNT;
			speedr_CNT = 0;
		}
		  		 
	}		 	

}

// 测速左
void SPEEDl_EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(SPEEDl_LINE) != RESET)
	{
		speedl_CNT++;
		EXTI_ClearITPendingBit(SPEEDl_LINE);
	}
}	

// 测速右
void SPEEDr_EXTI2_IRQHandler(void)
{
	if (EXTI_GetITStatus(SPEEDr_LINE) != RESET)
	{
		speedr_CNT++;
		EXTI_ClearITPendingBit(SPEEDr_LINE);
	}
}	


// 距离
void RANGEx_EXTI9_5_IRQHandler(void)
{
	// 左
	if (EXTI_GetITStatus(RANGEl_LINE) != RESET)
	{
		
		EXTI_ClearITPendingBit(RANGEl_LINE);
	}
	
	// 右
	if (EXTI_GetITStatus(RANGEr_LINE) != RESET)
	{
		
		EXTI_ClearITPendingBit(RANGEr_LINE);
	}
}

// 黑白线
void MARKx_EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(MARKl_LINE) != RESET)
	{
		
		EXTI_ClearITPendingBit(MARKl_LINE);
	}
	
	if (EXTI_GetITStatus(MARKm_LINE) != RESET)
	{
		
		EXTI_ClearITPendingBit(MARKm_LINE);
	}
	
	if (EXTI_GetITStatus(MARKr_LINE) != RESET)
	{
		
		EXTI_ClearITPendingBit(MARKr_LINE);
	}
}

// USART11中断处理
void DEBUG_USART_IRQHandler(void)
{
	if (USART_GetITStatus(DEBUG_USARTx, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(DEBUG_USARTx, USART_IT_RXNE);
		USART1_RECV_data = USART_ReceiveData(DEBUG_USARTx); // 获取数据字符型
	}

}

// USART2中断处理
void DEBUG_USART2_IRQHandler(void)
{
	if (USART_GetITStatus(DEBUG_USART2, USART_IT_RXNE) != RESET)
//	USART_GetFlagStatus(DEBUG_USART2, USART_IT_RXNE);
	{
		USART_ClearITPendingBit(DEBUG_USART2, USART_IT_RXNE);
		USART2_RECV_data = USART_ReceiveData(DEBUG_USART2);
		printf("--->%c\r\n",USART2_RECV_data);
	}
}



/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
