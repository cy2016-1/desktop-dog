#include "stm32f10x.h"
#include "MyI2C.h"
#include "OLED_Front.h"
#include "Delay.h"

void OLED_WriteCommand(uint8_t Command)
{
	MyI2C_Start();
	MyI2C_SendByte(0X78);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(0X00);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Command);
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}

/**
  * @brief  OLED写数据
  * @param  Data 要写入的数据
  * @retval 无
  */
void OLED_WriteData(uint8_t Data)
{
	MyI2C_Start();
	MyI2C_SendByte(0X78);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(0X40);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Data);
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}

void OLED_Init(void)
{
	MyI2C_Init();
	
	Delay_ms(100);
	
	OLED_WriteCommand(0xAE);	//关闭显示
	
	OLED_WriteCommand(0xD5);	//设置显示时钟分频比/振荡器频率
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);	//设置多路复用率
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);	//设置显示偏移
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//设置显示开始行
	
	OLED_WriteCommand(0xA1);	//设置左右方向，0xA1正常 0xA0左右反置
	
	OLED_WriteCommand(0xC8);	//设置上下方向，0xC8正常 0xC0上下反置

	OLED_WriteCommand(0xDA);	//设置COM引脚硬件配置
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//设置对比度控制
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//设置预充电周期
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//设置VCOMH取消选择级别
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//设置整个显示打开/关闭

	OLED_WriteCommand(0xA6);	//设置正常/倒转显示

	OLED_WriteCommand(0x8D);	//设置充电泵
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//开启显示

	Delay_ms(100);
}

void OLED_setweizhi(uint8_t x,uint8_t p)
{
	x+=2;
	OLED_WriteCommand(0x00|(x&0x0F));
	OLED_WriteCommand(0x10|((x&0xF0)>>4));
	OLED_WriteCommand(0xB0|p);
}

void OLED_Clear(void)
{
	for(uint8_t j=0;j<8;j++)
	{
		OLED_setweizhi(0,j);
		for(uint8_t i=0;i<128;i++)
		{
			OLED_WriteData(0x00);
		}
	}
}

void OLED_ShowChar(uint8_t x,uint8_t p,char cha)
{
	OLED_setweizhi(x,p);
	for(uint8_t i=0;i<8;i++)
	{
		OLED_WriteData(oledzi[cha-' '][i]);
	}
	OLED_setweizhi(x,p+1);
	for(uint8_t i=0;i<8;i++)
	{
		OLED_WriteData(oledzi[cha-' '][i+8]);
	}
}

void OLED_ShowString(uint8_t x,uint8_t p,char*str)
{
	for(uint8_t i=0;str[i]!='\0';i++)
	{
		OLED_ShowChar(x+i*8,p,str[i]);
	}
}

uint32_t OLED_Pow(uint32_t x,uint32_t y)
{
	uint32_t result=1;
	for(uint32_t i=0;i<y;i++)
	{
		result*=x;
	}
	return result;
}

void OLED_ShowNum(uint8_t x,uint8_t p,uint32_t num,uint8_t len)
{
	for(uint8_t i=0;i<len;i++)
	{
		OLED_ShowChar(x+i*8,p,num/OLED_Pow(10,len-i-1)%10+'0');
	}
}

void OLED_ShowPic(uint8_t x,uint8_t p,uint8_t kuan,uint8_t gao,const uint8_t *pic)
{
	for(uint8_t j=0;j<gao;j++)
	{
		OLED_setweizhi(x,p+j);
		for(uint8_t i=0;i<kuan;i++)
		{
			OLED_WriteData(pic[kuan*j+i]);
		}
	}
}
