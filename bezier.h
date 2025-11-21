#include <stdio.h>
#include <stdint.h>
#include "color_structs.h"


struct Color setColor(uint8_t r, uint8_t g, uint8_t b);
int linear(int p0, int p1, uint16_t t);
int quadratic(int p0, int p1, int p2, uint16_t t);
int cubic(int p0, int p1, int p2, int p3, uint16_t t);
struct Color cubicGradient(struct CubicGradient g, uint16_t t);
struct Color biCubicGradient(struct BiCubicGradient b, uint16_t u, uint16_t v);

int createBezier(void);
