#include <stdint.h>

#define DEFAULT_DEVICE_ADDRESS 60
#define MODBUS_REGISTER_COUNT 20
#define deviceAddressField rxBuff[0]
#define functionCodeField rxBuff[1]
#define READ_REGISTERS		0x03
#define WRITE_REGISTER	0x06
#define WRITE_MULTIPLE_REGS	0x10

extern uint16_t modbusRegisters[MODBUS_REGISTER_COUNT];
extern uint16_t prevRegValues[4];
extern uint16_t modbusReceived;
extern uint16_t modbusStateUpdated;

extern uint16_t modbusSendBufferLen;
extern uint16_t modbusSendPending;	

void handleRxPacket(void);
void serialHandler(void);
uint16_t calculateCRC(uint8_t *ptbuf, int num);
void prepareModbusRegisters(void);