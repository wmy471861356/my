#ifndef __TIM3TICK_H
#define	__TIM3TICK_H

#include "stm32f10x.h"
#include "misc.h"
#include "stm32f10x_tim.h"
//#include <stdio.h>

void Tim3_Config();  //配置定时器TIM3
static void NVIC_Configuration();  //配置定时器中断，当计数时间到时触发中断

#endif /* __USART1_H */
