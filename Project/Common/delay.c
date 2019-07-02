#include "delay.h"


static uint32_t usTicks = 0;
volatile uint32_t sysTickUptime;
volatile uint16_t loopCnt;
uint8_t loopFlag = 0;

//��ʱ/��ʱ��ʼ��
void timing_init(void)
{
	RCC_ClocksTypeDef get_rcc_clock;		//��ȡϵͳʱ��״̬
	RCC_GetClocksFreq(&get_rcc_clock);
	usTicks = get_rcc_clock.SYSCLK_Frequency / 1000000;
	SysTick_Config(get_rcc_clock.SYSCLK_Frequency / 1000);
}


//��ȡ�Գ�ʼ����ʼ��ʱ��
//return **us
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

//��ʱ���� us
void delay_us(uint32_t time)
{
	uint32_t temp;
	temp = micros();
	
	while(micros()-temp < time);
}


//��ʱ���� ms
void delay_ms(uint32_t time)
{
		delay_us(1000 * time);
}


  