#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Delay.h"

void Duoji_Init(void)
{
	PWM_Init();
}

void Duojione(float jiaodu)
{
	PWM_Setcompare1(jiaodu/180*2000+500);
}

void Duojitwo(float jiaodu)
{
	PWM_Setcompare2(jiaodu/180*2000+500);
}

void Duojitre(float jiaodu)
{
	PWM_Setcompare3(jiaodu/180*2000+500);
}

void Duojifor(float jiaodu)
{
	PWM_Setcompare4(jiaodu/180*2000+500);
}

void Qianjin(void)
{
	Duojione(45);
	Duojitre(105);
	Delay_ms(300);
	Duojitwo(45);
	Duojifor(115);
	Delay_ms(300);
	Duojione(90);
	Duojitre(60);
	Delay_ms(300);
	Duojitwo(90);
	Duojifor(70);
	Delay_ms(300);
	Duojitwo(135);
	Duojifor(25);
	Delay_ms(300);
	Duojione(135);
	Duojitre(15);
	Delay_ms(300);
	Duojitwo(90);
	Duojifor(70);
	Delay_ms(300);
	Duojione(90);
	Duojitre(60);
	Delay_ms(300);
}

void Houtui(void)
{
	Duojione(135);
	Duojitre(15);
	Delay_ms(300);
	Duojitwo(135);
	Duojifor(25);
	Delay_ms(300);
	Duojione(90);
	Duojitre(60);
	Delay_ms(300);
	Duojitwo(90);
	Duojifor(70);
	Delay_ms(300);
	Duojitwo(45);
	Duojifor(115);
	Delay_ms(300);
	Duojione(45);
	Duojitre(105);
	Delay_ms(300);
	Duojitwo(90);
	Duojifor(70);
	Delay_ms(300);
	Duojione(90);
	Duojitre(60);
	Delay_ms(300);
}

void Zuozhuan(void)
{
	Duojitwo(135);
	Duojifor(115);
	Delay_ms(300);
	Duojione(45);
	Duojitre(15);
	Delay_ms(300);
	Duojitwo(90);
	Duojifor(70);
	Delay_ms(300);
	Duojione(90);
	Duojitre(60);
	Delay_ms(300);
}

void Youzhuan(void)
{
	Duojione(45);
	Duojitre(15);
	Delay_ms(300);
	Duojitwo(135);
	Duojifor(115);
	Delay_ms(300);
	Duojione(90);
	Duojitre(60);
	Delay_ms(300);
	Duojitwo(90);
	Duojifor(70);
	Delay_ms(300);
}

void Qianpa(void)
{
	Duojione(135);
	Duojitwo(45);
	Delay_ms(1000);
	Duojione(90);
	Duojitwo(90);
}

void Houzuo(void)
{
	Duojitre(105);
	Duojifor(25);
	Delay_ms(1000);
	Duojitre(60);
	Duojifor(70);
}

void Yaohuang(void)
{
	Duojione(45);
	Duojitwo(135);
	Duojitre(105);
	Duojifor(25);
	Delay_ms(300);
	Duojione(135);
	Duojitwo(45);
	Duojitre(15);
	Duojifor(115);
	Delay_ms(300);
	Duojione(90);
	Duojitwo(90);
	Duojitre(60);
	Duojifor(70);
}

void lizheng(void)
{
	Duojione(90);
	Duojitwo(90);
	Duojitre(60);
	Duojifor(70);
}
