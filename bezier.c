#include "bezier.h"

#define parameterMid 32767

struct Color setColor(uint8_t r, uint8_t g, uint8_t b)
{
	struct Color res;
	res.r = r;
	res.g = g;
	res.b = b;
	
	return res;
}

int linear(int p0, int p1, uint16_t t)
{
	int correction, result;
	if(p0 < p1)
		correction = parameterMid;
	else
		correction = parameterMid * -1;
	
	result = (p1 - p0);
	result *= t;
	result += correction;
	result /= 65536;
	result += p0;
	
	return result;
}

int quadratic(int p0, int p1, int p2, uint16_t t)
{
	int res1, res2, res3;
	res1 = linear(p0, p1, t);
	res2 = linear(p1, p2, t);
	res3 = linear(res1, res2, t);
	
	return res3;
}

int cubic(int p0, int p1, int p2, int p3, uint16_t t)
{
	int res1, res2, res3;
	res1 = quadratic(p0, p1, p2, t);
	res2 = quadratic(p1, p2, p3, t);
	res3 = linear(res1, res2, t);
	
	return res3;
}

struct Color cubicGradient(struct CubicGradient g, uint16_t t)
{
	struct Color resultColor;
	uint16_t biasT;
	
	biasT = (uint16_t)cubic(0, (int)g.u0, (int)g.u1, 65535, t);
	
	resultColor.r = (uint8_t)cubic((int)g.rgb0.r,(int)g.rgb1.r,(int)g.rgb2.r,(int)g.rgb3.r, biasT);
	resultColor.g = (uint8_t)cubic((int)g.rgb0.g,(int)g.rgb1.g,(int)g.rgb2.g,(int)g.rgb3.g, biasT);
	resultColor.b = (uint8_t)cubic((int)g.rgb0.b,(int)g.rgb1.b,(int)g.rgb2.b,(int)g.rgb3.b, biasT);
	
	return resultColor;
}

struct Color biCubicGradient(struct BiCubicGradient b, uint16_t u, uint16_t v)
{
		struct CubicGradient g0,g1,g2,g3, gResult;
		struct Color cResult;
	
		g0.rgb0 = b.p0;
		g0.rgb1 = b.p1;
		g0.rgb2 = b.p2;
		g0.rgb3 = b.p3;
		g0.u0 = b.u0;
		g0.u1 = b.u1;
	
		gResult.rgb0 = cubicGradient(g0, u);
		
		g1.rgb0 = b.q0;
		g1.rgb1 = b.q1;
		g1.rgb2 = b.q2;
		g1.rgb3 = b.q3;
		g1.u0 = b.u0;
		g1.u1 = b.u1;
	
		gResult.rgb1 = cubicGradient(g1, u);
	
		g2.rgb0 = b.r0;
		g2.rgb1 = b.r1;
		g2.rgb2 = b.r2;
		g2.rgb3 = b.r3;
		g2.u0 = b.u0;
		g2.u1 = b.u1;

		gResult.rgb2 = cubicGradient(g2, u);

		g3.rgb0 = b.s0;
		g3.rgb1 = b.s1;
		g3.rgb2 = b.s2;
		g3.rgb3 = b.s3;
		g3.u0 = b.u0;
		g3.u1 = b.u1;

		gResult.rgb3 = cubicGradient(g3, u);
		
		gResult.u0 = b.v0;
		gResult.u1 = b.v1;
		
		cResult = cubicGradient(gResult, v);
		
		return cResult;
}
		