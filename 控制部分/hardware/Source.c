#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//uint8_t IR_Dataflag;
//uint8_t IR_Repeatflag;
//uint8_t IR_Adress;
//uint8_t IR_Commond;
//uint8_t IR_Data[4];
//uint8_t IR_pData;
//uint8_t IR_State;
//uint8_t IR_Time;

uint32_t Hongjieshou;
uint8_t Hongbiaozhi;

void Source_Init(void)//中断初始化函数
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	EXTI_ClearITPendingBit(EXTI_Line14);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line=EXTI_Line14;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
}

uint8_t JiHigh(void)//记录高电平所持续的时间
{
	uint8_t tim;
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==1)
	{
		tim++;
		Delay_us(20);
		if(tim>=250)
		{
			return tim;
		}
	}
	return tim;
}

//void EXTI15_10_IRQHandler(void)
//{
//	uint8_t T=0,Ok=0,Num,Data=0;
//	while(1)
//	{
//		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==1)
//		{
//			T=JiHigh();
//			if(T>=250)
//			{
//				break;
//			}
//			if(T>=200&&T<250)
//			 {
//			 	Ok=1;   
//			 }
//			 else if(T>=60&&T<90)
//			 {
//			 	Data=1;  
//			 }
//			 else if(T>=10&&T<50)
//			 {
//			 	Data=0;   
//			 }
//			 if(Ok==1)
//			 {
//				Hongjieshou<<=1;
//				Hongjieshou+=Data;
//			 }
//			 if(Num>=32)
//			 {
//				Hongbiaozhi=1;
//				break;
//			 }
//		 }
//	}
//	Num++;
//	EXTI_ClearITPendingBit(EXTI_Line14);
//}

//uint32_t Getjieshou(void)
//{
//	return Hongjieshou;
//}

//uint8_t Getbiaozhi(void)
//{
//	return Hongbiaozhi;
//}
