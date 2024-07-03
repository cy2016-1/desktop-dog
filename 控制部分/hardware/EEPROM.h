#ifndef __EEPROM_H
#define __EEPROM_H

void EEPROM_Init(void);
void AT24C02_WriteByte(uint8_t WordAddress,uint8_t Data);
unsigned char AT24C02_ReadByte(uint8_t WordAddress);

#endif
