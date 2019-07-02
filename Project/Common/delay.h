#ifndef __DELAY_H
#define __DELAY_H	 



#include "stm32f4xx.h"

//void delay_ms(__IO uint32_t nTime);
//void TimingDelay_Decrement(void);
void timing_init(void);
uint32_t micros(void);
void delay_us(uint32_t time);
void delay_ms(uint32_t time);


#endif


