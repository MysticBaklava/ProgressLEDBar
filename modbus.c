#include "main.h"
#include "modbus.h"
#include "uart.h"

uint8_t slaveAddress = DEFAULT_DEVICE_ADDRESS;
uint16_t modbusRegisters[MODBUS_REGISTER_COUNT];
uint16_t prevRegValues[4];
uint16_t registerAddress;

uint16_t registerCount;
uint16_t modbusReceived;
uint16_t modbusStateUpdated;

uint16_t modbusSendBufferLen;

void modbusACKReply(void);
void writeSingleRegister(void);
void writeMultipleRegisters(void);
void readHoldingRegisters(void);
uint8_t checkPacketCrc(void);
void modBusSend(uint16_t len);
void writeMultipleReply(void);
uint16_t getCRC16 (uint8_t *nData, uint16_t wLength);
static void applyStateFromRegister(void);
uint16_t modbusSendPending = 0;
	
union{
        uint8_t b[2];
        uint16_t sh;
}sh2b;

static uint8_t registersInRange(uint16_t startRegister, uint16_t registerQuantity){
        uint32_t endRegister;

        if(registerQuantity == 0)
                return 0;

        endRegister = (uint32_t)startRegister + registerQuantity;

        if(startRegister >= MODBUS_REGISTER_COUNT || endRegister > MODBUS_REGISTER_COUNT)
                return 0;

        return 1;
}

static void applyStateFromRegister(void){
        uint16_t requestedState = modbusRegisters[15] & 0x0FFF;

        if(modbusRegisters[15] != requestedState)
                modbusRegisters[15] = requestedState;

        if(machineState != requestedState)
                modbusStateUpdated = 1;

        modbusReceived = 1;
}

void handleRxPacket(void){
		
	if(deviceAddressField != slaveAddress) return;
	if(checkPacketCrc() == 0) return;
	
	switch(functionCodeField){
		case READ_REGISTERS:
			readHoldingRegisters();
			break;
		case WRITE_REGISTER:
			writeSingleRegister();			
			modbusACKReply();
			break;
		case WRITE_MULTIPLE_REGS:
			writeMultipleRegisters();			
			writeMultipleReply();			
			break;
		default:
			break;
	}
	
	return;
}

void writeSingleRegister(void){
        uint16_t i;
        uint16_t tmp;

        sh2b.b[1] = rxBuff[2];
        sh2b.b[0] = rxBuff[3];
        registerAddress = sh2b.sh;

        if(registerAddress >= 40000)
                registerAddress -= 40000;

        if(!registersInRange(registerAddress, 1))
                return;

        sh2b.b[1] = rxBuff[4];
        sh2b.b[0] = rxBuff[5];
        modbusRegisters[registerAddress] = sh2b.sh;
	
	switch(registerAddress){
                case 11:
                        s.segment[0].span = modbusRegisters[11];
                        modbusReceived = 1;
                        break;
                case 12:
                        s.segment[1].span = modbusRegisters[12];
                        modbusReceived = 1;
                        break;
                case 13:
                        s.segment[2].span = modbusRegisters[13];
                        modbusReceived = 1;
                        break;
                case 14:
                        s.segment[3].span = modbusRegisters[14];
                        modbusReceived = 1;
                        break;
                case 15:
                        modbusReceived = 1;
                        applyStateFromRegister();
                        break;
		case 17:
			if(modbusRegisters[17] <= 10)
				dimm = modbusRegisters[17];
			break;
		case 18:
			ledCount = modbusRegisters[18];
			break;
	}
}

void writeMultipleRegisters(void){
        uint16_t i,j;
        uint16_t byteCount;
        uint8_t stateRegisterWritten = 0;

        sh2b.b[1] = rxBuff[2];
        sh2b.b[0] = rxBuff[3];
        registerAddress = sh2b.sh;

        if(registerAddress >= 40000)
                registerAddress -= 40000;

        sh2b.b[1] = rxBuff[4];
        sh2b.b[0] = rxBuff[5];
        registerCount = sh2b.sh;

        byteCount = rxBuff[6];

        if(!registersInRange(registerAddress, registerCount))
                return;

        if(byteCount != registerCount * 2)
                return;
	
	j = 0;
        for(i=0;i<registerCount;i++){

                sh2b.b[1] = rxBuff[7 + j];
                sh2b.b[0] = rxBuff[8 + j];
                modbusRegisters[registerAddress + i] = sh2b.sh;

                if((registerAddress + i) == 15)
                        stateRegisterWritten = 1;

                j = j + 2;

        }

	if((registerAddress + registerCount) >= 17 &&  modbusRegisters[17] <= 10)
		dimm = modbusRegisters[17];
	
        if((registerAddress + registerCount) >= 18 &&  modbusRegisters[18] >20 && modbusRegisters[18] < 120)
                ledCount = modbusRegisters[18];

        modbusReceived = 1;
        if(stateRegisterWritten)
                applyStateFromRegister();
}

void writeMultipleReply(void){
	uint16_t i, crc;
	crc = calculateCRC(rxBuff, 6);
	
	for(i=0;i<6;i++)
		txBuff[i] = rxBuff[i];
	
	txBuff[7] = crc & 0xFF;
	txBuff[6] = crc >> 8;
	
	modbusSendBufferLen = 8;
	resdly = getTick();
	modbusSendPending = 1;
}

void readHoldingRegisters(void){
	uint16_t i,j, crcCalculated, packLen;
	uint8_t errorFlag = 0;
	
	sh2b.b[1] = rxBuff[2];
	sh2b.b[0] = rxBuff[3];
	registerAddress = sh2b.sh;
	
	if(registerAddress >= 40000)
		registerAddress -= 40000;
	
        sh2b.b[1] = rxBuff[4];
        sh2b.b[0] = rxBuff[5];
        registerCount = sh2b.sh;

        if(!registersInRange(registerAddress, registerCount))
                return;

        //Response packet
        txBuff[0] = slaveAddress;
	txBuff[1] = READ_REGISTERS;
	txBuff[2] = (uint8_t)((registerCount * 2) & 0x00FF);
	
	j = 3;
	for(i=0;i<registerCount;i++){
		sh2b.sh = modbusRegisters[registerAddress + i];
		txBuff[j] = sh2b.b[1];
		txBuff[j + 1] = sh2b.b[0];
		j = j + 2;
	}
	
	packLen = (registerCount * 2) + 3;
	
	crcCalculated = calculateCRC(txBuff, packLen);
	txBuff[j] = (uint8_t)((crcCalculated & 0xFF00) >> 8);
	txBuff[j + 1] = (uint8_t)(crcCalculated & 0x00FF);
	
	packLen = packLen + 2;
	
	modbusSendBufferLen = packLen;
	resdly = getTick();
	modbusSendPending = 1;
	
	return;
}

void modBusSend(uint16_t len){
	uint16_t i;
	
	TX_EN;
	delayMs(1);
	for(i=0;i<len;i++){		
		UART_SendChar(txBuff[i]);
	}
	delayMs(1);
	RX_EN;
}

void modbusACKReply(void){
	
	uint16_t i;
	
	for(i=0;i<rxIndice;i++)
		txBuff[i] = rxBuff[i];
	
	modbusSendBufferLen = rxIndice;
	resdly = getTick();
	modbusSendPending = 1;
}

void serialHandler(void){	
	
	if(rxIndice > 0 && getTick() - rxInterval > 5 * MS)
		receiveFlag = 1;
	
	if(receiveFlag == 1)
	{
		handleRxPacket();
		memset(rxBuff, 0x00, sizeof(rxBuff));
		rxIndice = 0;
		receiveFlag = 0;
	}
}

uint8_t checkPacketCrc(void){
	uint16_t crcReceived, crcCalculated;
	
	crcReceived = (uint16_t)((rxBuff[rxIndice - 2] << 8) | rxBuff[rxIndice - 1]);
	crcCalculated = calculateCRC(rxBuff, rxIndice - 2);
	
	if(crcCalculated != crcReceived) 
		return 0;
	
	return 1;
}

void prepareModbusRegisters(void){
        uint16_t i;

        for(i=0;i<MODBUS_REGISTER_COUNT;i++)
                modbusRegisters[i] = 0x0000;

	modbusRegisters[0] = 0x5042;					//Device identified Progress Bar initial letters
	modbusRegisters[1] = 0x0102;					//Hardware revision 1.02
	modbusRegisters[3] = 0x010C;					//Software revision 1.12
	modbusRegisters[4] = 0x0001;					//Palette file version
	modbusRegisters[5] = 0x05;						//Uart Speed 1:1200 2:4800 3:9600 4:19200 5:38400
	modbusRegisters[6] = 0x3C;						//Device address 60

	modbusRegisters[11] = s.segment[0].span;
	modbusRegisters[12] = s.segment[1].span;
	modbusRegisters[13] = s.segment[2].span;
        modbusRegisters[14] = s.segment[3].span;
        modbusRegisters[15] = machineState;

        modbusReceived = 0;
        modbusStateUpdated = 0;
}

uint16_t calculateCRC(uint8_t *ptbuf, int num){
	
	uint16_t crc16 = 0xffff;
	uint16_t temp;
	uint16_t flag;
	uint8_t i,c;

	for (i = 0; i < num; i++)
	{
		temp = ptbuf[i]; // temp has the first byte
		temp &= 0x00ff; // mask the MSB
		crc16 = crc16 ^ temp; //crc16 XOR with temp
		for (c=0; c<8; c++)
		{
			flag = crc16 & 0x01; // LSBit di crc16 is mantained
			crc16 = crc16 >> 1; // Lsbit di crc16 is lost
			if (flag != 0)
				crc16 = crc16 ^ 0x0a001; // crc16 XOR with 0x0a001
		}
	}
	crc16 = (crc16 >> 8) | (crc16 << 8); // LSB is exchanged with MSB
	return (crc16);
}

uint16_t getCRC16 (uint8_t *nData, uint16_t wLength)
{
static const uint16_t wCRCTable[] = {
   0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
   0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
   0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
   0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
   0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
   0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
   0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
   0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
   0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
   0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
   0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
   0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
   0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
   0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
   0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
   0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
   0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
   0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
   0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
   0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
   0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
   0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
   0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
   0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
   0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
   0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
   0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
   0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
   0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
   0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
   0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
   0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

	uint8_t nTemp;
	uint16_t wCRCWord = 0xFFFF;

  while (wLength--)
  {
      nTemp = *nData++ ^ wCRCWord;
      wCRCWord >>= 8;
      wCRCWord  ^= wCRCTable[nTemp];
  }
  return wCRCWord;
} 