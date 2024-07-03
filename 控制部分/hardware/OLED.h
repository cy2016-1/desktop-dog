#ifndef __OLED_H
#define __OLED_H

void OLED_WriteCommand(uint8_t Command); 
void OLED_WriteData(uint8_t Data);
void OLED_Init(void);
void OLED_setweizhi(uint8_t x,uint8_t p);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t x,uint8_t p,char cha);
void OLED_ShowString(uint8_t x,uint8_t p,char*str);
void OLED_ShowPic(uint8_t x,uint8_t p,uint8_t kuan,uint8_t gao,const uint8_t *pic);
void OLED_ShowNum(uint8_t x,uint8_t p,uint32_t num,uint8_t len);

#endif
