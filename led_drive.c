#include "main.h"
#include "led_drive.h"
#include "uart.h"

//COLOR ORDER G R B
#define RED 0x03FF00U
#define GREEN 0xFDA802U
#define BLUE 0x7425DBU
#define ORANGE 0x12FF02U			// alt 20FF03
#define WARMWHITE 0xF1FF2FU
#define YELLOW 0xFFFF00U

#define TOTALSEGMENT 4
#define TOTALCOLORCOUNT 4

uint16_t ledCount = 70;
volatile int ledCounter;
volatile uint32_t led[100];

void port3Set(int num){
	LPC_GPIO3->DATA |=  (1UL << num);
}

void port3Clear(int num){
	LPC_GPIO3->DATA &= ~(1UL << num);             /* LED Off                  */
}

void port0Set(int num){
	LPC_GPIO0->DATA |=  (1UL << num);
}

void port0Clear(int num){
	LPC_GPIO0->DATA &= ~(1UL << num);             /* LED Off                  */
}
void port2Set(int num){
	LPC_GPIO2->DATA |=  (1UL << num);
}

void port2Clear(int num){
	LPC_GPIO2->DATA &= ~(1UL << num);             /* LED Off                  */
}
void fillLedBar(void){
	int ik,jk, t;
	volatile uint32_t color;
	uint8_t snap = 0;
	
	ledCounter = 0;
	
	LPC_GPIO2->DATA &= ~(1 << 10);
	for(t=0;t<300;t++)											//reset	the led bar
	{
		__NOP();
	}
		
	for(ik=0; ik<ledCount; ik++){										//write all 64 leds
		color = led[ik];
		
		NVIC_DisableIRQ(UART_IRQn);
		NVIC_DisableIRQ(SysTick_IRQn);
		
		for(jk=0;jk<24;jk++){
			if(color & 0x00800000){								//sample the MSB bit, than shift the color left
				LPC_GPIO2->DATA |=  (1 << 10);					//if the bit is 1
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();				
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();				
				__NOP();
				__NOP();								
				LPC_GPIO2->DATA &= ~(1 << 10);
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();				
			}else{
				LPC_GPIO2->DATA |=  (1 << 10);						//if the bit is zero
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();								
				LPC_GPIO2->DATA &= ~(1 << 10);
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();				
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();
			}
			color = color << 1;
		}
		NVIC_EnableIRQ(SysTick_IRQn);
		NVIC_EnableIRQ(UART_IRQn);
		
		
	}
	//ledCounter = ik;
	LPC_GPIO2->DATA |=  (1 << 10);
	
}



void barGraph(uint32_t color, uint16_t count, uint16_t pixelDelay){
	uint16_t i;
	
	for(i=0;i<64;i++){
		led[i] = 0x000000U;
	}		
	fillLedBar();
	delay(500);		
	
	for(i=0;i<count;i++){
		led[i] = color;
		fillLedBar();
		delay(pixelDelay);
		}
}

void ledsOff(void){
	int p;
	
	for(p=0;p<100;p++){
		led[p] = 0x000000U;
	}		
	
}

void line(uint32_t color, uint16_t begin, uint16_t end){
	uint16_t it;

	for(it=begin;it<end;it++){
		setGammaColor(it, color);
	}
	
	fillLedBar();
}


void setGammaColor(uint16_t indice, uint32_t rgb){
	uint8_t r,g,b;
	uint32_t tmp;
	
	r = (uint8_t)(rgb >> 16) & 0x0000FF;
	g = (uint8_t)(rgb >> 8) & 0x0000FF;
	b = (uint8_t)(rgb & 0x0000FF);
	
	tmp = (uint32_t)r;
	tmp = (tmp * tmp) / 256;
	r = (uint8_t) tmp;
	
	tmp = (uint32_t)g;
	tmp = (tmp * tmp) / 300;
	g = (uint8_t) tmp;
	
	tmp = (uint32_t)b;
	tmp = (tmp * tmp) / 600;
	b = (uint8_t) tmp;
	
	tmp = 0;
	tmp |= g << 16;
	tmp |= r << 8;
	tmp |= b;
	
	led[indice] = tmp;
}

void setGammaColorRGB(uint16_t indice, struct Color rgb){
	uint8_t r,g,b;
	uint32_t tmp;

	r = rgb.r;
	g = rgb.g;
	b = rgb.b;
	
	tmp = (uint32_t)r;
	tmp = (tmp * tmp) / 256;
	r = (uint8_t) tmp;
	
	tmp = (uint32_t)g;
	tmp = (tmp * tmp) / 300;
	g = (uint8_t) tmp;
	
	tmp = (uint32_t)b;
	tmp = (tmp * tmp) / 600;
	b = (uint8_t) tmp;
	
	tmp = 0;
	tmp |= g << 16;
	tmp |= r << 8;
	tmp |= b;
	
	led[indice] = tmp;
}

uint32_t calculateGammaColorRGB(struct Color rgb){
	uint8_t r,g,b;
	uint32_t tmp;

	r = rgb.r;
	g = rgb.g;
	b = rgb.b;
	
	tmp = (uint32_t)r;
	tmp = (tmp * tmp) / 256;
	r = (uint8_t) tmp / dimm;
	
	tmp = (uint32_t)g;
	tmp = (tmp * tmp) / 300;
	g = (uint8_t) tmp / dimm;
	
	tmp = (uint32_t)b;
	tmp = (tmp * tmp) / 600;
	b = (uint8_t) tmp / dimm;
	
	tmp = 0;
	tmp |= g << 16;
	tmp |= r << 8;
	tmp |= b;
	
	return(tmp);
}


void fillSegments(void){
		
	//  segmentNr segment counter 
	//	sg number of physical pixels in the segment
	//  j physical pixel indice
	//  colorNr color counter inside the segment
	struct Color color;
	
	uint16_t i,j,segmentNr,colorNr;
	uint16_t segmentStart, segmentEnd, f;
	uint16_t totalLen;
	//uint16_t tmp[32];
	uint16_t colorSpan, segmentLen, animLen;

	//memset(led, 0x00, sizeof(led));

	totalLen = calculateTotalSegmentLen();
	
	j = 0;																																										//starting from physical led zero
	for(segmentNr=0;segmentNr<TOTALSEGMENT;segmentNr++)																				//count the segments
	{
		segmentLen = calculateSegmentsLen(segmentNr, totalLen);																	//count the segment's actual lenght
				
		if(segmentLen > 60) segmentLen = 16;
		
		segmentStart = j;
		segmentEnd = j + segmentLen -1;
		animLen = (uint16_t)segmentLen;
		
		while(segmentLen > 0)																																		//fill the segment with the pattern 
		{			
			for(colorNr=0;colorNr<TOTALCOLORCOUNT;colorNr++)																			//each segment can have up to 4 pattern colors
			{
				colorSpan = s.segment[segmentNr].patternColor[colorNr].span;
				if(colorSpan > 0)
				{
					//sprintf(str, "Color Nr %d\n", colorNr);
					//UART_SendStr(str);
		
					color.r = s.segment[segmentNr].patternColor[colorNr].r;														//get the pattern color value
					color.g = s.segment[segmentNr].patternColor[colorNr].g;
					color.b = s.segment[segmentNr].patternColor[colorNr].b;
				
					//sprintf(str, "R:%d,G:%d,B:%d\n", color.r,color.g,color.b);
					//UART_SendStr(str);
					
					for(i=0;i<colorSpan;i++)										//fill the led buffer with the pattern color and length
					{	
							//if(j < totalLen)
							//	setGammaColorRGB(j, color);								
							j++;																																						//led buffer counter
							segmentLen--;																																		//segments calculated legth counts down for next segment
					}
				}
			}
			
			/*
			f = s.segment[segmentNr].animCount;
			
			animLen = 16;
			
			if(s.segment[segmentNr].speed > 0)																																				
			{						
				
				for(i=0;i<animLen;i++)																															//copy and shift the buffer from led values to tmp 
				{
					tmp[f] = led[segmentStart + i];
					f++;
					if(f >= animLen) f = 0;
				}
				
				for(i=0;i<animLen;i++)																															//copy the shifted tmp to led buffer
				{
					led[segmentStart + i] = tmp[i];							
				}

				s.segment[segmentNr].animCount++;																										//move anim count forward
				if(s.segment[segmentNr].animCount == animLen) s.segment[segmentNr].animCount = 0;		//animLen count can not exceed segment len
				
			}
			*/
		}
	}
	
	//fillLedBar();																																							//fill the buffer into physical led strip
}

void setDefaultSegments(void){
	
	s.segment[0].span = 1;
	s.segment[0].patternColor[0].span = 16;
	s.segment[0].patternColor[0].r = 0x29;
	s.segment[0].patternColor[0].g = 0xB3;
	s.segment[0].patternColor[0].b = 0xD2;
	
	s.segment[0].patternColor[1].span = 0;
	s.segment[0].patternColor[1].r = 0x3F;
	s.segment[0].patternColor[1].g = 0x3F;
	s.segment[0].patternColor[1].b = 0x3F;

	s.segment[0].patternColor[2].span = 0;
	s.segment[0].patternColor[3].span = 0;
	
	s.segment[0].speed = 0;
	s.segment[0].animCount = 0;
	//-------------------------------------------------------
	
	s.segment[1].span = 1;
	s.segment[1].patternColor[0].span = 4;	
	s.segment[1].patternColor[0].r = 0x29;
	s.segment[1].patternColor[0].g = 0xB3;
	s.segment[1].patternColor[0].b = 0xD2;
	
	s.segment[1].patternColor[1].span = 4;
	s.segment[1].patternColor[1].r = 0xE3;
	s.segment[1].patternColor[1].g = 0xED;
	s.segment[1].patternColor[1].b = 0xEE;

	s.segment[1].patternColor[2].span = 4;		
	s.segment[1].patternColor[2].r = 0x29;
	s.segment[1].patternColor[2].g = 0xB3;
	s.segment[1].patternColor[2].b = 0xD2;
	
	s.segment[1].patternColor[3].span = 4;
	s.segment[1].patternColor[3].r = 0xE3;
	s.segment[1].patternColor[3].g = 0xED;
	s.segment[1].patternColor[3].b = 0xEE;
	
	s.segment[1].speed = 100;
	s.segment[1].animCount = 0;
	//-------------------------------------------------------
	
	s.segment[2].span = 0;
	s.segment[2].patternColor[0].span = 16;
	s.segment[2].patternColor[0].r = 0xE3;
	s.segment[2].patternColor[0].g = 0xED;
	s.segment[2].patternColor[0].b = 0xEE;
	
	s.segment[2].patternColor[1].span = 0;
	s.segment[2].patternColor[1].r = 0xFC;
	s.segment[2].patternColor[1].g = 0x03;
	s.segment[2].patternColor[1].b = 0x03;

	s.segment[2].patternColor[2].span = 0;
	s.segment[2].patternColor[3].span = 0;

	s.segment[2].speed = 0;
	s.segment[2].animCount = 0;
	//-------------------------------------------------------
	
	s.segment[3].span = 0;
	s.segment[3].patternColor[0].span = 16;
	s.segment[3].patternColor[0].r = 0x30;
	s.segment[3].patternColor[0].g = 0x3C;
	s.segment[3].patternColor[0].b = 0x40;
	
	s.segment[3].patternColor[1].span = 0;
	s.segment[3].patternColor[1].r = 0xFC;
	s.segment[3].patternColor[1].g = 0x03;
	s.segment[3].patternColor[1].b = 0x94;

	s.segment[3].patternColor[2].span = 0;
	s.segment[3].patternColor[3].span = 0;

	s.segment[3].speed = 0;
	s.segment[3].animCount = 0;
}
