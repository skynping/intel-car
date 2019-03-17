#include "bsp_ultrasonic.h"

// ������ģ��ʹ��HC-SR04�ͺţ�5V����

// ��ʼ������
static void ULTRASONIC_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( TRIG_CLK_PORT | ECHO_CLK_PORT,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = TRIG_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // trig��������Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TRIG_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ECHO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // echo��������Ϊ��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ECHO_PORT, &GPIO_InitStructure);
}


void ULTRASONIC_Init(void)
{
	ULTRASONIC_Config();
	TRIG_LOW;
	ECHO_LOW;
}

float Get_Length(void)
{
	uint16_t taken_time = 0; // ���泬���������������ѵ�ʱ��
	float length = 0; // �������
	int i = 5; // �ܹ�����5��
	float sum_length = 0; // ����ܾ���
	
	for(;i>0;i--)
	{
		
		// ��ʼ�ɼ����ݣ�����ģ��ʱ��ͼ��������
		TRIG_HIGH; // trig��������ߵ�ƽ
		Delay_us(20); // �ӳ� 20us
		TRIG_LOW; // trig��������͵�ƽ
		while(ECHO_READ == RESET); // �ȴ�echo������0��Ϊ1
		Open_TIM();
		while(ECHO_READ != RESET); // �ȴ�echo������1��Ϊ0
		Close_TIM();
		taken_time = Get_Timer(); // ��ȡʱ�䣬�ֱ���Ϊ1us
		length = ((float)taken_time/58.0);	 // ������룬��λcm
		sum_length += length; //�����ܾ���
	}
	
	
	return sum_length/5.0; // ����ƽ��ֵ
}

