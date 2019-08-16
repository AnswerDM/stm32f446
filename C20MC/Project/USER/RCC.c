#include "RCC.h"

void RCC_Configuration(void)
{
	
	RCC_DeInit();//将RCC设置为默认状态
  
  RCC_HSICmd(ENABLE);//使能HSI时钟    
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);//等待HSI使能成功
 
  RCC_HCLKConfig(RCC_SYSCLK_Div1);     
  RCC_PCLK2Config(RCC_HCLK_Div2);  
  RCC_PCLK1Config(RCC_HCLK_Div4);	
 
      
  //设置PLL时钟源及倍频倍数
	//void RCC_PLLConfig(RCC_PLLSource,PLLM,PLLN,PLLP,PLLQ,PLLR)
  RCC_PLLConfig(RCC_PLLSource_HSI,8,180,2,2,2);//配置PLL时钟源和倍频倍数，源HSI时钟除以2，倍数16倍  
  RCC_PLLCmd(ENABLE);//使能PLL
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET); //等待PLL使能成功 
  
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);//选择PLL时钟作为系统时钟   
   
  while(RCC_GetSYSCLKSource() != 0x08);//等待系统时钟设置完成，
	//  0x00:HSI    
  //  0x04:HSE   
  //  0x08:PLL 
}



