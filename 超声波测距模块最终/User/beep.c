#include "stm32f10x.h"
#include "beep.h"
void beep_Init(void)
{
RCC ->APB2ENR |= 1 << 3;// 使能PORTE时钟
GPIOB ->CRH   |= 3 << 0;//先设置输出模式
GPIOB ->CRH   &=~ (3 << 2);//PB.8 推挽输出
GPIOB ->ODR   &= ~(1 << 8);//PB.8 输出低电平
}