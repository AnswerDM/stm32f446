#include "UART.h"

void UART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART1ʱ��
	
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;    // ??9 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  // ???????
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP ;// ????????? ????
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //???
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz ; // ??

	GPIO_Init(GPIOA , &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;    // ??9 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  // ???????
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP ;// ????????? ????
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //???
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz ; // ??

  GPIO_Init(GPIOA , &GPIO_InitStructure);

	
   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = 115200;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
	
  USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���1 
	
  USART_ClearFlag(USART2, USART_FLAG_TC);
//	

 	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����


	
}
int fputc(int ch, FILE *f)
{
USART_SendData(USART2, (uint8_t) ch);

while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
return ch;
}


