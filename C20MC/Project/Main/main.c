#include "main.h"

int count_test=0;
uint16_t receive_buff[256];
int main()
{ 
	Timing_Init();
	LED_GPIO_Init();
	read_test();
	UART_Init();
	TIM3_Int_Init(999,8999);
	EXTIX_Init();
	KEY_Init();

	while(1)
	{
//				if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13)==1)	 
//		{
//			LED_ON;
//			delay_ms(1000);
		
//			GPIOB->BSRRL = GPIO_Pin_8;
		
		//GPIO_SetBits(GPIOB,GPIO_Pin_8);
		//delay_ms(1000);
		//GPIO_ResetBits(GPIOB,GPIO_Pin_8);
//		
//		GPIOB->BSRRH = GPIO_Pin_8;
//		delay_us(500);
//		test_for_baby = read_result;
////		}
////		else

//		GPIO_SetBits(GPIOD,GPIO_Pin_12);
//		test_for_baby = read_result;
//		LED_ON;
//		delay_ms(1000);
//			GPIO_ResetBits(GPIOD,GPIO_Pin_12);
//		test_for_baby = read_result;
////		//LED_OFF;

//		USART_SendData(USART2,0x33);
//    USART2->DR = 0X67;
		printf("Hello World!\r\n");
		delay_ms(1000);
		
			//printf("%s\r\n",receive_buff);

		delay_ms(1000);
   
		
	}
}

