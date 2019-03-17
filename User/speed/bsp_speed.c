#include "bsp_speed.h"
#include "bsp_motor.h"
#include "bsp_usart.h"

/************************************************************
	小车轮胎直径为6.6cm
	

*************************************************************/
extern uint16_t speedl_CNT_sum; // 左轮每个周期脉冲数
extern uint16_t speedr_CNT_sum; // 右轮每个周期脉冲数

uint16_t comparel = 350;
uint16_t comparer = 350;

PID pid;

void PID_Init(void)
{
	pid.Sv = 0.4; // 设定速度
	pid.Kp = 10;
	pid.T = 1000; // 采样周期
	pid.Ti = 5000; // 积分周期
	pid.Td = 1200; // 微分周期
}


// 速度计算
static float Get_Speed( uint16_t speedx_CNT_sum)
{
	return (float)((speedx_CNT_sum/20.0)*3.14*6.6*0.01)/0.5; // 单位为m/s
}

static uint16_t*  Get_Compare(float speedl_value,float speedr_value)
{
	static uint16_t compare[2];
	float speedl =	Get_Speed(speedl_CNT_sum); 
	float speedr =	Get_Speed(speedr_CNT_sum); 
	
	// 根据获取的速度动态调整占空比
	comparel = speedl<speedl_value?comparel+2:comparel-2;
	comparer = speedr<speedr_value?comparer+2:comparer-2;
	
	// 防止占空比超出0-720范围
	comparel = comparel>720?720:comparel<0?0:comparel; 
	comparer = comparer>720?720:comparer<0?0:comparer; 
	
	compare[0] = comparel;
	compare[1] = comparer;
	
	// 实时显示速度
	printf("speedl:%f, comparel:%d; speedr:%f, comparel:%d\r\n",speedl,comparel,speedr,comparer);
	
	return compare;
}

// 前进速度
void Go_Ahead_speed(float speed)
{
	uint16_t* compare_all = Get_Compare(speed,speed);
	
	Go_Ahead(compare_all[0],compare_all[1]);

}

// 前进速度
void Go_Back_speed(uint16_t speed)
{
	float speedl =	Get_Speed(speedl_CNT_sum); 
	float speedr =	Get_Speed(speedr_CNT_sum); 
	
	

}

// 左转速度
void Go_Left_speed(uint16_t speed_l,uint16_t speed_r)
{
	float speedl =	Get_Speed(speedl_CNT_sum); 
	float speedr =	Get_Speed(speedr_CNT_sum); 
	
	

}

// 右转速度
void Go_Right_speed(uint16_t speed_l,uint16_t speed_r)
{
	float speedl =	Get_Speed(speedl_CNT_sum); 
	float speedr =	Get_Speed(speedr_CNT_sum); 
	
	

}
