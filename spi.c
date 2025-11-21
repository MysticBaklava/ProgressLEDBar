#include "main.h"
#include "spi.h"

#define CE_LOW 	LPC_GPIO1->DATA &= ~(1UL <<  10)
#define CE_HIGH	LPC_GPIO1->DATA |= (1UL <<  10)

uint8_t chipUniqueId[8];

union{
	uint8_t b[4];
	uint32_t ln;
}ln2b;

void initSpi(void)
{	
	// Enable the SPI peripheral clock
  LPC_SYSCON->PRESETCTRL |= 0x01;					//Enable module
	LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 11); // Enable clock for SPI block
	LPC_SYSCON->SSP0CLKDIV = 4;
	
	LPC_IOCON->SCK_LOC = 0x02;							//SCK Locate to Pin 0_6
	
	LPC_IOCON->PIO0_6 &= ~0x07;
	LPC_IOCON->PIO0_6 |= 0x02;							//SCK pin function
	LPC_IOCON->PIO0_8 &= ~0x07;
	LPC_IOCON->PIO0_8 |= 0x01;							//MISO pin function
	LPC_IOCON->PIO0_9 &= ~0x17;
	LPC_IOCON->PIO0_9 |= 0x01;							//MOSI pin function
		
	LPC_GPIO1->DIR  |=  (1UL <<  10);				//CE 1_10
	LPC_GPIO1->DATA |= (1UL <<  10);        //CE HIGH
	
	LPC_SSP0->CPSR = 0x14;
	
	LPC_SSP0->CR0 = 0x07;
	LPC_SSP0->CR1 = 0x02;
}

uint8_t spiSend(uint8_t data)
{
	uint8_t rxData;
	
	LPC_SSP0->DR = data;
	while ( (LPC_SSP0->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
	rxData = LPC_SSP0->DR;
	return rxData;
}

uint8_t serialFlashUniqueID(void)
{
	uint8_t i;
	
	CE_LOW;
	
	spiSend(0x9F);
	for(i=0;i<4;i++)
		spiSend(0x00);
	
	for(i=0;i<8;i++)
		chipUniqueId[i] = spiSend(0xFF);
	
	CE_HIGH;
}

void serialFlashWriteEnable(void)
{	
	CE_LOW;
	
	spiSend(0x06);
	
	CE_HIGH;
}

void serialFlashWriteDisable(void)
{	
	CE_LOW;
	
	spiSend(0x04);
	
	CE_HIGH;
}

void serialFlashSectorErase(uint32_t address)
{
	serialFlashWriteEnable();
	CE_LOW;
	ln2b.ln = address;
	
	spiSend(0x20);
	spiSend(ln2b.b[2]);
	spiSend(ln2b.b[1]);
	spiSend(ln2b.b[0]);

	CE_HIGH;
	
	serialFlashWriteDisable();
}

uint8_t serialFlashWrite(uint32_t address, uint8_t *data, uint16_t count)
{
	uint8_t i;
	
	serialFlashWriteEnable();
	
	CE_LOW;
	ln2b.ln = address;
	
	spiSend(0x02);
	spiSend(ln2b.b[2]);
	spiSend(ln2b.b[1]);
	spiSend(ln2b.b[0]);
	for(i=0;i<count;i++)
		spiSend(data[i]);
	CE_HIGH;
	
	serialFlashWriteDisable();
}

uint8_t serialFlashReadByte(uint32_t address)
{
	uint8_t readValue;
	
	CE_LOW;
	ln2b.ln = address;
	
	spiSend(0x03);
	spiSend(ln2b.b[2]);
	spiSend(ln2b.b[1]);
	spiSend(ln2b.b[0]);
	readValue = spiSend(0xFF);
	CE_HIGH;
}

uint8_t serialFlashRead(uint32_t address, uint8_t *data, uint16_t count)
{
	uint16_t i = 0;
	
	CE_LOW;
	ln2b.ln = address;
	
	spiSend(0x0B);
	spiSend(ln2b.b[2]);
	spiSend(ln2b.b[1]);
	spiSend(ln2b.b[0]);
	while(count--)
	{
		data[i] = spiSend(0xFF);
		i++;
	}
	CE_HIGH;
}
