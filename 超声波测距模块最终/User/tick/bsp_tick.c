#include"bsp_tick.h"

void Tim3_Config()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	  NVIC_Configuration();  //配置中断函数
	  //使能TIM3时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	  
	 
    
	  TIM_TimeBaseStructure.TIM_Period =49999;
	  TIM_TimeBaseStructure.TIM_Prescaler=71;  //设置分频系数为71
	  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;  //设置为向上计数模式
	
	  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	 // TIM_ARRPreloadConfig(TIM3,ENABLE);  //使能TIM3重载寄存器
	  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);  //注意这里函数的意思是打开中断，溢出中断
	  
}

static void NVIC_Configuration()
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}