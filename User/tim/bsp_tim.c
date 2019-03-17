#include "bsp_tim.h"
#include "bsp_delay.h"

uint16_t time=0; // TIM3定时器计数器

/******************以下为TIM3配置**********************/

// TIM3中断优先级配置
static void GENERAL_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQ ;	
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void GENERAL_TIM_Config(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// 开启定时器时钟,即内部时钟CK_INT=72M
    GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK, ENABLE);
	
		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM_Period;	

	  // 时钟预分频数为
    TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;
	
		// 时钟分频因子 
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		
		// 计数器计数模式
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
		
		// 重复计数器的值
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	
	  // 初始化定时器
    TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
		
		// 清除计数器中断标志位
    TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update);
	  
		// 开启计数器中断
    TIM_ITConfig(GENERAL_TIM,TIM_IT_Update,ENABLE);
		
		// 使能计数器
    TIM_Cmd(GENERAL_TIM, DISABLE);
}

void GENERAL_TIM_Init(void)
{
	GENERAL_TIM_NVIC_Config();
	GENERAL_TIM_Config();
}

// 开启定时器
void Open_TIM(void)
{
	
	TIM_SetCounter(GENERAL_TIM,0); // 清除计数
	time = 0;
	TIM_Cmd(GENERAL_TIM, ENABLE); // 使能TIMx外设
}


// 关闭定时器
void Close_TIM(void)
{
	TIM_Cmd(GENERAL_TIM, DISABLE); // 失能TIMx外设
}

// 获取定时器时间
u32 Get_Timer(void)
{
	u32 t = 0;
	t = time*1000; //time为ms级别转换为us
	t += TIM_GetCounter(GENERAL_TIM); // 得到us
	GENERAL_TIM->CNT = 0; // 将TIM3计数寄存器清零
	Delay_ms(50);
	return t;
}

/******************以下为TIM4配置*********************************/
static void GENERAL_TIM4_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM4_IRQ ;	
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	 
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void GENERAL_TIM4_Config(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// 开启定时器时钟,即内部时钟CK_INT=72M
    GENERAL_TIM4_APBxClock_FUN(GENERAL_TIM4_CLK, ENABLE);
	
		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM4_Period;	

	  // 时钟预分频数为
    TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM4_Prescaler;
	
		// 时钟分频因子 
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		
		// 计数器计数模式
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
		
		// 重复计数器的值
		TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	
	  // 初始化定时器
    TIM_TimeBaseInit(GENERAL_TIM4, &TIM_TimeBaseStructure);
		
		// 清除计数器中断标志位
    TIM_ClearFlag(GENERAL_TIM4, TIM_FLAG_Update);
	  
		// 开启计数器中断
    TIM_ITConfig(GENERAL_TIM4,TIM_IT_Update,ENABLE);
		
		// 使能计数器
    TIM_Cmd(GENERAL_TIM4, ENABLE);
}

void GENERAL_TIM4_Init(void)
{
	GENERAL_TIM4_NVIC_Config();
	GENERAL_TIM4_Config();
}

/******************以下为TIM1输出PWM配置**********************/
// 配置输出GPIO口
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
	// 开启定时器时钟，内部时钟为72M
	ADVANCE_TIM1_APBxClock_FUN(ADVANCE_TIM1_CLK,ENABLE);
	// 时基结构体初始化
	TIM_TimeBaseStructure.TIM_Prescaler = ADVANCE_TIM1_Prescaler; // 驱动CNT计数器时钟
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
	TIM_TimeBaseStructure.TIM_Period = ADVANCE_TIM1_Period; // ARR，自动重载寄存器
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 时钟分频因子
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0; // 重复计数器值，未用到
	TIM_TimeBaseInit(ADVANCE_TIM1,&TIM_TimeBaseStructure); // 初始化定时器
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // 设置未PWM1模式
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; // 输出通道空闲电平极性配置
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset; // 互补输出通道空闲电平极性配置
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; // 互补输出通道电平极性配置
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // 输出通道电平极性配置
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; // 互补输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; // 设置占空比
	TIM_OC1Init(ADVANCE_TIM1, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(ADVANCE_TIM1, TIM_OCPreload_Enable);
	
	TIM_Cmd(ADVANCE_TIM1, ENABLE);	
	// 主输出使能，高级定时器才要
	TIM_CtrlPWMOutputs(ADVANCE_TIM1, ENABLE);
}

void TIM1_PWM_OUT_Init(void)
{
	TIM1_GPIO_Config();
	TIM1_OUT_PWM_Config();
	
}


/******************以下为TIM2输出PWM配置**********************/
//配置控制电机的GPIO口
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

// TIM2 PWM配置
static void TIM2_OUT_PWM_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	// 开启定时器时钟，内部时钟为72M
	GENERAL_TIM2_APBxClock_FUN(GENERAL_TIM2_CLK ,ENABLE);
	// 时基结构体初始化
	TIM_TimeBaseStructure.TIM_Prescaler = GENERAL_TIM2_Prescaler; // 驱动CNT计数器时钟
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
	TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM2_Period; // ARR，自动重载寄存器
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 时钟分频因子
	TIM_TimeBaseInit(GENERAL_TIM2,&TIM_TimeBaseStructure); // 初始化定时器
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // 设置未PWM1模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // 输出通道电平极性配置
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; // 设置占空比
	// 以下为CH1-CH2使能
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

// TIM2 初始化
void TIM2_PWM_OUT_Init(void)
{
	TIM2_GPIO_Config();
	TIM2_OUT_PWM_Config();
	
}


