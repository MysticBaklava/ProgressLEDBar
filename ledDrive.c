#include "main.h"

//COLOR ORDER G R B
#define RED 0x03FF00U
#define GREEN 0xFDA802U
#define BLUE 0x7425DBU
#define ORANGE 0x12FF02U			// alt 20FF03
#define WARMWHITE 0xF1FF2FU
#define YELLOW 0xFFFF00U

uint32_t led[100];

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
	int ik,jk;
	uint32_t color;
	
	for(ik=0;ik<300;ik++)											//reset	the led bar
		LPC_GPIO2->DATA &= 0xFBFF;
		
	for(ik=0; ik<64; ik++){										//write all 64 leds
		color = led[ik];
			
		for(jk=0;jk<24;jk++){
			if(color & 0x00800000){
				LPC_GPIO2->DATA |=  0x400;					//if the bit is 1
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
				LPC_GPIO2->DATA &= 0xFBFF;
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();				
			}else{
				LPC_GPIO2->DATA |=  0x400;						//if the bit is zero
				__NOP();
				__NOP();
				__NOP();
				__NOP();
				__NOP();				
				LPC_GPIO2->DATA &= 0xFBFF;
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
	}
	LPC_GPIO2->DATA |=  0x400;
	delay(1);
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
	
	for(p=0;p<64;p++){
		led[p] = 0x000000U;
	}		
	fillLedBar();
}

void line(uint32_t color, uint16_t begin, uint16_t end){
	uint16_t it;
	
	for(it=0;it<64;it++){
		led[it] = 0x000000U;
	}
	
	for(it=begin;it<end;it++){
		led[it] = color;
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