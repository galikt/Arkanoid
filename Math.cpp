#include "Math.h"

Vector2d::Vector2d(float x, float y) :
	X(x), Y(y)
{
}

Color4c::Color4c(uint32_t r, uint32_t g, uint32_t b)
{
	rgba = ColorToInt(r, g, b);
}

uint32_t Color4c::ColorToInt(uint32_t r, uint32_t g, uint32_t b)
{
	uint32_t result = b;
	result |= g << 8;
	result |= r << 16;
	result |= 0 << 24;

	return result;
}