#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define AT24C02_ADDRESS		0xA0

void EEPROM_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)BitValue);
}

void EEPROM_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)BitValue);
}

uint8_t EEPROM_R_SDA(void)
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10);
	return BitValue;
}

void EEPROM_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
}

void EEPROM_Start(void)
{
	EEPROM_W_SDA(1);
	EEPROM_W_SCL(1);
	EEPROM_W_SDA(0);
	EEPROM_W_SCL(0);
}

void EEPROM_Stop(void)
{
	EEPROM_W_SDA(0);
	EEPROM_W_SCL(1);
	EEPROM_W_SDA(1);
}

void EEPROM_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i ++)
	{
		EEPROM_W_SDA(Byte & (0x80 >> i));
		EEPROM_W_SCL(1);
		EEPROM_W_SCL(0);
	}
}

uint8_t EEPROM_ReceiveByte(void)
{
	uint8_t i, Byte = 0x00;
	EEPROM_W_SDA(1);
	for (i = 0; i < 8; i ++)
	{
		EEPROM_W_SCL(1);
		if (EEPROM_R_SDA() == 1){Byte |= (0x80 >> i);}
		EEPROM_W_SCL(0);
	}
	return Byte;
}

void EEPROM_SendAck(uint8_t AckBit)
{
	EEPROM_W_SDA(AckBit);
	EEPROM_W_SCL(1);
	EEPROM_W_SCL(0);
}

uint8_t EEPROM_ReceiveAck(void)
{
	uint8_t AckBit;
	EEPROM_W_SDA(1);
	EEPROM_W_SCL(1);
	AckBit = EEPROM_R_SDA();
	EEPROM_W_SCL(0);
	return AckBit;
}

void AT24C02_WriteByte(uint8_t WordAddress,uint8_t Data)
{
	EEPROM_Start();
	EEPROM_SendByte(AT24C02_ADDRESS);
	EEPROM_ReceiveAck();
	EEPROM_SendByte(WordAddress);
	EEPROM_ReceiveAck();
	EEPROM_SendByte(Data);
	EEPROM_ReceiveAck();
	EEPROM_Stop();
}

uint8_t AT24C02_ReadByte(uint8_t WordAddress)
{
	uint8_t Data;
	EEPROM_Start();
	EEPROM_SendByte(AT24C02_ADDRESS);
	EEPROM_ReceiveAck();
	EEPROM_SendByte(WordAddress);
	EEPROM_ReceiveAck();
	EEPROM_Start();
	EEPROM_SendByte(AT24C02_ADDRESS|0x01);
	EEPROM_ReceiveAck();
	Data=EEPROM_ReceiveByte();
	EEPROM_SendAck(1);
	EEPROM_Stop();
	return Data;
}
