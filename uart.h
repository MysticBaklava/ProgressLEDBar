void UART_Init(void);
void UART_SendChar(char ch);
void UART_ReceiveInit(void);
int UARTgetkey (void);
void sendRS485Char(char chr);
void UART_SendStr(char *str);

#define IER_RBR         (0x01<<0)
#define IER_THRE        (0x01<<1)
#define IER_RLS         (0x01<<2)

#define IIR_PEND        0x01
#define IIR_RLS         0x03
#define IIR_RDA         0x02
#define IIR_CTI         0x06
#define IIR_THRE        0x01

#define LSR_RDR         (0x01<<0)
#define LSR_OE          (0x01<<1)
#define LSR_PE          (0x01<<2)
#define LSR_FE          (0x01<<3)
#define LSR_BI          (0x01<<4)
#define LSR_THRE        (0x01<<5)
#define LSR_TEMT        (0x01<<6)
#define LSR_RXFE        (0x01<<7)

#define RX_EN LPC_GPIO1->DATA &= ~(1UL <<  5)
#define TX_EN	LPC_GPIO1->DATA |= (1UL <<  5)


extern volatile char receivedChar;