#include "main.h"
#include "uart.h"



uint32_t msTicks = 0;
uint32_t secCount = 0;
unsigned long rxInterval = 0;
volatile uint8_t receiveFlag = 0;
uint8_t rxBuff[BUFFLEN];
uint8_t txBuff[BUFFLEN];
volatile int rxIndice = 0;

uint8_t secFlag = 0;

void SysTick_Handler(void){                               /* SysTick interrupt Handler. */
  //msTicks++;                                                /* See startup file startup_LPC17xx.s for SysTick vector */ 
	//secCount++;
	
	if(secCount >= 1000)
	{
		secCount = 0;
		secFlag = 1;
	}
	
	if(rxIndice > 0)
	{
		//if(msTicks - rxInterval > 10)
		//	receiveFlag = 1;

	}
}

void TIMER32_0_IRQHandler(void) {
	
	LPC_TMR32B0->IR |= (1<<0); 						//Clear MR0 Interrupt flag
	//LPC_GPIO0->DATA ^= (1<<7); 						//Toggle LED
}

// UART interrupt service routine
void UART_IRQHandler(void) {
	uint8_t IIRValue, LSRValue;
  uint8_t dummy = dummy;
	
	IIRValue = LPC_UART->IIR;
	
	if(!(IIRValue & 0x01)){								//if zero, interrupt is pending			
		if(IIRValue & 0x04){						//Data pending flag				
			receivedChar = LPC_UART->RBR;  		//Read received character
			
			if(receiveFlag == 0)
			{
				rxBuff[rxIndice] = receivedChar;
				rxIndice++;
			}
			
			rxInterval = getTick();			
		}else{
			dummy = LPC_UART->RBR;  					// Erronous int, Dummy Read received character
		}			
	}else{
		dummy = LPC_UART->RBR;  						// Erronous int, Dummy Read received character
	}
}

void EINT2_IRQHandler(void){
	return;
}