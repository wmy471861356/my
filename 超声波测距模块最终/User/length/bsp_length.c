#include<bsp_length.h>


//ECHO PA4
//TRIG PA5
void Distance_Config()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //����IO�ڶ�Ӧ��ʱ��
	  
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	 // GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;  //���ŵ�ģʽ����Ϊ��������ģʽ
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //����Ϊͨ���������ģʽ
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
}