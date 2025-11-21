// test scenes
#include "main.h"
#include "bezier.h"


void sceneNumber(uint8_t num)
{
	setGammaColor(num-1, 0xFF0000);
		fillLedBar();
		delay(100);
		setGammaColor(num-1, 0x000000);
		fillLedBar();
		delay(100);
}

void scene1(void)
{
	uint16_t i;
	
	for(i=0;i<64;i++)
		led[i] = 0xFFFFFF;
	//	setGammaColor(i, 0xFFFFFF);			//Beyaz
	
	fillLedBar();
}

void scene2(void)
{
	uint16_t i,j;

	uint32_t colors[] = {	
		0xff7300,
		0xff7300,
		0xfc9121,
		0xf6a941,
		0xebbc5e,
		0xdfca79,
		0xd0d191,
		0xc0d2a4,
		0xb0cdb5,
		0xa0c1c1,
		0x91aec8,
		0x8493cb,
		0x7b71c9,
		0x7548c0,
		0x7316b1
	};

	for(j=0;j<15;j++)
	{
		for(i=0;i<64;i++)
		{
			setGammaColor(i, colors[j]);			//RED
		}
		
		fillLedBar();
		delay(20);
	}
	
}

void scene3(void)
{
	uint16_t i, j, k;
	j = 0;

	for(k=0;k<64;k++)
	{		
		for(i=0;i<j;i++)
			setGammaColor(i, 0x7F6B00);			//YEL
		
		for(i=j;i<j+20;i++)
			setGammaColor(i, 0xFF0000);			//RED
		
		for(i=j+20;i<64;i++)
			setGammaColor(i, 0x7F6B00);			//YEL
		
		fillLedBar();
		
		delay(1);
		j=j+1;
		
		if(j==64) j = 0;
	}	
}

void bicubicScene1(void)
{

	uint16_t ledNumber;
	uint32_t u,v;	
	
	struct Color resultRGB;
	
	struct BiCubicGradient b;
	uint8_t c[3];
	
	b.p0 = setColor(0,0,0);
	b.p1 = setColor(0,0,0);
	b.p2 = setColor(0,0,0);
	b.p3 = setColor(0,0,0);
	
	b.q0 = setColor(249,101,27);
	b.q1 = setColor(255,0,0);
	b.q2 = setColor(0,0,0);
	b.q3 = setColor(0,0,0);
	
	b.r0 = setColor(249, 101, 27);
	b.r1 = setColor(255,0,0);
	b.r2 = setColor(0,0,0);
	b.r3 = setColor(0,0,0);

	b.s0 = setColor(249, 101, 27);
	b.s1 = setColor(249, 101, 27);
	b.s2 = setColor(249, 101, 27);
	b.s3 = setColor(249, 101, 27);

	b.u0 = 31487;
  b.u1 = 50687;
  b.v0 = 36095;
  b.v1 = 65535;
	
	for(v=0;v<65535;v=v+64)
	{
		for(ledNumber=0;ledNumber<64;ledNumber++)
		{
			resultRGB = biCubicGradient(b,ledNumber * 1024, v);
			setGammaColorRGB(ledNumber, resultRGB);			
		}
		fillLedBar();
		//delay(20);
	}
}

void bicubicScene2(void)
{
	
	uint16_t ledNumber;
	uint32_t u,v;	
	
	struct Color resultRGB;
	
	struct BiCubicGradient b;
	
	b.p0 = setColor(249,101,27);
	b.p1 = setColor(249,101,27);
	b.p2 = setColor(249,101,27);
	b.p3 = setColor(249,101,27);
	
	b.q0 = setColor(255,214,0);
	b.q1 = setColor(41,179,210);
	b.q2 = setColor(41,179,210);
	b.q3 = setColor(249,101,27);
	
	b.r0 = setColor(0, 179, 115);
	b.r1 = setColor(41, 179, 210);
	b.r2 = setColor(41, 179, 210);
	b.r3 = setColor(249, 101, 27 );

	b.s0 = setColor(41, 179, 210);
	b.s1 = setColor(41, 179, 210);
	b.s2 = setColor(41, 179, 210);
	b.s3 = setColor(41, 179, 210);

	b.u0 = 0;
  b.u1 = 10495;
  b.v0 = 34047;	
  b.v1 = 31999;
	
	for(v=0;v<65535;v=v+64)
	{
		for(ledNumber=0;ledNumber<64;ledNumber++)
		{
			resultRGB = biCubicGradient(b,ledNumber * 1024, v);
			setGammaColorRGB(ledNumber, resultRGB);			
		}
		fillLedBar();
		//delay(20);
	}
}

void bicubicScene3(void)
{
	uint16_t ledNumber;
	uint32_t u,v;	
	
	struct Color resultRGB;
	
	struct BiCubicGradient b;
	
	b.p0 = setColor(41, 179, 210);
	b.p1 = setColor(41, 179, 210);
	b.p2 = setColor(41, 179, 210);
	b.p3 = setColor(41, 179, 210);
	
	b.q0 = setColor(0, 0, 0);
	b.q1 = setColor(0,179,115);
	b.q2 = setColor(41,179,210);
	b.q3 = setColor(0,0,0);
	
	b.r0 = setColor(0,0,0);
	b.r1 = setColor(41, 179, 210);
	b.r2 = setColor(0, 179, 115);
	b.r3 = setColor(0,0,0);

	b.s0 = setColor(0, 179, 115);
	b.s1 = setColor(0, 179, 115);
	b.s2 = setColor(0, 179, 115);
	b.s3 = setColor(0, 179, 115);

	b.u0 = 0;
  b.u1 = 54527;
  b.v0 = 0;	
  b.v1 = 60927;
	
	for(v=0;v<65535;v=v+64)
	{
		for(ledNumber=0;ledNumber<64;ledNumber++)
		{
			resultRGB = biCubicGradient(b,ledNumber * 1024, v);
			setGammaColorRGB(ledNumber, resultRGB);			
		}
		fillLedBar();
		//delay(20);
	}
}

void bicubicScene4(void)
{
	uint16_t ledNumber;
	uint32_t u,v;	
	
	struct Color resultRGB;
	
	struct BiCubicGradient b;
	
	b.p0 = setColor(0, 179, 115);
	b.p1 = setColor(0, 179, 115);
	b.p2 = setColor(0, 179, 115);
	b.p3 = setColor(0, 179, 115);
	
	b.q0 = setColor(255, 214, 0);
	b.q1 = setColor(0, 0, 0);
	b.q2 = setColor(0, 0, 0);
	b.q3 = setColor(0, 179, 115);
	
	b.r0 = setColor( 255, 214, 0);
	b.r1 = setColor(255, 214, 0);
	b.r2 = setColor(0, 0, 0);
	b.r3 = setColor(0, 179, 115 );

	b.s0 = setColor( 255, 214, 0);
	b.s1 = setColor( 255, 214, 0);
	b.s2 = setColor( 255, 214, 0);
	b.s3 = setColor( 255, 214, 0);

	b.u0 = 12288;
  b.u1 = 53503;
  b.v0 = 9472;	
  b.v1 = 50175;
	
	for(v=0;v<65535;v=v+64)
	{
		for(ledNumber=0;ledNumber<64;ledNumber++)
		{
			resultRGB = biCubicGradient(b,ledNumber * 1024, v);
			setGammaColorRGB(ledNumber, resultRGB);			
		}
		fillLedBar();
		//delay(20);
	}
}

void bicubicScene5(void)
{
	uint16_t ledNumber;
	uint32_t u,v;	
	
	struct Color resultRGB;
	
	struct BiCubicGradient b;
	
	b.p0 = setColor(255, 214, 0);
	b.p1 = setColor(255, 214, 0);
	b.p2 = setColor(255, 214, 0);
	b.p3 = setColor(255, 214, 0);
	
	b.q0 = setColor(249, 101, 27);
	b.q1 = setColor(249, 101, 27);
	b.q2 = setColor(255, 214, 0);
	b.q3 = setColor(255, 214, 0);
	
	b.r0 = setColor( 0,0,0);
	b.r1 = setColor(249, 101, 27);
	b.r2 = setColor(249, 101, 27);
	b.r3 = setColor(255, 214, 0 );

	b.s0 = setColor( 0, 0, 0);
	b.s1 = setColor( 0, 0, 0);
	b.s2 = setColor( 0, 0, 0);
	b.s3 = setColor( 0, 0, 0);

	b.u0 = 0;
  b.u1 = 26367;
  b.v0 = 23296;	
  b.v1 = 60927;
	
	for(v=0;v<65535;v=v+64)
	{
		for(ledNumber=0;ledNumber<64;ledNumber++)
		{
			resultRGB = biCubicGradient(b,ledNumber * 1024, v);
			setGammaColorRGB(ledNumber, resultRGB);			
		}
		fillLedBar();
		//delay(20);
	}
}


