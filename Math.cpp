#include "Math.h"

Vector2d::Vector2d(float x, float y) :
	X(x), Y(y)
{
}

uint32_t ColorTo(uint32_t r, uint32_t g, uint32_t b)
{
	uint32_t result = b;
	result |= g << 8;
	result |= r << 16;
	result |= 0 << 24;

	return result;
}