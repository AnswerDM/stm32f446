#ifndef __EXTI_H
#define __EXTI_H

#include "stm32f4xx.h"
void KEY_Init(void);
void EXTIX_Init(void);
#define KEY GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)	//PE3 

#endif
