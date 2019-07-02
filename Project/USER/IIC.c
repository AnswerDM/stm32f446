#include "IIC.h"

/*
	Ӧ��˵����
	��gpioģ��i2c����
	�ڷ���I2C�豸ǰ�����ȵ��� i2c_CheckDevice() ���I2C�豸�Ƿ��������ú���������GPIO
*/


/* ����I2C�������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����4�д��뼴������ı�SCL��SDA������ */

#define RCC_I2C_PORT 	RCC_AHB1Periph_GPIOB		/* GPIO�˿�ʱ�� */

#define PORT_I2C_SCL	GPIOB			/* GPIO�˿� */
#define PIN_I2C_SCL		GPIO_Pin_6		/* GPIO���� */

#define PORT_I2C_SDA	GPIOB			/* GPIO�˿� */
#define PIN_I2C_SDA		GPIO_Pin_7		/* GPIO���� */

#define I2C_SCL_PIN		GPIO_Pin_6			/* ���ӵ�SCLʱ���ߵ�GPIO */
#define I2C_SDA_PIN		GPIO_Pin_7			/* ���ӵ�SDA�����ߵ�GPIO */

/* �����дSCL��SDA�ĺ� */
#define I2C_SCL_1()  PORT_I2C_SCL->BSRRL = I2C_SCL_PIN				/* SCL = 1 */
#define I2C_SCL_0()  PORT_I2C_SCL->BSRRH = I2C_SCL_PIN				/* SCL = 0 */

#define I2C_SDA_1()  PORT_I2C_SDA->BSRRL = I2C_SDA_PIN				/* SDA = 1 */
#define I2C_SDA_0()  PORT_I2C_SDA->BSRRH = I2C_SDA_PIN				/* SDA = 0 */

#define I2C_SDA_READ()  ((PORT_I2C_SDA->IDR & I2C_SDA_PIN) != 0)	/* ��SDA����״̬ */
#define I2C_SCL_READ()  ((PORT_I2C_SCL->IDR & I2C_SCL_PIN) != 0)	/* ��SCL����״̬ */

/*
*********************************************************************************************************
*	�� �� ��: IIC_Init
*	����˵��: ����I2C���ߵ�GPIO������ģ��IO�ķ�ʽʵ��
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_I2C_PORT, ENABLE);	/* ��GPIOʱ�� */
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	/* ��©���ģʽ */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Pin = PIN_I2C_SCL;
	GPIO_Init(PORT_I2C_SCL, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = PIN_I2C_SDA;
	GPIO_Init(PORT_I2C_SDA, &GPIO_InitStructure);

//	i2c_bus_repair();
	/* ��һ��ֹͣ�ź�, ��λI2C�����ϵ������豸������ģʽ */
	i2c_Stop();
	i2c_bus_repair();
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_Delay
*	����˵��: I2C����λ�ӳ٣����400KHz
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void i2c_Delay(void)
{
	uint8_t i;

	/*��
		CPU��Ƶ168MHzʱ�����ڲ�Flash����, MDK���̲��Ż�����̨ʽʾ�����۲Ⲩ�Ρ�
		ѭ������Ϊ5ʱ��SCLƵ�� = 1.78MHz (����ʱ: 92ms, ��д������������ʾ����̽ͷ���ϾͶ�дʧ�ܡ�ʱ��ӽ��ٽ�)
		ѭ������Ϊ10ʱ��SCLƵ�� = 1.1MHz (����ʱ: 138ms, ���ٶ�: 118724B/s)
		ѭ������Ϊ30ʱ��SCLƵ�� = 440KHz�� SCL�ߵ�ƽʱ��1.0us��SCL�͵�ƽʱ��1.2us

		��������ѡ��2.2Kŷʱ��SCL������ʱ��Լ0.5us�����ѡ4.7Kŷ����������Լ1us

		ʵ��Ӧ��ѡ��400KHz���ҵ����ʼ���
	*/
	for (i = 0; i < 6; i++);
}

static void i2c_Delay_2(void)
{
	uint8_t i;

	/*��
		CPU��Ƶ168MHzʱ�����ڲ�Flash����, MDK���̲��Ż�����̨ʽʾ�����۲Ⲩ�Ρ�
		ѭ������Ϊ5ʱ��SCLƵ�� = 1.78MHz (����ʱ: 92ms, ��д������������ʾ����̽ͷ���ϾͶ�дʧ�ܡ�ʱ��ӽ��ٽ�)
		ѭ������Ϊ10ʱ��SCLƵ�� = 1.1MHz (����ʱ: 138ms, ���ٶ�: 118724B/s)
		ѭ������Ϊ30ʱ��SCLƵ�� = 440KHz�� SCL�ߵ�ƽʱ��1.0us��SCL�͵�ƽʱ��1.2us

		��������ѡ��2.2Kŷʱ��SCL������ʱ��Լ0.5us�����ѡ4.7Kŷ����������Լ1us

		ʵ��Ӧ��ѡ��400KHz���ҵ����ʼ���
	*/
	for (i = 0; i < 1; i++);
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_Start
*	����˵��: CPU����I2C���������ź�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Start(void)
{
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź� */
	I2C_SDA_1();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_0();
	i2c_Delay();
	
	I2C_SCL_0();
	i2c_Delay();
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_Start
*	����˵��: CPU����I2C����ֹͣ�ź�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Stop(void)
{
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */
	I2C_SDA_0();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_1();
	i2c_Delay();
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_SendByte
*	����˵��: CPU��I2C�����豸����8bit����
*	��    ��:  _ucByte �� �ȴ����͵��ֽ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	/* �ȷ����ֽڵĸ�λbit7 */
	for (i = 0; i < 8; i++)
	{
		if (_ucByte & 0x80)
		{
			I2C_SDA_1();
		}
		else
		{
			I2C_SDA_0();
		}
		i2c_Delay_2();
		I2C_SCL_1();
		i2c_Delay();
		I2C_SCL_0();
		if (i == 7)
		{
			 I2C_SDA_1(); // �ͷ�����
		}
		_ucByte <<= 1;	/* ����һ��bit */
		i2c_Delay_2();
	}
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_ReadByte
*	����˵��: CPU��I2C�����豸��ȡ8bit����
*	��    ��:  ��
*	�� �� ֵ: ����������
*********************************************************************************************************
*/
uint8_t i2c_ReadByte(void)
{
	uint8_t i;
	uint8_t value;

	/* ������1��bitΪ���ݵ�bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		I2C_SCL_1();
		i2c_Delay();
		if (I2C_SDA_READ())
		{
			value++;
		}
		I2C_SCL_0();
		i2c_Delay();
	}
	return value;
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_WaitAck
*	����˵��: CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
*	��    ��:  ��
*	�� �� ֵ: ����0��ʾ��ȷӦ��1��ʾ��������Ӧ
*********************************************************************************************************
*/
uint8_t i2c_WaitAck(void)
{
	uint8_t re;

	I2C_SDA_1();	/* CPU�ͷ�SDA���� */
	i2c_Delay();
	I2C_SCL_1();	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	i2c_Delay();
	if (I2C_SDA_READ())	/* CPU��ȡSDA����״̬ */
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	I2C_SCL_0();
	i2c_Delay();
	return re;
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_Ack
*	����˵��: CPU����һ��ACK�ź�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Ack(void)
{
	I2C_SDA_0();	/* CPU����SDA = 0 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU����1��ʱ�� */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
	I2C_SDA_1();	/* CPU�ͷ�SDA���� */
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_NAck
*	����˵��: CPU����1��NACK�ź�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_NAck(void)
{
	I2C_SDA_1();	/* CPU����SDA = 1 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU����1��ʱ�� */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_CheckDevice
*	����˵��: ���I2C�����豸��CPU�����豸��ַ��Ȼ���ȡ�豸Ӧ�����жϸ��豸�Ƿ����
*	��    ��:  _Address���豸��I2C���ߵ�ַ
*	�� �� ֵ: ����ֵ 0 ��ʾ��ȷ�� ����1��ʾδ̽�⵽
*********************************************************************************************************
*/
uint8_t i2c_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;

	if (I2C_SDA_READ() && I2C_SCL_READ())
	{
		i2c_Start();		/* ���������ź� */

		/* �����豸��ַ+��д����bit��0 = w�� 1 = r) bit7 �ȴ� */
		i2c_SendByte(_Address | I2C_WR);
		ucAck = i2c_WaitAck();	/* ����豸��ACKӦ�� */

		i2c_Stop();			/* ����ֹͣ�ź� */

		return ucAck;
	}
	return 1;	/* I2C�����쳣 */
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_bus_repair
*	����˵��: ���i2c���ߣ����޸�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_bus_repair(void)
{
	while(!I2C_SDA_READ())
	{
		i2c_Delay();
		I2C_SCL_1();
		i2c_Delay();
		I2C_SCL_0();
	}
	i2c_Delay();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_0();
	i2c_Delay();
	I2C_SDA_1();
}






void I2C_WriteByte(unsigned char id,unsigned char write_address,unsigned char byte)
{
	i2c_Start();
	
	i2c_SendByte(id | I2C_WR);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	i2c_SendByte((uint8_t)write_address);
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	i2c_SendByte(byte);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
		
	i2c_Stop();
	
	cmd_fail:
	i2c_Stop();
	
}

unsigned char I2C_ReadByte(unsigned char  id, unsigned char read_address)
{
	uint8_t data;
	
	i2c_Start();
	
	i2c_SendByte(id | I2C_WR);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	i2c_SendByte(read_address);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	i2c_Start();
	
	i2c_SendByte(id | I2C_RD);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	data = i2c_ReadByte();
	
	i2c_NAck();
	
	i2c_Stop();
	
	return data;
	
	cmd_fail:
	
	i2c_Stop();

	return data;
}



void I2C_Write2Byte_HignLow(unsigned char id,unsigned char write_address,uint16_t data16)
{
	i2c_Start();
	
	i2c_SendByte(id | I2C_WR);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	i2c_SendByte((uint8_t)write_address);
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	i2c_SendByte((uint8_t)(data16 >> 8));
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	i2c_SendByte((uint8_t)data16);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	i2c_Stop();
	
	cmd_fail:
	i2c_Stop();
}

void I2C_Write2Byte_LowHigh(unsigned char id,unsigned char write_address,uint16_t data16)
{
	i2c_Start();
	
	i2c_SendByte(id | I2C_WR);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	i2c_SendByte((uint8_t)write_address);
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	i2c_SendByte((uint8_t)data16);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	i2c_SendByte((uint8_t)(data16 >> 8));
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	i2c_Stop();
	
	cmd_fail:
	i2c_Stop();
}

u16 I2C_Read2Byte_HighLow(unsigned char  id, unsigned char read_address)
{
	uint16_t data16;
	uint8_t data_high, data_low;
	
	i2c_Start();
	
	i2c_SendByte(id | I2C_WR);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	i2c_SendByte(read_address);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	i2c_Start();
	
	i2c_SendByte(id | I2C_RD);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	data_high = i2c_ReadByte();
	
	i2c_Ack();
	
	data_low = i2c_ReadByte();
	
	i2c_NAck();
	
	i2c_Stop();
	
	data16=((u16)data_low)|((u16)(data_high<<8));

	return data16;
	
	cmd_fail:
	
	i2c_Stop();
	
	data16=((u16)data_low)|((u16)(data_high<<8));

	return data16;
}


u16 I2C_Read2Byte_LowHigh(unsigned char  id, unsigned char read_address)
{
	uint16_t data16;
	uint8_t data_high, data_low;
	
	i2c_Start();
	
	i2c_SendByte(id | I2C_WR);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	i2c_SendByte(read_address);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	i2c_Start();
	
	i2c_SendByte(id | I2C_RD);
	
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* iic������Ӧ�� */
	}
	
	data_low = i2c_ReadByte();
	
	i2c_Ack();
	
	data_high = i2c_ReadByte();
	
	i2c_NAck();
	
	i2c_Stop();
	
	data16=((u16)data_low)|((u16)(data_high<<8));

	return data16;
	
	cmd_fail:
	
	i2c_Stop();
	
	data16=((u16)data_low)|((u16)(data_high<<8));

	return data16;
}




