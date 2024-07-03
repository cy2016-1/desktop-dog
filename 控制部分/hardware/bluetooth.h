#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

void Bluetooth_Init(void);
extern uint8_t LY_Biaozhi;
extern char LY_JS[];
void Sendbyte(uint8_t byte);
void SendArry(uint8_t *Arr,uint16_t num);
void SendString(char *string);
void SendNum(uint32_t num,uint8_t leng);
void LY_Sprintf(char *format,...);
uint8_t Get_LYBZ(void);
uint8_t Get_LYSJ(void);

#endif
