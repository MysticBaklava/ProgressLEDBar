#include "main.h"
#include "led_drive.h"
#include "bezier.h"


uint32_t segBuf[4][96];
struct Color color;

void getColor(uint16_t segmentNr, uint16_t colorNr);
void createSegment(uint16_t totalLen, uint16_t segmentNr);	
uint16_t calculateTotalSegmentLen(void);
uint16_t calculateSegmentsLen(uint16_t segmentNr, uint16_t totalLen);
uint32_t smear(uint32_t prev, uint32_t next, int speed, int timing);
uint16_t animationRunning = 0;
//------------------------------------------------------------------------------------------

void getColor(uint16_t segmentNr, uint16_t colorNr){
	color.r = s.segment[segmentNr].patternColor[colorNr].r;														//get the pattern color value
	color.g = s.segment[segmentNr].patternColor[colorNr].g;
	color.b = s.segment[segmentNr].patternColor[colorNr].b;
}

void createSegment(uint16_t totalLen, uint16_t segmentNr){
	//her segmentin 64 ledlik bufferi var. 
	uint16_t segmentLen, animationLen;	
	uint16_t totalColorSpan, colorSpan, colorNr;
	uint16_t i,j,k;
	
	if(s.segment[segmentNr].span == 0) return;																		//this is the segments rational len to the physical led strip, if zero, do not render
	
	totalColorSpan = 0;
	segmentLen = calculateSegmentsLen(segmentNr, totalLen);												//count the segment's actual lenght
	s.segment[segmentNr].ledCount = segmentLen;
	
	for(i=0;i<4;i++)
		totalColorSpan += s.segment[segmentNr].patternColor[i].span;	
	
	if(totalColorSpan > segmentLen)
			animationLen = totalColorSpan;
	else
			animationLen = segmentLen;
	
	colorNr = 0;
	j = 0;
	animationLen = 64;
	while(animationLen > 0)
	{
		colorSpan = s.segment[segmentNr].patternColor[colorNr].span;	
		
		if(colorSpan > 0)
		{				
			getColor(segmentNr, colorNr);
			for(k=0;k<colorSpan;k++)
			{
					segBuf[segmentNr][j++] = calculateGammaColorRGB(color);					
					if(--animationLen == 0) break;						
			}
		}
		
		if(colorNr++ == 4) colorNr = 0;			
	}
	/*
	i = 0;
	while(i < 63)
	{
		if(segBuf[segmentNr][i] != segBuf[segmentNr][i+1])
		{
			segBuf[segmentNr][i] = smooth(segBuf[segmentNr][i], segBuf[segmentNr][i+1], 5000);
			segBuf[segmentNr][i+1] = smooth(segBuf[segmentNr][i], segBuf[segmentNr][i+1], 28000);
			i++;
		}
		i++;
	}
	*/
	if(s.segment[segmentNr].speed > 0){
		if(s.segment[segmentNr].animCount++ == 64){
			s.segment[segmentNr].animCount = 0;
		}
	}
}


uint16_t calculateTotalSegmentLen(void){
	uint16_t totalSegmentLen;
	totalSegmentLen = s.segment[0].span + s.segment[1].span + s.segment[2].span + s.segment[3].span;
	return totalSegmentLen;
}

uint16_t calculateSegmentsLen(uint16_t segmentNr, uint16_t totalLen){
	uint16_t segmentLen;
	
	segmentLen = (uint16_t)(((s.segment[segmentNr].span * 100) / totalLen) * ledCount) / 100;				//count the segment's actual lenght
	return segmentLen;
}


static uint32_t oldLedBuffer[100];
static uint16_t transitionPos = 0;
static const uint16_t transitionStep = 1;  // Her frame'de kaç LED ilerlesin
static uint8_t transitioning = 0;


void initSegmentTransition(void) {
    memcpy(oldLedBuffer, led, ledCount * sizeof(uint32_t));
    transitionPos = 0;
    transitioning = 1;
}



void segmentsRender(void) {
    for (int segmentNr = 0; segmentNr < 4; segmentNr++) {
        if (s.segment[segmentNr].span > 0) {
            switch (s.segment[segmentNr].renderMode) {
                case RENDER_STANDARD: {
                    int k = 0;
                    while (k < 64) {
                        for (int clr = 0; clr < 4; clr++) {
                            uint8_t span = s.segment[segmentNr].patternColor[clr].span;
                            if (span > 0) {
                                color.r = s.segment[segmentNr].patternColor[clr].r;
                                color.g = s.segment[segmentNr].patternColor[clr].g;
                                color.b = s.segment[segmentNr].patternColor[clr].b;
                                uint32_t gammaColor = calculateGammaColorRGB(color);
                                for (int j = 0; j < span && k < 64; j++) {
                                    segBuf[segmentNr][k++] = gammaColor;
                                }
                            }
                        }
                    }
                    break;
                }
                case RENDER_CUBIC: {
                    for (int j = 0; j < 64; j++) {
                        uint16_t t = (uint16_t)((65535UL * j) / 63);
                        struct Color gradCol = cubicGradient(s.segment[segmentNr].cubicGradient, t);
                        uint32_t gammaColor = calculateGammaColorRGB(gradCol);
                        segBuf[segmentNr][j] = gammaColor;
                    }
                    break;
                }
                case RENDER_BICUBIC: {
                    uint16_t v_param = 32767;
                    for (int j = 0; j < 64; j++) {
                        uint16_t u_param = (uint16_t)(j * 1024);
                        struct Color gradCol = biCubicGradient(s.segment[segmentNr].biCubicGradient, u_param, v_param);
                        uint32_t gammaColor = calculateGammaColorRGB(gradCol);
                        segBuf[segmentNr][j] = gammaColor;
                    }
                    break;
                }
            }

            if (s.segment[segmentNr].speed > 0) {
                for (int j = 1; j < 64; j++) {
                    if (segBuf[segmentNr][j] != segBuf[segmentNr][j - 1]) {
                        segBuf[segmentNr][j - 1] = smear(segBuf[segmentNr][j - 1], segBuf[segmentNr][j],
                                                        s.segment[segmentNr].speed, s.segment[segmentNr].timing);
                    }
                    if (j == 63) {
                        segBuf[segmentNr][63] = smear(segBuf[segmentNr][63], segBuf[segmentNr][0],
                                                     s.segment[segmentNr].speed, s.segment[segmentNr].timing);
                    }
                }
            } else if (s.segment[segmentNr].speed < 0) {
                for (int j = 63; j > 0; j--) {
                    if (j < 63 && segBuf[segmentNr][j] != segBuf[segmentNr][j + 1]) {
                        segBuf[segmentNr][j + 1] = smear(segBuf[segmentNr][j + 1], segBuf[segmentNr][j],
                                                        s.segment[segmentNr].speed, s.segment[segmentNr].timing);
                    }
                    if (j == 63 && segBuf[segmentNr][0] != segBuf[segmentNr][63]) {
                        segBuf[segmentNr][63] = smear(segBuf[segmentNr][0], segBuf[segmentNr][63],
                                                     s.segment[segmentNr].speed, s.segment[segmentNr].timing);
                    }
                }
            }
        }
    }

    int j = 0;
    for (segmentNr = 0; segmentNr < 4; segmentNr++) {
        int m = s.segment[segmentNr].animCount;
        for (int i = 0; i < s.segment[segmentNr].span; i++) {
            led[j++] = segBuf[segmentNr][m];
            if (++m >= 64) m = 1;
        }

        if (s.segment[segmentNr].timing <= 0) {
            animationRunning = 0;
            s.segment[segmentNr].timing = s.segment[segmentNr].speed;
            if (s.segment[segmentNr].timing < 0)
                s.segment[segmentNr].timing *= -1;

            if (s.segment[segmentNr].speed > 0) {
                s.segment[segmentNr].animCount++;
                if (s.segment[segmentNr].animCount >= 64)
                    s.segment[segmentNr].animCount = 0;
            } else if (s.segment[segmentNr].speed < 0) {
                s.segment[segmentNr].animCount--;
                if (s.segment[segmentNr].animCount <= 0)
                    s.segment[segmentNr].animCount = 63;
            }
        } else {
            s.segment[segmentNr].timing--;
            animationRunning = 1;
        }
    }

    if (transitioning) {
        for (uint16_t i = transitionPos; i < ledCount; i++) {
            led[i] = oldLedBuffer[i];
        }
        transitionPos += transitionStep;
        if (transitionPos >= ledCount) {
            transitioning = 0;
        }
    }
    fillLedBar();
}


uint32_t smear(uint32_t prev, uint32_t next, int speed, int timing){
	int r1,g1,b1;
	int r2,g2,b2;
	int r3,g3,b3;
	uint32_t result;
	
	int prevWeight, nextWeight;

	if(speed < 0) speed *= -1;
	if(timing < 0) timing *= -1;
	
	prevWeight = timing;
	nextWeight = speed - timing;
	
	g1 = (prev & 0xFF0000) >> 16;
	r1 = (prev & 0x00FF00) >> 8;
	b1 = (prev & 0x0000FF) ;
	
	g2 = (next & 0xFF0000) >> 16;
	r2 = (next & 0x00FF00) >> 8;
	b2 = (next & 0x0000FF) ;
	
	g3 = (g1 * prevWeight + g2 * nextWeight) / speed;
	r3 = (r1 * prevWeight + r2 * nextWeight) / speed;
	b3 = (b1 * prevWeight + b2 * nextWeight) / speed;
	
	result = (g3 << 16) | (r3 << 8) | (b3);
	
	return result;
}
