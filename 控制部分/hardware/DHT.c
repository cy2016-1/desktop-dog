#include "stm32f10x.h"                  // Device header
#include "Delay.h"
 
 
void DHT_Init_InPut(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
 
void DHT_Init_OutPut(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
 
void DHT_Start(void)
{
	DHT_Init_OutPut();
	GPIO_ResetBits(GPIOA, GPIO_Pin_11); 
	Delay_us(19000);
	GPIO_SetBits(GPIOA, GPIO_Pin_11); 
	Delay_us(20);
	DHT_Init_InPut();
}
 
uint16_t DHT_Scan(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11); 
}
 
uint16_t DHT_ReadBit(void)
{
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == RESET);
	Delay_us(40);
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == SET)
	{
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == SET);
		return 1;
	}
	else
	{
		return 0;
	}
}
 
uint16_t DHT_ReadByte(void)
{
	uint16_t i, data = 0;
	for(i = 0; i < 8; i++)
	{
		data <<= 1; 
		data |= DHT_ReadBit();
	}
	return data;
}
 
uint16_t DHT_ReadData(uint8_t buffer[5])
{
	uint16_t i =0;
	
	DHT_Start();
	if(DHT_Scan() == RESET)
	{
		while(DHT_Scan() == RESET);
		while(DHT_Scan() == SET);
		for(i = 0; i < 5; i++)
		{
			buffer[i] = DHT_ReadByte();
		}
		while(DHT_Scan() == RESET);
		DHT_Init_OutPut();
		GPIO_SetBits(GPIOA, GPIO_Pin_11);
		
		uint8_t check = buffer[0] + buffer[1] + buffer[2] + buffer[3];
		if(check != buffer[4])
		{
			return 1; 
		}
	}
	return  0;
}
