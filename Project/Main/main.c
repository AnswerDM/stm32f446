#include "main.h"

int count_test;
u8  test_for_baby;

int main()
{
	static int get_sysclk;
		static int sys_test=0;
	static long int RCC_value;
  static long int time1;
	static long int time2;
	static  long int time;
		//RCC_Configuration();
	RCC_ClocksTypeDef get_rcc_clock;		//获取系统时钟状态
	RCC_GetClocksFreq(&get_rcc_clock);

	//get_sysclk = get_rcc_clock.SYSCLK_Frequency;
	get_sysclk = get_rcc_clock.PCLK1_Frequency;


	timing_init();
	LED_GPIO_Init();
	read_test();
	UART_Init();
	TIM3_Int_Init(9999,8999);
	EXTIX_Init();
	KEY_Init();
	
	time1=micros();
		
		delay_ms(1000);
		time2 =micros();
		time = time2 - time1;
//add iic test
	while(1)
	{
//				if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13)==1)	 
//		{
//			LED_ON;
//			delay_ms(1000);
//		GPIOB->BSRRH = GPIO_Pin_7;
		delay_ms(1000);
		GPIOB->BSRRH = GPIO_Pin_7;
		test_for_baby = read_result;
//		}
//		else

		GPIO_SetBits(GPIOD,GPIO_Pin_12);
		test_for_baby = read_result;
//		LED_ON;
		delay_ms(1000);
			GPIO_ResetBits(GPIOD,GPIO_Pin_12);
		test_for_baby = read_result;
//		//LED_OFF;

		//USART_SendData(USART2,0x33);


		
	}
}

