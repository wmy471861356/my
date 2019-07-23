#include<bsp_length.h>


//ECHO PA4
//TRIG PA5
void Distance_Config()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //开启IO口对应的时钟
	  
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	 // GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;  //引脚的模式设置为浮空输入模式
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //配置为通用推挽输出模式
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
}