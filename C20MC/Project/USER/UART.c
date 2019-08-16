#include "UART.h"


/********2019-08-16 DM uart2 test pass**********/

void UART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); 
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;     
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP ;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ; 

	GPIO_Init(GPIOA , &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;    
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP ;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ; 

  GPIO_Init(GPIOA , &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 115200;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART2, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART2, ENABLE);  //使能串口1 
	
  USART_ClearFlag(USART2, USART_FLAG_TC);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断

  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	
}

int fputc(int ch, FILE *f)
{
	USART_SendData(USART2, (uint8_t) ch);

	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	return ch;
}


