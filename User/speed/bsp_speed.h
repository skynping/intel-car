#ifndef __BSP_SPEED_H
#define __BSP_SPEED_H

#include "stm32f10x.h"

// 定义PID结构体
typedef struct
{
	float Sv; // 用户设定值
	float Pv;
	
	float Kp;
	float T; // PID计算周期
	float Ti;
	float Td;
	
	float Ek; // 本次偏差
	float Ek_1; // 前一次偏差
	float SEk; // 历史偏差之和
	
	float OUT0;
	
	float OUT; // 输出量
}PID;

void Go_Ahead_speed(float speed);


#endif /* __BSP_SPEED_H */
