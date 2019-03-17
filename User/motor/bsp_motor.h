#ifndef __BSP_MOTOR_H
#define __BSP_MOTOR_H

#include "stm32f10x.h"

void Go_Stop(void);
void Go_Ahead(uint16_t Compare1_l, uint16_t Compare1_r); // ǰ��
void Go_Back(uint16_t Compare1_l, uint16_t Compare1_r); // ����
void Go_Left(uint16_t Compare1_l, uint16_t Compare1_r); // ��ת
void Go_Right(uint16_t Compare1_l, uint16_t Compare1_r); // ��ת

#endif /* __BSP_MOTOR_H */
