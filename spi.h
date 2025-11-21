#include "LPC11xx.h"                    // Device header

#define SSPSR_RNE       (0x1<<2)
#define SSPSR_BSY       (0x1<<4)

void initSpi(void);
uint8_t spiSend(uint8_t data);
uint8_t serialFlashReadByte(uint32_t address);
uint8_t serialFlashRead(uint32_t address, uint8_t *data, uint16_t count);
uint8_t serialFlashUniqueID(void);
void serialFlashSectorErase(uint32_t address);
uint8_t serialFlashWrite(uint32_t address, uint8_t *data, uint16_t count);
