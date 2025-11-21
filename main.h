#include "LPC11xx.h"                    // Device header
#include <stdio.h>
#include <string.h>
#include "color_structs.h"


#define MS	100
#define getTick() LPC_TMR32B0->TC

#define BUFFLEN 256


typedef enum {
    RENDER_STANDARD = 0,   // existing patternColor mode
    RENDER_CUBIC,          // cubic Bézier gradient mode
    RENDER_BICUBIC         // bicubic Bézier gradient mode
} RenderMode;



struct PatternColor{
	uint8_t span;
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct Segment{
	uint8_t span;
	uint8_t ledCount;
	int speed;
	int timing;
	int animCount;
	uint16_t segmentStart;
	uint16_t segmentEnd;
	struct PatternColor patternColor[4];
	 RenderMode renderMode;              // NEW: mode of rendering for this segment
    struct CubicGradient cubicGradient; // NEW: parameters for cubic Bézier gradient
    struct BiCubicGradient biCubicGradient; // NEW: parameters for bicubic Bézier gradient
	
};

typedef union{
	struct Segment segment[4];
	uint8_t bytes[sizeof(struct Segment) * 4];
}sType;

extern sType s; 

															

void UART_IRQHandler(void);

extern volatile uint32_t led[100];
extern volatile uint8_t receiveFlag;
extern volatile int rxIndice;
extern uint8_t rxBuff[BUFFLEN];
extern uint8_t txBuff[BUFFLEN];
extern struct Segment segment[4];
extern int dimm;
extern uint16_t animationRunning;

extern char str[64];

extern unsigned long t,resdly;
extern uint8_t secFlag;
extern uint32_t msTicks;
extern uint32_t secCount;
extern unsigned long rxInterval;

void ledsOff(void);
void delay(unsigned int time);
void delayMs(uint16_t timeVal);
void setGammaColor(uint16_t indice, uint32_t rgb);

void fillLedBar(void);

void sceneNumber(uint8_t num);
void scene1(void);
void scene2(void);
void scene3(void);
void bicubicScene1(void);
void bicubicScene2(void);
void bicubicScene3(void);
void bicubicScene4(void);
void bicubicScene5(void);

void selectContent(int state);
extern unsigned int machineState;
extern uint16_t ledCount;