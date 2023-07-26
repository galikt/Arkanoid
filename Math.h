#pragma once

#include <stdint.h>

class Vector2d
{
public:
	Vector2d(float x, float y);
	~Vector2d() = default;

	Vector2d operator+(const Vector2d& v) const;
	Vector2d operator-(const Vector2d& v) const;
	Vector2d operator*(const Vector2d& v) const;
	Vector2d operator/(const Vector2d& v) const;

	Vector2d operator+=(const Vector2d& v);
	Vector2d operator-=(const Vector2d& v);
	Vector2d operator*=(const Vector2d& v);
	Vector2d operator/=(const Vector2d& v);
	Vector2d operator*=(const float& s);
	Vector2d operator/=(const float& s);

	float operator|(const Vector2d& v) const;
	float operator^(const Vector2d& v) const;

	Vector2d operator+(const float& s) const;
	Vector2d operator-(const float& s) const;
	Vector2d operator*(const float& s) const;
	Vector2d operator/(const float& s) const;

	void Normalize();
	void Invert();
	float Length();

	float X;
	float Y;
};

class Color4c
{
public:
	Color4c(uint32_t r, uint32_t g, uint32_t b);
	~Color4c() = default;

	inline void SetColor(uint32_t r, uint32_t g, uint32_t b);
	inline uint32_t GetColor();
	inline uint32_t GetR() const;
	inline uint32_t GetG() const;
	inline uint32_t GetB() const;

protected:
	uint32_t R;
	uint32_t G;
	uint32_t B;
	uint32_t rgba;

	uint32_t ColorToInt();
};

void Color4c::SetColor(uint32_t r, uint32_t g, uint32_t b)
{
	R = r;
	G = g;
	B = b;
	rgba = ColorToInt();
}

uint32_t Color4c::GetColor()
{
	return rgba;
}

inline uint32_t Color4c::GetR() const
{
	return R;
}

inline uint32_t Color4c::GetG() const
{
	return G;
}

inline uint32_t Color4c::GetB() const
{
	return B;
}
