#include "stm32f10x.h"   
#include "psd_led.h"
#include "bsp_usart.h"
#include "bsp_delay.h"
#include "bsp_tim.h"
#include "bsp_ultrasonic.h"
#include "bsp_digital.h"
#include "bsp_motor.h"
#include "bsp_speed.h"

int main(void)
{	
 extern uint16_t time_SPEEDl;
	extern uint16_t time_SPEEDr;
	extern uint16_t time_RANGEl;
	extern uint16_t time_RANGEr;
	extern uint16_t time_MARKl;
	extern uint16_t time_MARKm;
	extern uint16_t time_MARKr;
	
	extern uint16_t speedl_CNT_sum;
	extern uint16_t speedr_CNT_sum;
	
	extern uint16_t speedl_CNT;
	int j = 0;
	float length = 0.0; // ������ģ�����
	int i = 25;
//	extern uint16_t ON; 
	USART_Config(); //USART1���ڳ�ʼ��
//	USART2_Config();//USART2���ڳ�ʼ����Ӱ���Ҳ�����������A2��A3
	LED_GPIO_Config(); //LED��ʼ��
	GENERAL_TIM_Init(); //ͨ�ö�ʱ��TIM3��ʼ��
	TIM1_PWM_OUT_Init(); // ��ʼ��TIM1
	TIM2_PWM_OUT_Init(); // ��ʼ��TIM2
	ULTRASONIC_Init(); // ��ʼ��������ģ��
	Digital_Init(); // ��ʼ������������
	GENERAL_TIM4_Init(); // ��ʼ����ʱ��TIM3
	
	
//	TIM_SetCompare1(GENERAL_TIM2, 0);
//	TIM_SetCompare2(GENERAL_TIM2, 350);
//	TIM_SetCompare1(GENERAL_TIM2, 880);
//	TIM_SetCompare2(GENERAL_TIM2, 0);
//	TIM_SetCompare3(GENERAL_TIM2, 350);
//	TIM_SetCompare4(GENERAL_TIM2, 0);
	Go_Ahead(350,350);
//	Go_Back(350,350);
//	Go_Left(350,300);
//		Go_Right(300,350);
//	Go_Stop();
//	printf("��ʼ����\r\n");
	while(1)
	{
		Go_Ahead_speed(0.45);
//		for(j=300;j<880;j++)
//		{
//			TIM_SetCompare1(GENERAL_TIM2, j);
//			TIM_SetCompare2(GENERAL_TIM2, 0);
//			TIM_SetCompare3(GENERAL_TIM2, j);
//			TIM_SetCompare4(GENERAL_TIM2, 0);
//			Delay_ms(100);
//		}
//		TIM_SetCompare1(ADVANCE_TIM1, 26);
//		Delay_ms(2000);
//		TIM_SetCompare1(ADVANCE_TIM1, 100);
//		Delay_ms(2000);
//		TIM_SetCompare1(ADVANCE_TIM1, 35);
//		Delay_ms(2000);
//		TIM_SetCompare1(ADVANCE_TIM1, 80);
//		Delay_ms(500);
//		TIM_SetCompare1(ADVANCE_TIM1, 66);
//		printf("Value:%d\r\n",123);
//		Delay_ms(1000);
//		TIM_SetCompare1(ADVANCE_TIM1, 30);
//		Delay_ms(500);
//		 Go_Ahead_speed(0.13);
//		Usart_SendStr(USART2,"main\r\n");
//		LED3_ON_OR_OFF;
//		Delay_ms(1000);
//		Delay_ms(1000);
//		length = Get_Length();
//		printf("��þ���Ϊ%fcm,�Ƕ�Ϊ%f\r\n",length,0.0);
		
//		for(;i<125;i+=5){
//			TIM_SetCompare1(ADVANCE_TIM1, i);
//			Delay_ms(500);
//			length = Get_Length();
//			printf("��þ���Ϊ%fcm,�Ƕ�Ϊ%f\r\n",length,(i-23)*1.77);
//		}
		
//		TIM_SetCompare1(GENERAL_TIM2, i);
//		TIM_SetCompare2(GENERAL_TIM2, 0);
//		TIM_SetCompare3(GENERAL_TIM2, i);
//		TIM_SetCompare4(GENERAL_TIM2, 0);
////		
//		if(i<300){
//			i=900;
//		}
//		i-=10;
//		Delay_ms(500);
////		
//		LED3_ON_OR_OFF;
//		Delay_ms(200);

//		if(ON==1)
//		{
//			printf("hello");
//			LED2_ON_OR_OFF;
//			Delay_ms(1000);
//			ON=0;
//		}
printf("speed1_CNT:%d; speedr_CNT:%d\r\n",speedl_CNT_sum,speedr_CNT_sum);
//			if(time_SPEEDl>=1000)
//			{
//				time_SPEEDl = 0;
//				printf("speed1_CNT:%d\r\n",speedl_CNT);
//				speedl_CNT = 0;
//			}
			Delay_ms(1000);

		
	}
}

