#include "bsp_digital.h"

// ��ʼ���ⲿ�ж�IO��
static void Digital_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(SPEEDx_CLK_PORT | RANGEx_CLK_PORT | MARKx_CLK_PORT, ENABLE);
	// ����
	GPIO_InitStructure.GPIO_Pin = SPEEDl_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPEEDx_PORT, &GPIO_InitStructure);
	GPIO_EXTILineConfig(SPEEDl_GPIO_PortSource, SPEEDl_GPIO_PinSource);
	
	GPIO_InitStructure.GPIO_Pin = SPEEDr_PIN;
	GPIO_Init(SPEEDx_PORT, &GPIO_InitStructure);
	GPIO_EXTILineConfig(SPEEDr_GPIO_PortSource, SPEEDr_GPIO_PinSource);
	
	// ����
	GPIO_InitStructure.GPIO_Pin = RANGEl_PIN;
	GPIO_Init(RANGEx_PORT, &GPIO_InitStructure);
	GPIO_EXTILineConfig(RANGEl_GPIO_PortSource, RANGEl_GPIO_PinSource);
	
	GPIO_InitStructure.GPIO_Pin = RANGEr_PIN ;
	GPIO_Init(RANGEx_PORT, &GPIO_InitStructure);
	GPIO_EXTILineConfig(RANGEr_GPIO_PortSource, RANGEr_GPIO_PinSource);
	
	// �ڰ���ʶ��
	GPIO_InitStructure.GPIO_Pin = MARKl_PIN;
	GPIO_Init(MARKx_PORT,&GPIO_InitStructure);
	GPIO_EXTILineConfig(MARKl_GPIO_PortSource, MARKl_GPIO_PinSource);
	
	GPIO_InitStructure.GPIO_Pin = MARKm_PIN;
	GPIO_Init(MARKx_PORT,&GPIO_InitStructure);
	GPIO_EXTILineConfig(MARKm_GPIO_PortSource, MARKm_GPIO_PinSource);
	
	GPIO_InitStructure.GPIO_Pin = MARKr_PIN;
	GPIO_Init(MARKx_PORT,&GPIO_InitStructure);
	GPIO_EXTILineConfig(MARKr_GPIO_PortSource, MARKr_GPIO_PinSource);
}

static void Digital_EXIT_Config(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	EXTI_InitStructure.EXTI_Line = SPEEDx_LINE | RANGEx_LINE | MARKx_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	// ����жϱ�־λ
	EXTI_ClearITPendingBit(SPEEDl_LINE);
	EXTI_ClearITPendingBit(SPEEDr_LINE);
	EXTI_ClearITPendingBit(RANGEl_LINE);
	EXTI_ClearITPendingBit(RANGEr_LINE);
	EXTI_ClearITPendingBit(MARKl_LINE);
	EXTI_ClearITPendingBit(MARKm_LINE);
	EXTI_ClearITPendingBit(MARKr_LINE);
}

// �����ж����ȼ�
static void Digital_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	/****************����Ϊ���ٲ���*********************/
	// �����ж���Ϊ1
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		
	// ����������жϴ�����
	NVIC_InitStructure.NVIC_IRQChannel = SPEEDl_EXTI1_IRQn ;	
	// ���������ȼ�Ϊ 0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	// ������ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		
	NVIC_InitStructure.NVIC_IRQChannel = SPEEDr_EXTI2_IRQn ;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/****************����Ϊ���벿��*********************/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		
	NVIC_InitStructure.NVIC_IRQChannel = RANGEx_EXTI9_5_IRQn ;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/****************����Ϊ�ڰ��߲���*********************/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		
	NVIC_InitStructure.NVIC_IRQChannel = MARKx_EXTI15_10_IRQn ;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void Digital_Init(void)
{
	Digital_NVIC_Config();
	Digital_GPIO_Config();
	Digital_EXIT_Config();
}



