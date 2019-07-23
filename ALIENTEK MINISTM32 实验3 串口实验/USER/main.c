#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "string.h"
#include <stdlib.h>
#include "hcsr04.h"

//ALIENTEK Mini STM32¿ª·¢°å·¶Àı´úÂë3
//´¿ÚÊµÑé   
//¼¼ÊõÖ§³Ö£ºwww.openedv.com
//¹ãÖİÊĞĞÇÒíµç×Ó¿Æ¼¼ÓĞÏŞ¹«Ë¾
void clear_buff(void);
void ack(char *pc);
 int main(void)
 {	
	u16 t;
	u8 len;	
	u16 times=0; 
  u8 *p1;
	delay_init();	    	 //ÑÓÊ±º¯Êı³õÊ¼»¯	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// ÉèÖÃÖĞ¶ÏÓÅÏÈ¼¶·Ö×é2
	uart_init(115200);	 //´¿Ú³õÊ¼»¯Îª115200
	uart_init(115200);	 //´¿Ú³õÊ¼»¯Îª115200
	LED_Init();		  	 //³õÊ¼»¯ÓëLEDÁ¬½ÓµÄÓ²¼ş½Ó¿Ú 
  LED0=0;
	float length; 
	while(1)
	{
		p1=(u8*)strstr((const char*)(USART_RX_BUF),"0");
		
		if(p1)
			{
			LED0=0;
			clear_buff();
			ack("LED ÁÁÁË\r\n");
			
		}
		p1=(u8*)strstr((const char*)(USART_RX_BUF),"1");
		if(p1)
			{
			LED0=1;
			clear_buff();
			ack("LED ÃğÁË\r\n");
				
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



