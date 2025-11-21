#ifndef COLOR_STRUCTS
#define COLOR_STRUCTS

#include <stdint.h>

struct Color{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct CubicGradient{
	struct Color rgb0;
	struct Color rgb1;
	struct Color rgb2;
	struct Color rgb3;
	uint16_t u0;
	uint16_t u1;
};

struct BiCubicGradient{
	struct Color p0;
	struct Color p1;
	struct Color p2;
	struct Color p3;
	struct Color q0;
	struct Color q1;
	struct Color q2;
	struct Color q3;
	struct Color r0;
	struct Color r1;
	struct Color r2;
	struct Color r3;
	struct Color s0;
	struct Color s1;
	struct Color s2;
	struct Color s3;
	uint16_t u0;
	uint16_t u1;
	uint16_t v0;
	uint16_t v1;
};

#endif