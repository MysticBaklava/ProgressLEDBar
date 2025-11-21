#include "LPC11xx.h"                    // Device header
#include <stdio.h>
#include "color_structs.h"

void ledsOff(void);
void setGammaColor(uint16_t indice, uint32_t rgb);
void setGammaColorRGB(uint16_t indice, struct Color rgb);
void line(uint32_t color, uint16_t begin, uint16_t end);
void setDefaultSegments(void);
void fillSegments(void);


uint32_t calculateGammaColorRGB(struct Color rgb);

extern uint16_t ledCount;
extern volatile int ledCounter;