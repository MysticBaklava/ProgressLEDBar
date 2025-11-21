#include "main.h"
#include "bezier.h"
#include "modbus.h"
#include "led_drive.h"
#include "segment_animate.h"
#include "spi.h"
#include "uart.h"

unsigned long t,resdly;
char str[64];
//struct Segment segment[4];

unsigned int machineState = 0x00;
sType s;

int dimm = 1;

void ioInit(void){
	LPC_SYSCON->SYSAHBCLKCTRL |= ((1UL <<  6) |     /* enable clock for GPIO        */
                                (1UL << 16) );    /* enable clock for IOCON       */

  LPC_GPIO2->DIR  |=  (1UL <<  10);               /* Data 1configure PINs as Output     */
  LPC_GPIO2->DATA &= ~(1UL <<  10);               /* switch LEDs off              */
	
	LPC_GPIO0->DIR  |=  (1UL <<  7);                /* Data2 configure PINs as Output     */
  LPC_GPIO0->DATA &= ~(1UL <<  7);                /* switch LEDs off              */
	
	LPC_GPIO2->DIR  &=  ~(1UL <<  2);                /* Data1 return configure PINs as Input     */
	LPC_GPIO2->IS &= ~(1UL <<  2);									// interrupt edge triggered
	LPC_GPIO2->IEV |= (1UL <<  2);									// rising edge
	LPC_GPIO2->IE  |= (1UL <<  2);									// enable interrupt
	//LPC_IOCON->PIO2_2 &=  ~(3UL <<  3);                /* Data1 return pin PD internal   Clear bits 3 and 4*/
	//LPC_IOCON->PIO2_2 |=  (1UL <<  3);                /* Data1 return pin PD internal   set pin 3*/
	
	//LPC_GPIO2->DIR  &=  ~(1UL <<  9);                /* Data2 return configure PINs as Input     */
  //LPC_IOCON->PIO2_9 &=  ~(3UL <<  3);                /* Data2 return pin PD internal   */
	//LPC_IOCON->PIO2_9 |=  (1UL <<  3);                /* Data2 return pin PD internal   */
	
	//NVIC_EnableIRQ(EINT2_IRQn);
	return;
}

void initTimers(void){
	uint32_t timerMatchValue;
	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1UL <<  9);				// enable timer0 32bit clock source
	
	LPC_TMR32B0->PR = 480;														// prescale
	//timerMatchValue = (SystemCoreClock / 1000000000) * 350; // 350ns
	
	LPC_TMR32B0->MR0 = 0xFFFFFFFF;														// Configure match register for generating interrupt at match
	
	//LPC_TMR32B0->MCR |= (1 << 1) | (1 << 0); 				// Reset timer on match, enable interrupt on match
	LPC_TMR32B0->MCR |= (1 << 1); 				// Reset timer on match, enable interrupt on match
    
	//LPC_TMR32B0->TCR |= (1<<1); 										//Reset Timer0
	
  //NVIC_EnableIRQ(TIMER_32_0_IRQn); 								// Enable Timer1 interrupt in NVIC
	LPC_TMR32B0->TCR |= (1<<0);											// enable timer
	
	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1UL <<  7);				// enable timer0 16bit clock source
	LPC_TMR16B0->PR = 1;
	LPC_TMR16B0->MR0 = 10;
	LPC_TMR16B0->MCR |= (1 << 1) | (1 << 0); 				// Reset timer on match, enable interrupt on match
	//LPC_TMR16B0->TCR |= 1;
}

void delay(unsigned int time){
	unsigned int i;
	unsigned long t;
	for(i=0;i<time;i++){
		for(t=0;t<50000;t++) __NOP();
	}
}

void delayMs(uint16_t timeVal){
	uint32_t tmpTime;
	tmpTime = LPC_TMR32B0->TC;
	
	while(LPC_TMR32B0->TC - tmpTime < timeVal * MS){
		__NOP();
	}
}


uint32_t smooth(uint32_t c1, uint32_t c2, uint16_t t){
	uint8_t r1,g1,b1,r2,g2,b2,r3,g3,b3;
	uint32_t c3;
	
	r1 = (uint8_t)((c1 & 0x00FF00) >> 8);
	g1 = (uint8_t)((c1 & 0xFF0000) >> 16);
	b1 = (uint8_t)(c1 & 0x0000FF);
	
	r2 = (uint8_t)((c2 & 0x00FF00) >> 8);
	g2 = (uint8_t)((c2 & 0xFF0000) >> 16);
	b2 = (uint8_t)(c2 & 0x0000FF);
	
	r3 = linear(r1, r2, t);
	g3 = linear(g1, g2, t);
	b3 = linear(b1, b2, t);
	
	c3 = g3;
	c3 = c3 << 8;
	c3 = c3 | r3;
	c3 = c3 << 8;
	c3 = c3 | b3;
	
	return(c3);
}



int main(void){

	
	SystemInit();
	SystemCoreClockUpdate();
	
	ioInit();
	
	receiveFlag = 0;
	
	UART_Init();
	UART_ReceiveInit();
	initTimers();
	t = getTick();
	resdly = getTick();
	rxInterval = getTick();
	
	prepareModbusRegisters();
	
	ledsOff();
	fillLedBar();
	
	selectContent(0x0000);

	while(1)
	{
		serialHandler();
		
		if(modbusSendPending == 1)
		{
			if(getTick() - resdly >= 35)
			{
				modbusSendPending = 0;
				modBusSend(modbusSendBufferLen);
			}	
		}
		
                static uint16_t previousRequestedState = 0xFFFF;
                uint16_t requestedState = modbusRegisters[15] & 0x0FFF;

                if(modbusRegisters[15] != requestedState)
                        modbusRegisters[15] = requestedState;

                if(previousRequestedState != requestedState)
                {
                        previousRequestedState = requestedState;

                        if(machineState != requestedState)
                                selectContent(machineState = requestedState);

                        modbusStateUpdated = 0;
                        modbusReceived = 0;
                }
                else if(modbusStateUpdated)
                {
                        modbusStateUpdated = 0;
                        modbusReceived = 0;
                }
                else if(modbusReceived)
                {
                        modbusReceived = 0;
                }
		
		if(getTick() - t >= MS)					//1 ms tick, 1 tick 10us
		{
			t = getTick();			
			secCount++;
				
			if(secCount == 10)						//30ms per frame refresh
			{
				secCount = 0;				
			}
			segmentsRender();
		}
	}
}
