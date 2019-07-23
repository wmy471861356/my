#include"bsp_tick.h"

void Tim3_Config()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	  NVIC_Configuration();  //�����жϺ���
	  //ʹ��TIM3ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	  
	 
    
	  TIM_TimeBaseStructure.TIM_Period =49999;
	  TIM_TimeBaseStructure.TIM_Prescaler=71;  //���÷�Ƶϵ��Ϊ71
	  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;  //����Ϊ���ϼ���ģʽ
	
	  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	 // TIM_ARRPreloadConfig(TIM3,ENABLE);  //ʹ��TIM3���ؼĴ���
	  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);  //ע�����ﺯ������˼�Ǵ��жϣ�����ж�
	  
}

static void NVIC_Configuration()
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* �����ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}