#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
uint8_t LY_Data;
uint8_t LY_Biaozhi;

void Bluetooth_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
}

void Sendbyte(uint8_t byte)
{
	USART_SendData(USART1,byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}

void SendArry(uint8_t *Arry,uint16_t num)
{
	uint16_t i;
	for(i=0;i<num;i++)
	{
		Sendbyte(Arry[i]);
	}
}

void SendString(char *string)
{
	uint16_t i;
	for(i=0;string[i]!=0;i++)
	{
		Sendbyte(string[i]);
	}
}

uint32_t LYpow(uint32_t X,uint32_t Y)
{
	uint32_t i=1;
	while(Y--)
	{
		i*=X;
	}
	return i;
}

void SendNum(uint32_t num,uint8_t leng)
{
	uint8_t i;
	for(i=0;i<leng;i++)
	{
		Sendbyte(num/LYpow(10,leng-i-1)%10+'0');
	}
}

int fputc(int ly,FILE *f)
{
	Sendbyte(ly);
	return ly;
}

void LY_Sprintf(char *format,...)
{
	char string[100];
	va_list arg;
	va_start(arg,format);
	vsprintf(string,format,arg);
	va_end(arg);
	SendString(string);
}

uint8_t Get_LYBZ(void)
{
	if(LY_Biaozhi==1)
	{
		LY_Biaozhi=0;
		return 1;
	}
	return 0;
}

uint8_t Get_LYSJ(void)
{
	return LY_Data;
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		LY_Data=USART_ReceiveData(USART1);
		LY_Biaozhi=1;
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}
