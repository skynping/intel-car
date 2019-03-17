#include "bsp_motor.h"
#include "bsp_tim.h"


/*
		CH1  CH2  CH3  CH4  (IN1-IN4) 
右  1    0    1    0      前进
左  0		 1    0     1     后退
*/

// 左前
static void Go_Aheadl(uint16_t Compare1)
{
	TIM_SetCompare1(GENERAL_TIM2, Compare1);
	TIM_SetCompare2(GENERAL_TIM2, 0);
}

// 左后
static void Go_Backl(uint16_t Compare1)
{
	TIM_SetCompare1(GENERAL_TIM2, 0);
	TIM_SetCompare2(GENERAL_TIM2, Compare1);
}

// 右前
static void Go_Aheadr(uint16_t Compare1)
{
	TIM_SetCompare3(GENERAL_TIM2, Compare1);
	TIM_SetCompare4(GENERAL_TIM2, 0);
}

// 右后
static void Go_Backr(uint16_t Compare1)
{
	
	TIM_SetCompare3(GENERAL_TIM2, 0);
	TIM_SetCompare4(GENERAL_TIM2, Compare1);
}

/********************Compare1_l为占空比，最大设置为900*********************/
void Go_Stop(void)
{
	TIM_SetCompare1(GENERAL_TIM2, 0);
	TIM_SetCompare2(GENERAL_TIM2, 0);
	TIM_SetCompare3(GENERAL_TIM2, 0);
	TIM_SetCompare4(GENERAL_TIM2, 0);

}

// 前行
void Go_Ahead(uint16_t Compare1_l, uint16_t Compare1_r)
{
	Go_Aheadl(Compare1_l);
	Go_Aheadr(Compare1_r);
}

// 后退
void Go_Back(uint16_t Compare1_l, uint16_t Compare1_r)
{
	Go_Backl(Compare1_l);
	Go_Backr(Compare1_r);
}

// 左转
void Go_Left(uint16_t Compare1_l, uint16_t Compare1_r)
{
	Go_Aheadl(Compare1_l);
	Go_Backr(Compare1_r);
}

// 右转
void Go_Right(uint16_t Compare1_l, uint16_t Compare1_r)
{
	Go_Aheadr(Compare1_r);
	Go_Backl(Compare1_l);
}