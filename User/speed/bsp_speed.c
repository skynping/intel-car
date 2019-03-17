#include "bsp_speed.h"
#include "bsp_motor.h"
#include "bsp_usart.h"

/************************************************************
	С����ֱ̥��Ϊ6.6cm
	

*************************************************************/
extern uint16_t speedl_CNT_sum; // ����ÿ������������
extern uint16_t speedr_CNT_sum; // ����ÿ������������

uint16_t comparel = 350;
uint16_t comparer = 350;

PID pid;

void PID_Init(void)
{
	pid.Sv = 0.4; // �趨�ٶ�
	pid.Kp = 10;
	pid.T = 1000; // ��������
	pid.Ti = 5000; // ��������
	pid.Td = 1200; // ΢������
}


// �ٶȼ���
static float Get_Speed( uint16_t speedx_CNT_sum)
{
	return (float)((speedx_CNT_sum/20.0)*3.14*6.6*0.01)/0.5; // ��λΪm/s
}

static uint16_t*  Get_Compare(float speedl_value,float speedr_value)
{
	static uint16_t compare[2];
	float speedl =	Get_Speed(speedl_CNT_sum); 
	float speedr =	Get_Speed(speedr_CNT_sum); 
	
	// ���ݻ�ȡ���ٶȶ�̬����ռ�ձ�
	comparel = speedl<speedl_value?comparel+2:comparel-2;
	comparer = speedr<speedr_value?comparer+2:comparer-2;
	
	// ��ֹռ�ձȳ���0-720��Χ
	comparel = comparel>720?720:comparel<0?0:comparel; 
	comparer = comparer>720?720:comparer<0?0:comparer; 
	
	compare[0] = comparel;
	compare[1] = comparer;
	
	// ʵʱ��ʾ�ٶ�
	printf("speedl:%f, comparel:%d; speedr:%f, comparel:%d\r\n",speedl,comparel,speedr,comparer);
	
	return compare;
}

// ǰ���ٶ�
void Go_Ahead_speed(float speed)
{
	uint16_t* compare_all = Get_Compare(speed,speed);
	
	Go_Ahead(compare_all[0],compare_all[1]);

}

// ǰ���ٶ�
void Go_Back_speed(uint16_t speed)
{
	float speedl =	Get_Speed(speedl_CNT_sum); 
	float speedr =	Get_Speed(speedr_CNT_sum); 
	
	

}

// ��ת�ٶ�
void Go_Left_speed(uint16_t speed_l,uint16_t speed_r)
{
	float speedl =	Get_Speed(speedl_CNT_sum); 
	float speedr =	Get_Speed(speedr_CNT_sum); 
	
	

}

// ��ת�ٶ�
void Go_Right_speed(uint16_t speed_l,uint16_t speed_r)
{
	float speedl =	Get_Speed(speedl_CNT_sum); 
	float speedr =	Get_Speed(speedr_CNT_sum); 
	
	

}
