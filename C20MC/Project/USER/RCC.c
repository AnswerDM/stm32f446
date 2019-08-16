#include "RCC.h"

void RCC_Configuration(void)
{
	
	RCC_DeInit();//��RCC����ΪĬ��״̬
  
  RCC_HSICmd(ENABLE);//ʹ��HSIʱ��    
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);//�ȴ�HSIʹ�ܳɹ�
 
  RCC_HCLKConfig(RCC_SYSCLK_Div1);     
  RCC_PCLK2Config(RCC_HCLK_Div2);  
  RCC_PCLK1Config(RCC_HCLK_Div4);	
 
      
  //����PLLʱ��Դ����Ƶ����
	//void RCC_PLLConfig(RCC_PLLSource,PLLM,PLLN,PLLP,PLLQ,PLLR)
  RCC_PLLConfig(RCC_PLLSource_HSI,8,180,2,2,2);//����PLLʱ��Դ�ͱ�Ƶ������ԴHSIʱ�ӳ���2������16��  
  RCC_PLLCmd(ENABLE);//ʹ��PLL
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET); //�ȴ�PLLʹ�ܳɹ� 
  
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);//ѡ��PLLʱ����Ϊϵͳʱ��   
   
  while(RCC_GetSYSCLKSource() != 0x08);//�ȴ�ϵͳʱ��������ɣ�
	//  0x00:HSI    
  //  0x04:HSE   
  //  0x08:PLL 
}



