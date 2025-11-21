#include "main.h"
#include "modbus.h"
#include <math.h>
#include "color_structs.h"
#include "bezier.h"

int previousState = -1;

void startupContent(void);
void resetSegments(void);

void resetSegments(void){ 
		
	s.segment[ 0 ].span = 0;
	//s.segment[ 0 ].speed = 0;
	//s.segment[ 0 ].timing = 0;
	//s.segment[ 0 ].animCount = 0;
	s.segment[ 0 ].patternColor[ 0 ].span = 0;
	s.segment[ 0 ].patternColor[ 1 ].span = 0;
	s.segment[ 0 ].patternColor[ 2 ].span = 0;
	s.segment[ 0 ].patternColor[ 3 ].span = 0;
	s.segment[ 1 ].span = 0;
	s.segment[ 1 ].speed = 0;
	//s.segment[ 1 ].animCount = 0;
	s.segment[ 1 ].patternColor[ 0 ].span = 0;
	s.segment[ 1 ].patternColor[ 1 ].span = 0;
	s.segment[ 1 ].patternColor[ 2 ].span = 0;
	s.segment[ 1 ].patternColor[ 3 ].span = 0;
	s.segment[ 2 ].span = 0;
	s.segment[ 2 ].speed = 0;
	//s.segment[ 2 ].animCount = 0;
	s.segment[ 2 ].patternColor[ 0 ].span = 0;
	s.segment[ 2 ].patternColor[ 1 ].span = 0;
	s.segment[ 2 ].patternColor[ 2 ].span = 0;
	s.segment[ 2 ].patternColor[ 3 ].span = 0;
	s.segment[ 3 ].span = 0;
	s.segment[ 3 ].speed = 0;
	//s.segment[ 3 ].animCount = 0;
	s.segment[ 3 ].patternColor[ 0 ].span = 0;
	s.segment[ 3 ].patternColor[ 1 ].span = 0;
	s.segment[ 3 ].patternColor[ 2 ].span = 0;
	s.segment[ 3 ].patternColor[ 3 ].span = 0;
	for (int seg = 0; seg < 4; ++seg) {
        s.segment[seg].renderMode = RENDER_STANDARD;
	}		//
}


void exampleGradientContent(void) {
     resetSegments();
    // Segment 0: Cubic Bezier gradient
    s.segment[0].span = 1;
    s.segment[0].speed = 4;                     
    s.segment[0].renderMode = RENDER_CUBIC;
    // Define a cubic gradient with 4 control colors and param bias:
    s.segment[0].cubicGradient.rgb0 = setColor(150, 0, 0);    
    s.segment[0].cubicGradient.rgb1 = setColor(0,0, 0);  
    s.segment[0].cubicGradient.rgb2 = setColor(0, 0, 0);   
    s.segment[0].cubicGradient.rgb3 = setColor(150, 0, 0);   
    s.segment[0].cubicGradient.u0   = 65535;  // control bias (approx 25%)
    s.segment[0].cubicGradient.u1   = 0;  // control bias (approx 75%)
	
	
	
//s.segment[0].span = 1;
//s.segment[0].speed = 5;                    // animate with scrolling
//s.segment[0].renderMode = RENDER_BICUBIC;
//					
//s.segment[0].biCubicGradient.p0 = setColor(48, 60, 64);
//s.segment[0].biCubicGradient.p1 = setColor(48, 60, 64);
//s.segment[0].biCubicGradient.p2 = setColor(48, 60, 64);
//s.segment[0].biCubicGradient.p3 = setColor(48, 60, 64);
//					
//s.segment[0].biCubicGradient.q0 = setColor(251, 236, 212);
//s.segment[0].biCubicGradient.q1 = setColor(48, 60, 64);
//s.segment[0].biCubicGradient.q2 = setColor(48, 60, 64);
//s.segment[0].biCubicGradient.q3 = setColor(251, 236, 212);
//					
//s.segment[0].biCubicGradient.r0 = setColor(251, 236, 212);
//s.segment[0].biCubicGradient.r1 = setColor(48, 60, 64);
//s.segment[0].biCubicGradient.r2 = setColor(48, 60, 64);
//s.segment[0].biCubicGradient.r3 = setColor(251, 236, 212);
//					
//s.segment[0].biCubicGradient.s0 = setColor(251, 236, 212);
//s.segment[0].biCubicGradient.s1 = setColor(251, 236, 212);
//s.segment[0].biCubicGradient.s2 = setColor(251, 236, 212);
//s.segment[0].biCubicGradient.s3 = setColor(251, 236, 212);
//					
//s.segment[0].biCubicGradient.u0 = 32767;
//s.segment[0].biCubicGradient.u1 = 32511;
//s.segment[0].biCubicGradient.v0 = 49407;
//s.segment[0].biCubicGradient.v1 = 16895;






}

void startupContent(void){ // # 0 & 0 
s.segment[ 0 ].span = 1;
s.segment[ 0 ].speed = 0;
s.segment[ 0 ].patternColor[ 0 ].span = 1;
s.segment[ 0 ].patternColor[ 0 ].r = 249;
s.segment[ 0 ].patternColor[ 0 ].g = 101;
s.segment[ 0 ].patternColor[ 0 ].b = 27;
}
// r=238 g=210 b=165 krem rengi, r=234 g=88 b=2 turuncu, r=206 g=235 b=238 buz mavisi, 
//r=41 g=179 b=210 mavi, r=0 g=179 b=90 yesil, r=255 g=214 b=0 sari
void readyContent(void){ //#10 &16
s.segment[ 0 ].span = 1;
s.segment[ 0 ].speed = 0;
s.segment[ 0 ].patternColor[ 0 ].span = 1;
s.segment[ 0 ].patternColor[ 0 ].r = 238;
s.segment[ 0 ].patternColor[ 0 ].g = 210;
s.segment[ 0 ].patternColor[ 0 ].b = 165;
}

void selection(void){ //#20 &32
	
//s.segment[0].span = 1;
//s.segment[0].speed = 6;                    // animate with scrolling
//s.segment[0].renderMode = RENDER_BICUBIC;
//	
//s.segment[0].biCubicGradient.p0 = setColor(238, 210, 165);
//s.segment[0].biCubicGradient.p1 = setColor(48, 60, 64);
//s.segment[0].biCubicGradient.p2 = setColor(48, 60, 64);
//s.segment[0].biCubicGradient.p3 = setColor(238, 210, 165);
//					
//s.segment[0].biCubicGradient.q0 = setColor(238, 210, 165);
//s.segment[0].biCubicGradient.q1 = setColor(48, 60, 64);
//s.segment[0].biCubicGradient.q2 = setColor(48, 60, 64);
//s.segment[0].biCubicGradient.q3 = setColor(238, 210, 165);
//					
//s.segment[0].biCubicGradient.r0 = setColor(238, 210, 165);
//s.segment[0].biCubicGradient.r1 = setColor(48, 60, 64);
//s.segment[0].biCubicGradient.r2 = setColor(48, 60, 64);
//s.segment[0].biCubicGradient.r3 = setColor(238, 210, 165);
//					
//s.segment[0].biCubicGradient.s0 = setColor(238, 210, 165);
//s.segment[0].biCubicGradient.s1 = setColor(48, 60, 64);
//s.segment[0].biCubicGradient.s2 = setColor(48, 60, 64);
//s.segment[0].biCubicGradient.s3 = setColor(238, 210, 165);
//					
//s.segment[0].biCubicGradient.u0 = 32767;
//s.segment[0].biCubicGradient.u1 = 32511;
//s.segment[0].biCubicGradient.v0 = 49407;
//s.segment[0].biCubicGradient.v1 = 17151;


     resetSegments();
    // Segment 0: Cubic Bezier gradient
    s.segment[0].span = 1;
    s.segment[0].speed = 10;                     
    s.segment[0].renderMode = RENDER_CUBIC;
    // Define a cubic gradient with 4 control colors and param bias:
    s.segment[0].cubicGradient.rgb0 = setColor(238, 210, 165);    
    s.segment[0].cubicGradient.rgb1 = setColor(48,60, 64);  
    s.segment[0].cubicGradient.rgb2 = setColor(48, 60, 64);   
    s.segment[0].cubicGradient.rgb3 = setColor(238, 210, 165);   
    s.segment[0].cubicGradient.u0   = 0;  // control bias (approx 25%)
    s.segment[0].cubicGradient.u1   = 65535;  // control bias (approx 75%)




}

void cycling1(void){
s.segment[ 0 ].span = 12;
s.segment[ 0 ].speed = 50;
s.segment[ 0 ].patternColor[ 0 ].span = 12;
s.segment[ 0 ].patternColor[ 0 ].r = 41;
s.segment[ 0 ].patternColor[ 0 ].g = 179;
s.segment[ 0 ].patternColor[ 0 ].b = 210;
s.segment[ 1 ].span = 8;
s.segment[ 1 ].speed = 14;
s.segment[ 1 ].patternColor[ 0 ].span = 46;
s.segment[ 1 ].patternColor[ 0 ].r = 48;
s.segment[ 1 ].patternColor[ 0 ].g = 60;
s.segment[ 1 ].patternColor[ 0 ].b = 64;
	
s.segment[ 1 ].patternColor[ 1 ].span = 2;
s.segment[ 1 ].patternColor[ 1 ].r = 41;
s.segment[ 1 ].patternColor[ 1 ].g = 179;
s.segment[ 1 ].patternColor[ 1 ].b = 210;
	
s.segment[ 1 ].patternColor[ 2 ].span = 2;
s.segment[ 1 ].patternColor[ 2 ].r = 100;
s.segment[ 1 ].patternColor[ 2 ].g = 220;
s.segment[ 1 ].patternColor[ 2 ].b = 250;


//s.segment[0].renderMode = RENDER_STANDARD;
//s.segment[ 0 ].span = 12;
//s.segment[ 0 ].speed = 50;
//s.segment[ 0 ].patternColor[ 0 ].span = 12;
//s.segment[ 0 ].patternColor[ 0 ].r = 41;
//s.segment[ 0 ].patternColor[ 0 ].g = 179;
//s.segment[ 0 ].patternColor[ 0 ].b = 210;


//s.segment[1].span = 1;
//s.segment[1].speed = 5;                    // animate with scrolling
//s.segment[1].renderMode = RENDER_BICUBIC;
//					
//s.segment[1].biCubicGradient.p0 = setColor(0, 0, 0);
//s.segment[1].biCubicGradient.p1 = setColor(0, 0, 0);
//s.segment[1].biCubicGradient.p2 = setColor(0, 0, 0);
//s.segment[1].biCubicGradient.p3 = setColor(0, 0, 0);

//s.segment[1].biCubicGradient.q0 = setColor(0, 0, 0);
//s.segment[1].biCubicGradient.q1 = setColor(41, 179, 210);
//s.segment[1].biCubicGradient.q2 = setColor(41, 179, 210);
//s.segment[1].biCubicGradient.q3 = setColor(0, 0, 0);

//s.segment[1].biCubicGradient.r0 = setColor(0, 0, 0);
//s.segment[1].biCubicGradient.r1 = setColor(41, 179, 210);
//s.segment[1].biCubicGradient.r2 = setColor(41, 179, 210);
//s.segment[1].biCubicGradient.r3 = setColor(0, 0, 0);

//s.segment[1].biCubicGradient.s0 = setColor(0, 0, 0);
//s.segment[1].biCubicGradient.s1 = setColor(0, 0, 0);
//s.segment[1].biCubicGradient.s2 = setColor(0, 0, 0);
//s.segment[1].biCubicGradient.s3 = setColor(0, 0, 0);

//s.segment[1].biCubicGradient.u0 = 0;
//s.segment[1].biCubicGradient.u1 = 65535;
//s.segment[1].biCubicGradient.v0 = 0;
//s.segment[1].biCubicGradient.v1 = 65535;



}                            

void cycling2(void){
s.segment[ 0 ].span = 12;
s.segment[ 0 ].speed = 0;
s.segment[ 0 ].patternColor[ 0 ].span = 1;
s.segment[ 0 ].patternColor[ 0 ].r = 41;
s.segment[ 0 ].patternColor[ 0 ].g = 179;
s.segment[ 0 ].patternColor[ 0 ].b = 210;
s.segment[ 1 ].span = 8;
s.segment[ 1 ].speed = -14;
s.segment[ 1 ].patternColor[ 0 ].span = 2;
s.segment[ 1 ].patternColor[ 0 ].r = 255;
s.segment[ 1 ].patternColor[ 0 ].g = 123;
s.segment[ 1 ].patternColor[ 0 ].b = 0;
s.segment[ 1 ].patternColor[ 1 ].span = 2;
s.segment[ 1 ].patternColor[ 1 ].r = 234;
s.segment[ 1 ].patternColor[ 1 ].g = 88;
s.segment[ 1 ].patternColor[ 1 ].b = 6;
s.segment[ 1 ].patternColor[ 2 ].span = 80;
s.segment[ 1 ].patternColor[ 2 ].r = 48;
s.segment[ 1 ].patternColor[ 2 ].g = 60;
s.segment[ 1 ].patternColor[ 2 ].b = 64;
}

void cycling3(void){
	s.segment[ 0 ].span = 12;
s.segment[ 0 ].speed = 0;
s.segment[ 0 ].patternColor[ 0 ].span = 1;
s.segment[ 0 ].patternColor[ 0 ].r = 41;
s.segment[ 0 ].patternColor[ 0 ].g = 179;
s.segment[ 0 ].patternColor[ 0 ].b = 210;
s.segment[ 1 ].span = 8;
s.segment[ 1 ].speed = 0;
s.segment[ 1 ].patternColor[ 0 ].span = 3;
s.segment[ 1 ].patternColor[ 0 ].r = 41;
s.segment[ 1 ].patternColor[ 0 ].g = 179;
s.segment[ 1 ].patternColor[ 0 ].b = 210;
s.segment[ 1 ].patternColor[ 1 ].span = 3;
s.segment[ 1 ].patternColor[ 1 ].r = 227;
s.segment[ 1 ].patternColor[ 1 ].g = 237;
s.segment[ 1 ].patternColor[ 1 ].b = 238;
s.segment[ 2 ].span = 6;
s.segment[ 2 ].speed = 0;
s.segment[ 2 ].patternColor[ 0 ].span = 1;
s.segment[ 2 ].patternColor[ 0 ].r = 227;
s.segment[ 2 ].patternColor[ 0 ].g = 237;
s.segment[ 2 ].patternColor[ 0 ].b = 238;
s.segment[ 3 ].span = 16;
s.segment[ 3 ].speed = 512;
s.segment[ 3 ].patternColor[ 0 ].span = 2;
s.segment[ 3 ].patternColor[ 0 ].r = 249;
s.segment[ 3 ].patternColor[ 0 ].g = 101;
s.segment[ 3 ].patternColor[ 0 ].b = 27;
s.segment[ 3 ].patternColor[ 1 ].span = 10;
s.segment[ 3 ].patternColor[ 1 ].r = 72;
s.segment[ 3 ].patternColor[ 1 ].g = 88;
s.segment[ 3 ].patternColor[ 1 ].b = 88;
}

void done1(void){
	s.segment[ 0 ].span = 1;
s.segment[ 0 ].speed = 60;
s.segment[ 0 ].patternColor[ 0 ].span = 32;
s.segment[ 0 ].patternColor[ 0 ].r = 0;
s.segment[ 0 ].patternColor[ 0 ].g = 179;
s.segment[ 0 ].patternColor[ 0 ].b = 115;
s.segment[ 0 ].patternColor[ 1 ].span = 8;
s.segment[ 0 ].patternColor[ 1 ].r = 0;
s.segment[ 0 ].patternColor[ 1 ].g = 232;
s.segment[ 0 ].patternColor[ 1 ].b = 120;
}
void done2(void){
	s.segment[ 0 ].span = 1;
s.segment[ 0 ].speed = 70;
s.segment[ 0 ].patternColor[ 0 ].span = 32;
s.segment[ 0 ].patternColor[ 0 ].r = 0;
s.segment[ 0 ].patternColor[ 0 ].g = 179;
s.segment[ 0 ].patternColor[ 0 ].b = 115;
s.segment[ 0 ].patternColor[ 1 ].span = 8;
s.segment[ 0 ].patternColor[ 1 ].r = 255;
s.segment[ 0 ].patternColor[ 1 ].g = 214;
s.segment[ 0 ].patternColor[ 1 ].b = 0;
}
void done3(void){
s.segment[ 0 ].span = 1;
s.segment[ 0 ].speed = 70;
s.segment[ 0 ].patternColor[ 0 ].span = 32;
s.segment[ 0 ].patternColor[ 0 ].r = 0;
s.segment[ 0 ].patternColor[ 0 ].g = 179;
s.segment[ 0 ].patternColor[ 0 ].b = 115;
s.segment[ 0 ].patternColor[ 1 ].span = 8;
s.segment[ 0 ].patternColor[ 1 ].r = 249;
s.segment[ 0 ].patternColor[ 1 ].g = 101;
s.segment[ 0 ].patternColor[ 1 ].b = 27;
}
void stopping(void){
	s.segment[ 0 ].span = 3;
	s.segment[ 0 ].speed = 128;
	s.segment[ 0 ].patternColor[ 0 ].span = 4;
	s.segment[ 0 ].patternColor[ 0 ].r = 0;
	s.segment[ 0 ].patternColor[ 0 ].g = 179;
	s.segment[ 0 ].patternColor[ 0 ].b = 115;
	s.segment[ 0 ].patternColor[ 1 ].span = 2;
	s.segment[ 0 ].patternColor[ 1 ].r = 72;
	s.segment[ 0 ].patternColor[ 1 ].g = 88;
	s.segment[ 0 ].patternColor[ 1 ].b = 88;
	s.segment[ 1 ].span = 2;
	s.segment[ 1 ].speed = 128;
	s.segment[ 1 ].patternColor[ 0 ].span = 4;
	s.segment[ 1 ].patternColor[ 0 ].r = 48;
	s.segment[ 1 ].patternColor[ 0 ].g = 60;
	s.segment[ 1 ].patternColor[ 0 ].b = 64;
	s.segment[ 1 ].patternColor[ 1 ].span = 2;
	s.segment[ 1 ].patternColor[ 1 ].r = 72;
	s.segment[ 1 ].patternColor[ 1 ].g = 88;
	s.segment[ 1 ].patternColor[ 1 ].b = 88;
}
void outOfOrder(void){
	s.segment[ 0 ].span = 1;
s.segment[ 0 ].speed = 0;
s.segment[ 0 ].patternColor[ 0 ].span = 8;
s.segment[ 0 ].patternColor[ 0 ].r = 249;
s.segment[ 0 ].patternColor[ 0 ].g = 101;
s.segment[ 0 ].patternColor[ 0 ].b = 27;
s.segment[ 0 ].patternColor[ 1 ].span = 8;
s.segment[ 0 ].patternColor[ 1 ].r = 48;
s.segment[ 0 ].patternColor[ 1 ].g = 60;
s.segment[ 0 ].patternColor[ 1 ].b = 64;
}
void emergencyStop(void){
	s.segment[ 0 ].span = 2;
s.segment[ 0 ].speed = 128;
s.segment[ 0 ].patternColor[ 0 ].span = 4;
s.segment[ 0 ].patternColor[ 0 ].r = 249;
s.segment[ 0 ].patternColor[ 0 ].g = 101;
s.segment[ 0 ].patternColor[ 0 ].b = 27;
s.segment[ 0 ].patternColor[ 1 ].span = 12;
s.segment[ 0 ].patternColor[ 1 ].r = 120;
s.segment[ 0 ].patternColor[ 1 ].g = 30;
s.segment[ 0 ].patternColor[ 1 ].b = 0;
}
void delayedStart1(void){
	s.segment[ 0 ].span = 16;
s.segment[ 0 ].speed = 1024;
s.segment[ 0 ].patternColor[ 0 ].span = 8;
s.segment[ 0 ].patternColor[ 0 ].r = 249;
s.segment[ 0 ].patternColor[ 0 ].g = 101;
s.segment[ 0 ].patternColor[ 0 ].b = 27;
s.segment[ 0 ].patternColor[ 1 ].span = 8;
s.segment[ 0 ].patternColor[ 1 ].r = 48;
s.segment[ 0 ].patternColor[ 1 ].g = 60;
s.segment[ 0 ].patternColor[ 1 ].b = 64;
}
void delayedStart2(void){
	s.segment[ 0 ].span = 63;
	s.segment[ 0 ].speed = 0;
	s.segment[ 0 ].patternColor[ 0 ].span = 1;
	s.segment[ 0 ].patternColor[ 0 ].r = 48;
	s.segment[ 0 ].patternColor[ 0 ].g = 60;
	s.segment[ 0 ].patternColor[ 0 ].b = 64;
	s.segment[ 1 ].span = 27;
	s.segment[ 1 ].speed = -160;
	s.segment[ 1 ].patternColor[ 0 ].span = 2;
	s.segment[ 1 ].patternColor[ 0 ].r = 249;
	s.segment[ 1 ].patternColor[ 0 ].g = 101;
	s.segment[ 1 ].patternColor[ 0 ].b = 27;
	s.segment[ 1 ].patternColor[ 1 ].span = 14;
	s.segment[ 1 ].patternColor[ 1 ].r = 72;
	s.segment[ 1 ].patternColor[ 1 ].g = 88;
	s.segment[ 1 ].patternColor[ 1 ].b = 88;
}
void payment1(void){
s.segment[ 0 ].span = 12;
s.segment[ 0 ].speed = 0;
//s.segment[ 0 ].patternColor[ 0 ].span = 3;
//s.segment[ 0 ].patternColor[ 0 ].r = 48;
//s.segment[ 0 ].patternColor[ 0 ].g = 60;
//s.segment[ 0 ].patternColor[ 0 ].b = 64;
s.segment[ 0 ].patternColor[ 0 ].span = 6;
s.segment[ 0 ].patternColor[ 0 ].r = 255;
s.segment[ 0 ].patternColor[ 0 ].g = 214;
s.segment[ 0 ].patternColor[ 0 ].b = 0;
s.segment[ 1 ].span = 8;
s.segment[ 1 ].speed = 0;
s.segment[ 1 ].patternColor[ 0 ].span = 1;
s.segment[ 1 ].patternColor[ 0 ].r = 48;
s.segment[ 1 ].patternColor[ 0 ].g = 60;
s.segment[ 1 ].patternColor[ 0 ].b = 64;
}
void payment2(void){
	s.segment[ 0 ].span = 12;
s.segment[ 0 ].speed = 0;
s.segment[ 0 ].patternColor[ 0 ].span = 2;
s.segment[ 0 ].patternColor[ 0 ].r = 0;
s.segment[ 0 ].patternColor[ 0 ].g = 179;
s.segment[ 0 ].patternColor[ 0 ].b = 115;
s.segment[ 0 ].patternColor[ 1 ].span = 6;
s.segment[ 0 ].patternColor[ 1 ].r = 0;
s.segment[ 0 ].patternColor[ 1 ].g = 179;
s.segment[ 0 ].patternColor[ 1 ].b = 115;
s.segment[ 1 ].span = 0;
s.segment[ 1 ].speed = 0;
s.segment[ 1 ].patternColor[ 0 ].span = 1;
s.segment[ 1 ].patternColor[ 0 ].r = 48;
s.segment[ 1 ].patternColor[ 0 ].g = 60;
s.segment[ 1 ].patternColor[ 0 ].b = 64;
}
void payment3(void){
	s.segment[ 0 ].span = 1;
s.segment[ 0 ].speed = 1024;
s.segment[ 0 ].patternColor[ 0 ].span = 4;
s.segment[ 0 ].patternColor[ 0 ].r = 48;
s.segment[ 0 ].patternColor[ 0 ].g = 60;
s.segment[ 0 ].patternColor[ 0 ].b = 64;
s.segment[ 0 ].patternColor[ 1 ].span = 4;
s.segment[ 0 ].patternColor[ 1 ].r = 249;
s.segment[ 0 ].patternColor[ 1 ].g = 101;
s.segment[ 0 ].patternColor[ 1 ].b = 27;
s.segment[ 0 ].patternColor[ 2 ].span = 4;
s.segment[ 0 ].patternColor[ 2 ].r = 255;
s.segment[ 0 ].patternColor[ 2 ].g = 214;
s.segment[ 0 ].patternColor[ 2 ].b = 0;
s.segment[ 0 ].patternColor[ 3 ].span = 4;
s.segment[ 0 ].patternColor[ 3 ].r = 249;
s.segment[ 0 ].patternColor[ 3 ].g = 101;
s.segment[ 0 ].patternColor[ 3 ].b = 27;
}
void welcome(void){
	s.segment[ 0 ].span = 1;
s.segment[ 0 ].speed = -512;
s.segment[ 0 ].patternColor[ 0 ].span = 32;
s.segment[ 0 ].patternColor[ 0 ].r = 251;
s.segment[ 0 ].patternColor[ 0 ].g = 236;
s.segment[ 0 ].patternColor[ 0 ].b = 212;
s.segment[ 0 ].patternColor[ 1 ].span = 32;
s.segment[ 0 ].patternColor[ 1 ].r = 227;
s.segment[ 0 ].patternColor[ 1 ].g = 237;
s.segment[ 0 ].patternColor[ 1 ].b = 238;
}
void thankyou(void){
	s.segment[ 0 ].span = 1;
s.segment[ 0 ].speed = 0;
s.segment[ 0 ].patternColor[ 0 ].span = 1;
s.segment[ 0 ].patternColor[ 0 ].r = 72;
s.segment[ 0 ].patternColor[ 0 ].g = 88;
s.segment[ 0 ].patternColor[ 0 ].b = 88;
}
void outofWorkingHours(void){
s.segment[ 0 ].span = 1;
s.segment[ 0 ].speed = 64;
s.segment[ 0 ].patternColor[ 0 ].span = 1;
s.segment[ 0 ].patternColor[ 0 ].r = 227;
s.segment[ 0 ].patternColor[ 0 ].g = 237;
s.segment[ 0 ].patternColor[ 0 ].b = 238;
s.segment[ 0 ].patternColor[ 1 ].span = 15;
s.segment[ 0 ].patternColor[ 1 ].r = 72;
s.segment[ 0 ].patternColor[ 1 ].g = 88;
s.segment[ 0 ].patternColor[ 1 ].b = 88;
}
void wizard(void){
s.segment[ 0 ].span = 1;
s.segment[ 0 ].speed = 0;
s.segment[ 0 ].patternColor[ 0 ].span = 1;
s.segment[ 0 ].patternColor[ 0 ].r = 0;
s.segment[ 0 ].patternColor[ 0 ].g = 179;
s.segment[ 0 ].patternColor[ 0 ].b = 115;
s.segment[ 1 ].span = 1;
s.segment[ 1 ].speed = 0;
s.segment[ 1 ].patternColor[ 0 ].span = 16;
s.segment[ 1 ].patternColor[ 0 ].r = 238;
s.segment[ 1 ].patternColor[ 0 ].g = 210;
s.segment[ 1 ].patternColor[ 0 ].b = 165;
s.segment[ 2 ].span = 1;
s.segment[ 2 ].speed = 0;
s.segment[ 2 ].patternColor[ 1 ].span = 128;
s.segment[ 2 ].patternColor[ 1 ].r = 48;
s.segment[ 2 ].patternColor[ 1 ].g = 60;
s.segment[ 2 ].patternColor[ 1 ].b = 64;
}

void calculateActualSegmentlengths(void){
	
	int givenSegmentsTotal, calculatedTotal;

	if(modbusReceived == 1)
	{
		if(s.segment[ 0 ].span != 0) s.segment[ 0 ].span = (uint8_t)modbusRegisters[11];
		if(s.segment[ 1 ].span != 0) s.segment[ 1 ].span = (uint8_t)modbusRegisters[12];
		if(s.segment[ 2 ].span != 0) s.segment[ 2 ].span = (uint8_t)modbusRegisters[13];
		if(s.segment[ 3 ].span != 0) s.segment[ 3 ].span = (uint8_t)modbusRegisters[14];
	}
		
	givenSegmentsTotal = s.segment[ 0 ].span + s.segment[ 1 ].span + s.segment[ 2 ].span + s.segment[ 3 ].span;

	s.segment[ 0 ].span = (ledCount * s.segment[ 0 ].span) / givenSegmentsTotal;
	s.segment[ 1 ].span = (ledCount * s.segment[ 1 ].span) / givenSegmentsTotal;
	s.segment[ 2 ].span = (ledCount * s.segment[ 2 ].span) / givenSegmentsTotal;
	s.segment[ 3 ].span = (ledCount * s.segment[ 3 ].span) / givenSegmentsTotal;
	
	calculatedTotal = s.segment[ 0 ].span + s.segment[ 1 ].span + s.segment[ 2 ].span + s.segment[ 3 ].span;
		
	s.segment[0].speed *= -1;
	s.segment[1].speed *= -1;
	s.segment[2].speed *= -1;
	s.segment[3].speed *= -1;
	
	//if(calculatedTotal < ledCount)
	//	s.segment[ 3 ].span	+= (ledCount - calculatedTotal);
}


static int lastState = -1;

void selectContent(int state){
	
	state = state & 0x0FFF;
	
	previousState = state;
	
	resetSegments();
	
	switch(state){
		
		    
		case 0x0000:
			startupContent();
			break;
		case 0x0010:
			readyContent();
			break;
		case 0x0020:
			selection();
			break;
		case 0x0030:
			cycling1();
			break;
		case 0x0031:
			cycling2();
			break;
		case 0x0032:
			cycling3();
			break;
		case 0x0040:
			done1();
			break;
		case 0x0041:
			done2();
			break;
		case 0x0042:
			done3();
			break;
		case 0x0050:
			exampleGradientContent();
			break;
		case 0x0060:
			outOfOrder();
			break;
		case 0x0070:
			emergencyStop();
			break;
		case 0x00D0:
			delayedStart1();
			break;
		case 0x00D1:
			delayedStart2();
			break;
		case 0x0080:
			payment1();
			break;
		case 0x0081:
			payment2();
			break;
		case 0x0082:
			payment3();
			break;
		case 0x0090:
			welcome();
			break;
		case 0x0091:
			welcome();
			break;
		case 0x00A0:
			thankyou();
			break;
		case 0x00B0:
			outofWorkingHours();
			break;
		case 0x00C0:
			wizard();
			break;
	}
	
	calculateActualSegmentlengths();
	   if (state != lastState) {
        initSegmentTransition();
        lastState = state;
			
    }
}