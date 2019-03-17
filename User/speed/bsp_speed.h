#ifndef __BSP_SPEED_H
#define __BSP_SPEED_H

#include "stm32f10x.h"

// ����PID�ṹ��
typedef struct
{
	float Sv; // �û��趨ֵ
	float Pv;
	
	float Kp;
	float T; // PID��������
	float Ti;
	float Td;
	
	float Ek; // ����ƫ��
	float Ek_1; // ǰһ��ƫ��
	float SEk; // ��ʷƫ��֮��
	
	float OUT0;
	
	float OUT; // �����
}PID;

void Go_Ahead_speed(float speed);


#endif /* __BSP_SPEED_H */
