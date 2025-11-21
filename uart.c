#include "LPC11xx.h"                    // Device header
#include "uart.h"

volatile char receivedChar;
uint16_t uartBaudRate = 38400;

void UART_Init(void) {
		
    // Configure UART pins (TXD and RXD)
    LPC_IOCON->PIO1_6 &= ~0x07; // Clear FUNC bits
    LPC_IOCON->PIO1_6 |= 0x01;  // Set pin as TXD
    LPC_IOCON->PIO1_7 &= ~0x07; // Clear FUNC bits
    LPC_IOCON->PIO1_7 |= 0x01;  // Set pin as RXD

		// Enable the UART peripheral clock    
		LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 12); // Enable clock for UART block		
		
    // Calculate the UART divider value for the desired baud rate
    unsigned int uartDiv = SystemCoreClock / (16 * uartBaudRate);

    // Configure the UART settings
    LPC_UART->LCR = 0x83;  // 8-bit character length, 1 stop bit, no parity
    LPC_UART->DLM = uartDiv / 256;
    LPC_UART->DLL = uartDiv % 256;

    // Enable the UART receiver and transmitter
    LPC_UART->LCR = 0x03;  // Set DLAB to 0
    LPC_UART->FCR = 0x07;  // Enable and reset FIFOs
		
		LPC_SYSCON->UARTCLKDIV = 1;
	
		LPC_GPIO1->DIR  |=  (1UL <<  5);                /* RS485 RE PINs as Output     */
		LPC_GPIO1->DATA &= ~(1UL <<  5);                /* Receive mode              */
}

void UART_SendChar(char ch) {
    // Wait for the UART transmitter to be ready
    
    // Send the character
    LPC_UART->THR = ch;
	
		while (!(LPC_UART->LSR & (1 << 5) && LPC_UART->LSR & (1 << 6)));
}

void sendRS485Char(char chr){
	TX_EN;
	delayMs(1);
	UART_SendChar(chr);
	delayMs(1);
	RX_EN;
}

void UART_SendStr(char *str){
	uint16_t i = 0;
	
	TX_EN;
	delayMs(1);
	
	while(str[i] != '\0' && i<64)
	{
		UART_SendChar(str[i]);
		i++;
	}
	
	delayMs(1);
	RX_EN;
}

void UART_ReceiveInit(void) {
		
    // Enable UART receive data available interrupt
    LPC_UART->IER |= (1 << 0);  // RDA (Receive Data Available) interrupt
    // Enable UART interrupt in NVIC
    NVIC_EnableIRQ(UART_IRQn);
}


/*----------------------------------------------------------------------------
  Read character from Serial Port   (blocking read)
 *----------------------------------------------------------------------------*/
int UARTgetkey (void) {
  while (!(LPC_UART->LSR & 0x01));
  return (LPC_UART->RBR);
}