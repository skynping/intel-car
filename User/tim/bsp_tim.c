#include "bsp_tim.h"
#include "bsp_delay.h"

uint16_t time=0; // TIM3��ʱ��������

/******************����ΪTIM3����**********************/

// TIM3�ж����ȼ�����
static void GENERAL_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQ ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void GENERAL_TIM_Config(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
    GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK, ENABLE);
	
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM_Period;	

	  // ʱ��Ԥ��Ƶ��Ϊ
    TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;
	
		// ʱ�ӷ�Ƶ���� 
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		
		// ����������ģʽ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
		
		// �ظ���������ֵ
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	
	  // ��ʼ����ʱ��
    TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
		
		// ����������жϱ�־λ
    TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update);
	  
		// �����������ж�
    TIM_ITConfig(GENERAL_TIM,TIM_IT_Update,ENABLE);
		
		// ʹ�ܼ�����
    TIM_Cmd(GENERAL_TIM, DISABLE);
}

void GENERAL_TIM_Init(void)
{
	GENERAL_TIM_NVIC_Config();
	GENERAL_TIM_Config();
}

// ������ʱ��
void Open_TIM(void)
{
	
	TIM_SetCounter(GENERAL_TIM,0); // �������
	time = 0;
	TIM_Cmd(GENERAL_TIM, ENABLE); // ʹ��TIMx����
}


// �رն�ʱ��
void Close_TIM(void)
{
	TIM_Cmd(GENERAL_TIM, DISABLE); // ʧ��TIMx����
}

// ��ȡ��ʱ��ʱ��
u32 Get_Timer(void)
{
	u32 t = 0;
	t = time*1000; //timeΪms����ת��Ϊus
	t += TIM_GetCounter(GENERAL_TIM); // �õ�us
	GENERAL_TIM->CNT = 0; // ��TIM3�����Ĵ�������
	Delay_ms(50);
	return t;
}

/******************����ΪTIM4����*********************************/
static void GENERAL_TIM4_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM4_IRQ ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void GENERAL_TIM4_Config(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
    GENERAL_TIM4_APBxClock_FUN(GENERAL_TIM4_CLK, ENABLE);
	
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM4_Period;	

	  // ʱ��Ԥ��Ƶ��Ϊ
    TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM4_Prescaler;
	
		// ʱ�ӷ�Ƶ���� 
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		
		// ����������ģʽ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
		
		// �ظ���������ֵ
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	
	  // ��ʼ����ʱ��
    TIM_TimeBaseInit(GENERAL_TIM4, &TIM_TimeBaseStructure);
		
		// ����������жϱ�־λ
    TIM_ClearFlag(GENERAL_TIM4, TIM_FLAG_Update);
	  
		// �����������ж�
    TIM_ITConfig(GENERAL_TIM4,TIM_IT_Update,ENABLE);
		
		// ʹ�ܼ�����
    TIM_Cmd(GENERAL_TIM4, ENABLE);
}

void GENERAL_TIM4_Init(void)
{
	GENERAL_TIM4_NVIC_Config();
	GENERAL_TIM4_Config();
}

/******************����ΪTIM1���PWM����**********************/
// �������GPIO��
static void TIM1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  TIM1_CH1_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TIM1_CH1_PORT, &GPIO_InitStructure);
	GPIO_ResetBits(TIM1_CH1_PORT,TIM1_CH1_PIN);
}

static void TIM1_OUT_PWM_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	// ������ʱ��ʱ�ӣ��ڲ�ʱ��Ϊ72M
	ADVANCE_TIM1_APBxClock_FUN(ADVANCE_TIM1_CLK,ENABLE);
	// ʱ���ṹ���ʼ��
	TIM_TimeBaseStructure.TIM_Prescaler = ADVANCE_TIM1_Prescaler; // ����CNT������ʱ��
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period = ADVANCE_TIM1_Period; // ARR���Զ����ؼĴ���
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // ʱ�ӷ�Ƶ����
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0; // �ظ�������ֵ��δ�õ�
	TIM_TimeBaseInit(ADVANCE_TIM1,&TIM_TimeBaseStructure); // ��ʼ����ʱ��
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // ����δPWM1ģʽ
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; // ���ͨ�����е�ƽ��������
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset; // �������ͨ�����е�ƽ��������
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; // �������ͨ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // ���ͨ����ƽ��������
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; // �������ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // ���ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; // ����ռ�ձ�
	TIM_OC1Init(ADVANCE_TIM1, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(ADVANCE_TIM1, TIM_OCPreload_Enable);
	
	TIM_Cmd(ADVANCE_TIM1, ENABLE);	
	// �����ʹ�ܣ��߼���ʱ����Ҫ
	TIM_CtrlPWMOutputs(ADVANCE_TIM1, ENABLE);
}

void TIM1_PWM_OUT_Init(void)
{
	TIM1_GPIO_Config();
	TIM1_OUT_PWM_Config();
	
}


/******************����ΪTIM2���PWM����**********************/
//���ÿ��Ƶ����GPIO��
static void TIM2_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(TIM2_CHx_CLK_PORT, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  TIM2_CH1_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TIM2_CHx_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  TIM2_CH2_PIN ;
	GPIO_Init(TIM2_CHx_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  TIM2_CH3_PIN ;
	GPIO_Init(TIM2_CHx_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  TIM2_CH4_PIN ;
	GPIO_Init(TIM2_CHx_PORT, &GPIO_InitStructure);
	
	GPIO_ResetBits(TIM2_CHx_PORT,TIM2_CH1_PIN);
	GPIO_ResetBits(TIM2_CHx_PORT,TIM2_CH2_PIN);
	GPIO_ResetBits(TIM2_CHx_PORT,TIM2_CH3_PIN);
	GPIO_ResetBits(TIM2_CHx_PORT,TIM2_CH4_PIN);
}

// TIM2 PWM����
static void TIM2_OUT_PWM_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	// ������ʱ��ʱ�ӣ��ڲ�ʱ��Ϊ72M
	GENERAL_TIM2_APBxClock_FUN(GENERAL_TIM2_CLK ,ENABLE);
	// ʱ���ṹ���ʼ��
	TIM_TimeBaseStructure.TIM_Prescaler = GENERAL_TIM2_Prescaler; // ����CNT������ʱ��
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM2_Period; // ARR���Զ����ؼĴ���
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // ʱ�ӷ�Ƶ����
	TIM_TimeBaseInit(GENERAL_TIM2,&TIM_TimeBaseStructure); // ��ʼ����ʱ��
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // ����δPWM1ģʽ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // ���ͨ����ƽ��������
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // ���ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; // ����ռ�ձ�
	// ����ΪCH1-CH2ʹ��
	TIM_OC1Init(GENERAL_TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM2, TIM_OCPreload_Enable);
	
	TIM_OC2Init(GENERAL_TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(GENERAL_TIM2, TIM_OCPreload_Enable);
	
	TIM_OC3Init(GENERAL_TIM2, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(GENERAL_TIM2, TIM_OCPreload_Enable);
	
	TIM_OC4Init(GENERAL_TIM2, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(GENERAL_TIM2, TIM_OCPreload_Enable);
	TIM_Cmd(GENERAL_TIM2, ENABLE);	

}

// TIM2 ��ʼ��
void TIM2_PWM_OUT_Init(void)
{
	TIM2_GPIO_Config();
	TIM2_OUT_PWM_Config();
	
}


