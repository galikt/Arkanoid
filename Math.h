#pragma once

#include <stdint.h>



class Vector2d
{
public:
	Vector2d(float x, float y);
	~Vector2d() = default;

	float X;
	float Y;
};

class Color4c
{
public:
	Color4c(uint32_t r, uint32_t g, uint32_t b);
	~Color4c() = default;

	inline uint32_t GetColor();

protected:
	uint32_t R;
	uint32_t G;
	uint32_t B;
	uint32_t rgba;

	uint32_t ColorToInt(uint32_t r, uint32_t g, uint32_t b);
};

uint32_t Color4c::GetColor()
{
	return rgba;
}