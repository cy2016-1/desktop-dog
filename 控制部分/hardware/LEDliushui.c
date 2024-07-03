#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define LED1(x)		GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)(x))
#define LED2(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_0, (BitAction)(x))
#define LED3(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction)(x))
#define LED4(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)(x))
#define LED5(x)		GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)(x))
#define LED6(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_13, (BitAction)(x))
#define LED7(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_14, (BitAction)(x))
#define LED8(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_15, (BitAction)(x))

void LEDLiu_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	LED1(1);
	LED2(1);
	LED3(1);
	LED4(1);
	LED5(1);
	LED6(1);
	LED7(1);
	LED8(1);
}

void Quanliang(void)
{
	LED1(0);
	LED2(0);
	LED3(0);
	LED4(0);
	LED5(0);
	LED6(0);
	LED7(0);
	LED8(0);
}

void Quanmie(void)
{
	LED1(1);
	LED2(1);
	LED3(1);
	LED4(1);
	LED5(1);
	LED6(1);
	LED7(1);
	LED8(1);
}

void Liushui(void)
{
	Quanmie();
	LED1(0);
	Delay_ms(500);
	LED1(1);
	LED2(0);
	Delay_ms(500);
	LED2(1);
	LED3(0);
	Delay_ms(500);
	LED3(1);
	LED4(0);
	Delay_ms(500);
	LED4(1);
	LED5(0);
	Delay_ms(500);
	LED5(1);
	LED6(0);
	Delay_ms(500);
	LED6(1);
	LED7(0);
	Delay_ms(500);
	LED7(1);
	LED8(0);
	Delay_ms(500);
	LED8(1);
}

void Jiaoti(void)
{
	Quanmie();
	LED1(0);
	LED8(0);
	Delay_ms(500);
	LED1(1);
	LED8(1);
	LED2(0);
	LED7(0);
	Delay_ms(500);
	LED2(1);
	LED7(1);
	LED3(0);
	LED6(0);
	Delay_ms(500);
	LED3(1);
	LED6(1);
	LED4(0);
	LED5(0);
	Delay_ms(500);
	LED4(1);
	LED5(1);
}
