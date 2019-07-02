#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"

void LED_GPIO_Init(void);
void read_test(void);
#define LED_ON GPIO_SetBits(GPIOB,GPIO_Pin_7);

#define LED_OFF GPIO_ResetBits(GPIOB,GPIO_Pin_7);

#define read_result ((GPIOB->IDR)& GPIO_Pin_4)>>4

#endif


