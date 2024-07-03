#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include <string.h>

#define   L1     262-1//低调 do 的频率
#define   L2     294-1//低调 re 的频率
#define   L3     330-1//低调 mi 的频率
#define   L4     350-1//低调 fa 的频率
#define   L5     392-1//低调 sol 的频率
#define   L6     440-1//低调 la 的频率
#define   L7     494-1//低调 si 的频率
                                               
#define   M1     524-1//中调 do 的频率
#define   M2     588-1//中调 re 的频率
#define   M3     660-1//中调 mi 的频率
#define   M4     700-1//中调 fa 的频率
#define   M5     784-1//中调 sol 的频率
#define   M6     880-1//中调 la 的频率
#define   M7     988-1//中调 si 的频率
 
#define   H1     1048-1//高调 do 的频率
#define   H2     1176-1//高调 re 的频率
#define   H3     1320-1//高调 mi 的频率
#define   H4     1480-1//高调 fa 的频率
#define   H5     1640-1//高调 sol 的频率
#define   H6     1760-1//高调 la 的频率
#define   H7     1976-1//高调 si 的频率
 
#define   S      0//不发音

/*
该数组用于储存回家的乐谱，
在后续播放函数中调用改变频率函数依次根据数组中的数字来改变震动频率和占空比，
以此达到通过蜂鸣器播放回家的目的。
*/
uint16_t mus_go[]={
	S,S,S,S,M2,M2,M3,M3,M3,M3,L5,L5,L5,L5,S,S,S,S,M2,M2,M3,M3,M3,M3,L5,L5,L5,L5,
	S,S,S,S,M5,M5,M6,M6,M6,M6,M6,M6,M3,M1,M2,M2,M2,M2,M2,M2,M2,M2,M2,M2,M2,M2,M2,
	M2,M2,M2,M2,M2,S,S,S,S,M2,M2,M3,M3,M3,M3,L5,L5,L5,L5,S,S,S,S,M2,M2,M3,M3,M3,M3,
	L5,L5,L5,L5,S,S,S,S,M5,M5,M6,M6,M6,M6,M6,M6,M3,M1,M2,M2,M2,M2,M2,M2,M2,M2,M2,M2,
	M2,M2,M2,M2,M6,M6,M7,M7,H1,H1,H1,H1,M7,M7,H1,H1,H1,H1,M6,M6,M7,M7,H1,H1,H1,
	H1,H1,H1,M7,M7,H1,H1,H1,H1,H1,H1,S,M3,M6,M7,H1,H1,H1,H1,M7,H1,H2,H3,H3,H3,H2,H2,
	H1,H1,M7,M7,M7,M7,M7,M7,S,S,M3,M3,M6,M6,M7,M7,H1,H1,H1,H1,M7,M7,H1,H1,H1,H1,M6,M6,
	M7,M7,H1,H1,M7,M7,M7,M7,M6,M5,M3,M2,L1,L1,L1,L1,S,M1,M6,M6,M5,M5,M6,M6,M3,M3,M3,M3,
	M3,M3,M1,M1,M3,M3,M2,M2,M2,M2,M2,M2,S,S,S,S,S,S,M3,M3,M6,M6,M7,M7,H1,H1,H1,H1,M7,M7,
	H1,H1,H1,H1,M6,M6,M7,M7,H1,H1,M7,M7,M7,M7,M6,M5,M3,M2,L1,L1,L1,L1,S,M1,M6,M6,M5,M5,
	M4,M4,M3,M3,M3,M3,M2,M2,M1,M1,M2,M2,M2,M2,M2,M2,S,S,M5,M4,M4,M3,M3,L2,L2,M3,M3,M2,M1,M1,
	M1,M1,M1,M1,M1,M1,M1,M1,M1,M1,S,S,S,S,S,S,S,S
};

/*
该数组用于储存天空之城的乐谱，
在后续播放函数中调用改变频率函数依次根据数组中的数字来改变震动频率和占空比，
以此达到通过蜂鸣器播放天空之城的目的。
*/
uint16_t mus_tian[]={
		S,S,S,S,S,S,M6,M7,H1,H1,M7,H1,H1,H3,
		M7,M7,M7,M7,M7,M7,M3,M3,M6,M6,M5,M6,M6,H1,H1,
		M5,M5,M5,M5,M5,M5,M3,M3,M4,M4,M3,M4,M4,H1,H1,
		M3,M3,M3,M3,S,H1,H1,H1,M7,M7,M4,M4,M4,M7,M7,M7,
		M7,M7,M7,M6,M7,H1,H1,M7,H1,H1,H3,H3,
		M7,M7,M7,M7,M7,M7,M3,M3,M6,M6,M5,M6,M6,H1,H1,
		M5,M5,M5,M5,M5,M5,M2,M3,M4,M4,H1,M7,H1,H1,H1,
		H2,H2,H3,H1,H1,H1,H1,H1,H1,M7,M6,M6,M7,M7,M5,M5,
		M6,M6,M6,M6,M6,M6,H1,H2,H3,H3,H2,H3,H3,H5,H5,
		H2,H2,H2,H2,H2,H2,M5,M5,H1,H1,M7,H1,H1,H3,H3,
		H3,H3,H3,H3,H3,H3,H3,H3,M6,M7,H1,H1,M7,M7,H2,H2,
		H1,H1,M5,M5,M5,M5,M5,H4,H4,H3,H3,H2,H2,H1,H1,
		H3,H3,H3,H3,H3,H3,H3,H3,H6,H6,H6,H6,H5,H5,H6,H6,
		H3,H2,H1,H1,H1,H1,S,H1,H2,H2,H1,H2,H2,H2,H5,H5,
		H3,H3,H3,H3,H3,H3,H3,H3,H6,H6,H6,H6,H5,H5,H5,H5,
		H3,H2,H1,H1,H1,H1,S,H1,H2,H2,H1,H2,H2,H2,M7,M7,
		M6,M6,M6,M6,M6,M6,M6,M7
};

void Button_Init(void)//蜂鸣器以及定时器三初始化
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=1;
	TIM_TimeBaseInitStructure.TIM_Prescaler=72-1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);
}

void set_voice(uint16_t h)//其中h为输入的频率
{
	if(h==0)
	{
		TIM_SetAutoreload(TIM3,1);
		TIM_SetCompare1(TIM3,0);
	}
	else
	{
		TIM_SetAutoreload(TIM3,1000000/h);
		TIM_SetCompare1(TIM3,1000000/h/6);
	}
}

void bo_gohome(void)//播放回家的函数
{
	for(int i=0;i<sizeof(mus_go)/sizeof(mus_go[0]);i++)
	{
		set_voice(mus_go[i]);
		Delay_ms(200);
	}
	set_voice(0);
}

void bo_tianko(void)//播放天空之城的函数
{
	for(int i=0;i<sizeof(mus_tian)/sizeof(mus_tian[0]);i++)
	{
		set_voice(mus_tian[i]);
		Delay_ms(400);
	}
	set_voice(0);
}

void stop(void)
{
	set_voice(0);
}
