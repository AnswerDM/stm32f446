#ifndef __IIC_H
#define __IIC_H


#include "stm32f4xx.h"

#define I2C_WR	0		/* Ð´¿ØÖÆbit */
#define I2C_RD	1		/* ¶Á¿ØÖÆbit */

#define I2C2_SLAVE_ADDRESS7    0x8E

void i2c_Init(void);
void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(void);
uint8_t i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);
uint8_t i2c_CheckDevice(uint8_t _Address);

void i2c_bus_repair(void);
void I2C_WriteByte(unsigned char id,unsigned char write_address,unsigned char byte);
unsigned char I2C_ReadByte(unsigned char  id, unsigned char read_address);

void I2C_Write2Byte_HighLow(unsigned char id,unsigned char write_address,u16 data16);
u16 I2C_Read2Byte_HighLow(unsigned char  id, unsigned char read_address);
	
void I2C_Write2Byte_LowHigh(unsigned char id,unsigned char write_address,u16 data16);
u16 I2C_Read2Byte_LowHigh(unsigned char  id, unsigned char read_address);




#endif
