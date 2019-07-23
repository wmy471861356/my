#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "string.h"
#include <stdlib.h>
#include "hcsr04.h"

//ALIENTEK Mini STM32�����巶������3
//���ʵ��   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
void clear_buff(void);
void ack(char *pc);
 int main(void)
 {	
	u16 t;
	u8 len;	
	u16 times=0; 
  u8 *p1;
	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	uart_init(115200);	 //��ڳ�ʼ��Ϊ115200
	uart_init(115200);	 //��ڳ�ʼ��Ϊ115200
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ� 
  LED0=0;
	float length; 
	while(1)
	{
		p1=(u8*)strstr((const char*)(USART_RX_BUF),"0");
		
		if(p1)
			{
			LED0=0;
			clear_buff();
			ack("LED ����\r\n");
			
		}
		p1=(u8*)strstr((const char*)(USART_RX_BUF),"1");
		if(p1)
			{
			LED0=1;
			clear_buff();
			ack("LED ����\r\n");
				
		}
			
		
	
	}		
}
void clear_buff(void)
{
	u16 i;
	
	for(i=0;i<USART_RX_STA;i++)
	{
	USART_RX_BUF[i]=0;
	}
	USART_RX_STA=0;
}
void ack(char *pc)
	{
u16 t;
		for(t=0;t<(strlen(pc));t++)
		{
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
			USART_SendData(USART1,pc[t]);
		}
		USART_RX_STA=0;
}



