#include "stm32f10x.h"
#include "beep.h"
void beep_Init(void)
{
RCC ->APB2ENR |= 1 << 3;// ʹ��PORTEʱ��
GPIOB ->CRH   |= 3 << 0;//���������ģʽ
GPIOB ->CRH   &=~ (3 << 2);//PB.8 �������
GPIOB ->ODR   &= ~(1 << 8);//PB.8 ����͵�ƽ
}