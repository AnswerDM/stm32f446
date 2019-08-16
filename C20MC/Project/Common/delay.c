#include "delay.h"


/********2019-08-16 DM delay test pass**********/


static uint32_t usTicks = 0;
volatile uint32_t sysTickUptime;
volatile uint16_t loopCnt;
uint8_t loopFlag = 0;

void Timing_Init(void)
{
	RCC_ClocksTypeDef get_rcc_clock;	
	RCC_GetClocksFreq(&get_rcc_clock);
	usTicks = get_rcc_clock.SYSCLK_Frequency / 1000000;
	SysTick_Config(get_rcc_clock.SYSCLK_Frequency / 1000);
}


uint32_t micros(void)
{
	register uint32_t ms, cycle_cnt;
	do{
		ms = sysTickUptime;
		cycle_cnt = SysTick->VAL;
	}
	while(ms != sysTickUptime);

	return (ms * 1000) + (usTicks * 1000 - cycle_cnt) / usTicks;
}

void delay_us(uint32_t time)
{
	uint32_t temp;
	temp = micros();
	
	while(micros()-temp < time);
}

void delay_ms(uint32_t time)
{
		delay_us(1000 * time);
}



  