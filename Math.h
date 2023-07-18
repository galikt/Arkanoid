#pragma once

#include <stdint.h>

extern uint32_t ColorTo(uint32_t r, uint32_t g, uint32_t b);

class Vector2d
{
public:
	Vector2d(float x, float y);
	~Vector2d() = default;

	float X;
	float Y;
};
