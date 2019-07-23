
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
//注意这里的超声波模块的VCC必须是+5V，如果是+3V的话会导致测距不准
#define CLI()      __set_PRIMASK(1)		/* 关闭总中断 */  
#define SEI() __set_PRIMASK(0)		/*开总中断*/

void Delay(unsigned short int time);  //粗略的延时函数
float ChangeDistance(unsigned int cout1);  //时间转为距离函数


//ECHO PA4
//TRIG PA5
 /**
  * @brief  主函数
  * @param  无
  * @retval 无
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
		

		
	   delay_init();	    	 //延时函数初始化	  
	   uart_init(115200);	 	//串口初始化
	
	
 	  
	 
	 	LCD_Init();				//初始化LCD
		USART1_Config();
    Distance_Config();  //测距模块对应的引脚初始化
    CLI() ;//关闭总中断
	  SEI(); //开总中断
	  Tim3_Config();  //定时器的初始化
	 

	  GPIO_ResetBits(GPIOA,GPIO_Pin_5);  //先拉低电平
	  
		 
	  		
			
		
	     			
 
	
 
		POINT_COLOR=RED;//设置字体为红色 
	  
 	while(DHT11_Init())	//DHT11初始化	
	{
		LCD_ShowString(60,130,300,16,16,"DHT11 Error");
		delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		delay_ms(200);
	}								   
	
	POINT_COLOR=BLUE;//设置字体为蓝色 
 	LCD_ShowString(60,150,300,16,16,"Temp:  C");	 
 	LCD_ShowString(60,170,300,16,16,"Humi:  %");
	LCD_ShowString(60,190,150,16,16,"distance:      cm");		
	while(1)
	{	    	    
 		if(t%10==0)//每100ms读取一次
		{									  
			DHT11_Read_Data(&temperature,&humidity);		//读取温湿度值					    
			LCD_ShowNum(60+40,150,temperature,2,16);		//显示温度	   		   
			LCD_ShowNum(60+40,170,humidity,2,16);			//显示湿度	 	   
		}				   
	 	delay_ms(10);
		t++;

			if(i==0){
      printf("测距开始\n");
				i++;
			}
			 GPIO_SetBits(GPIOA,GPIO_Pin_5);  //拉高电平
			 Delay(20);  //延时20个微秒
		
			 GPIO_ResetBits(GPIOA,GPIO_Pin_5); 

       TIM3->CNT=0;  //TIM3的计数器清0

       while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 0); //等待ECHO的高电平
		
       
       TIM_Cmd(TIM3,ENABLE);  //运行TIM3进行计时
       
			while((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 1) && (TIM3->CNT < TIM3->ARR-10));
			 
			  TIM_Cmd(TIM3,DISABLE);  
       		
        count=TIM3->CNT;
        
		
			  	
			 
				beep_Init();      //初始化蜂鸣器
			  LED_Init();				//初始化与LED连接的硬件接口
			  LED0=1;
        LED1=1;		
				distance=ChangeDistance(count);
				LCD_ShowNum(130,190,distance,5,16);		
			  printf(" 当前距离为：%.2f cm\n",distance);
				printf(" 当前温度为：%d C\n",temperature);
				printf(" 当前湿度为：%d %%\n",humidity);
				printf("\n");
				if(distance<50){
						LED0=0;
						GPIOB ->ODR   |= (1 << 8); 			//PB.8 输出高  蜂鸣器开
				}
				else{
						LED1=0;
					  GPIOB ->ODR   &= ~(1 << 8);     //PB.8 输出低  蜂鸣器关
				}
		
				POINT_COLOR=BLUE;
		
				POINT_COLOR=RED;
										    		
			  Delay(50000); 
				Delay(50000);
				Delay(50000);
				
				
       
	 }
 }

void Delay(unsigned short int time)  //粗略的延时函数
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