
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_length.h"
#include "bsp_tick.h"
#include "led.h"
#include "string.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include <stdlib.h>
#include "lcd.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"
#include "pwm.h"
#include "lcd.h"
#include "dht11.h"
#include "key.h"
#include "stm32f10x_adc.h"
#include "beep.h"
//ע������ĳ�����ģ���VCC������+5V�������+3V�Ļ��ᵼ�²�಻׼
#define CLI()      __set_PRIMASK(1)		/* �ر����ж� */  
#define SEI() __set_PRIMASK(0)		/*�����ж�*/

void Delay(unsigned short int time);  //���Ե���ʱ����
float ChangeDistance(unsigned int cout1);  //ʱ��תΪ���뺯��


//ECHO PA4
//TRIG PA5
 /**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{  
	 int i=0;
	 int a=0;
 
	 u8 len;	
	 u16 times=0; 
   u8 x=0;
   u16 adcx;
	 float temp;	 
	 u8 t=0;			    
	 u8 temperature;  	    
	 u8 humidity;    	
   
  
	  unsigned int count=0;
	  float distance=0;
	  
	  float distancebuf[]={0};
		 char c[5];
		

		
	   delay_init();	    	 //��ʱ������ʼ��	  
	   uart_init(115200);	 	//���ڳ�ʼ��
	
	
 	  
	 
	 	LCD_Init();				//��ʼ��LCD
		USART1_Config();
    Distance_Config();  //���ģ���Ӧ�����ų�ʼ��
    CLI() ;//�ر����ж�
	  SEI(); //�����ж�
	  Tim3_Config();  //��ʱ���ĳ�ʼ��
	 

	  GPIO_ResetBits(GPIOA,GPIO_Pin_5);  //�����͵�ƽ
	  
		 
	  		
			
		
	     			
 
	
 
		POINT_COLOR=RED;//��������Ϊ��ɫ 
	  
 	while(DHT11_Init())	//DHT11��ʼ��	
	{
		LCD_ShowString(60,130,300,16,16,"DHT11 Error");
		delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		delay_ms(200);
	}								   
	
	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
 	LCD_ShowString(60,150,300,16,16,"Temp:  C");	 
 	LCD_ShowString(60,170,300,16,16,"Humi:  %");
	LCD_ShowString(60,190,150,16,16,"distance:      cm");		
	while(1)
	{	    	    
 		if(t%10==0)//ÿ100ms��ȡһ��
		{									  
			DHT11_Read_Data(&temperature,&humidity);		//��ȡ��ʪ��ֵ					    
			LCD_ShowNum(60+40,150,temperature,2,16);		//��ʾ�¶�	   		   
			LCD_ShowNum(60+40,170,humidity,2,16);			//��ʾʪ��	 	   
		}				   
	 	delay_ms(10);
		t++;

			if(i==0){
      printf("��࿪ʼ\n");
				i++;
			}
			 GPIO_SetBits(GPIOA,GPIO_Pin_5);  //���ߵ�ƽ
			 Delay(20);  //��ʱ20��΢��
		
			 GPIO_ResetBits(GPIOA,GPIO_Pin_5); 

       TIM3->CNT=0;  //TIM3�ļ�������0

       while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 0); //�ȴ�ECHO�ĸߵ�ƽ
		
       
       TIM_Cmd(TIM3,ENABLE);  //����TIM3���м�ʱ
       
			while((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 1) && (TIM3->CNT < TIM3->ARR-10));
			 
			  TIM_Cmd(TIM3,DISABLE);  
       		
        count=TIM3->CNT;
        
		
			  	
			 
				beep_Init();      //��ʼ��������
			  LED_Init();				//��ʼ����LED���ӵ�Ӳ���ӿ�
			  LED0=1;
        LED1=1;		
				distance=ChangeDistance(count);
				LCD_ShowNum(130,190,distance,5,16);		
			  printf(" ��ǰ����Ϊ��%.2f cm\n",distance);
				printf(" ��ǰ�¶�Ϊ��%d C\n",temperature);
				printf(" ��ǰʪ��Ϊ��%d %%\n",humidity);
				printf("\n");
				if(distance<50){
						LED0=0;
						GPIOB ->ODR   |= (1 << 8); 			//PB.8 �����  ��������
				}
				else{
						LED1=0;
					  GPIOB ->ODR   &= ~(1 << 8);     //PB.8 �����  ��������
				}
		
				POINT_COLOR=BLUE;
		
				POINT_COLOR=RED;
										    		
			  Delay(50000); 
				Delay(50000);
				Delay(50000);
				
				
       
	 }
 }

void Delay(unsigned short int time)  //���Ե���ʱ����
{
    unsigned char i=0;
	  while(time--)
		{
        i=100;
			  while(i--);
    }
}

float ChangeDistance(unsigned int cout1)
{
    float distance=0;
	  
	  distance=cout1/58.0;
	
	  return distance;
}


/*********************************************END OF FILE**********************/