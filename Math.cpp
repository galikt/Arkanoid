#include "Math.h"
#include <cmath>

Vector2d::Vector2d(float x, float y) :
	X(x), Y(y)
{
}
//********************************************************************************

Vector2d Vector2d::operator+(const Vector2d& v) const
{
	return Vector2d(X + v.X, Y + v.Y);
}
//********************************************************************************

Vector2d Vector2d::operator-(const Vector2d& v) const
{
	return Vector2d(X - v.X, Y - v.Y);
}
//********************************************************************************
Vector2d Vector2d::operator*(const Vector2d& v) const
{
	return Vector2d(X * v.X, Y * v.Y);
}
//********************************************************************************

Vector2d Vector2d::operator/(const Vector2d& v) const
{
	return Vector2d(X / v.X, Y / v.Y);
}
//********************************************************************************

Vector2d Vector2d::operator+=(const Vector2d& v)
{
	X += v.X;
	Y += v.Y;
	return *this;
}
//********************************************************************************

Vector2d Vector2d::operator-=(const Vector2d& v)
{
	X -= v.X;
	Y -= v.Y;
	return *this;
}
//********************************************************************************

Vector2d Vector2d::operator*=(const Vector2d& v)
{
	X *= v.X;
	Y *= v.Y;
	return *this;
}
//********************************************************************************

Vector2d Vector2d::operator/=(const Vector2d& v)
{
	X /= v.X;
	Y /= v.Y;
	return *this;
}
//********************************************************************************

Vector2d Vector2d::operator*=(const float& s)
{
	X *= s;
	Y *= s;
	return *this;
}
//********************************************************************************

Vector2d Vector2d::operator/=(const float& s)
{
	X /= s;
	Y /= s;
	return *this;
}
//********************************************************************************

float Vector2d::operator|(const Vector2d& v) const
{
	return (X * v.X) + (Y * v.Y);
}
//********************************************************************************

float Vector2d::operator^(const Vector2d& v) const
{
	return (X * v.X) - (Y * v.Y);
}
//********************************************************************************

Vector2d Vector2d::operator+(const float& s) const
{
	return Vector2d(X + s, Y + s);
}
//********************************************************************************

Vector2d Vector2d::operator-(const float& s) const
{
	return Vector2d(X - s, Y - s);
}
//********************************************************************************

Vector2d Vector2d::operator*(const float& s) const
{
	return Vector2d(X * s, Y * s);
}
//********************************************************************************

Vector2d Vector2d::operator/(const float& s) const
{
	return Vector2d(X / s, Y / s);
}
//********************************************************************************

void Vector2d::Normalize()
{
	*this *= 1.0f / std::sqrtf((X * X) + (Y * Y));
}
//********************************************************************************

void Vector2d::Invert()
{
	X = -X;
	Y = -Y;
}
//********************************************************************************

float Vector2d::Length()
{
	return (X * X) + (Y * Y);
}
//********************************************************************************
//********************************************************************************

Color4c::Color4c(uint32_t r, uint32_t g, uint32_t b) :
	R(r), G(g), B(b)
{
	rgba = ColorToInt();
}
//********************************************************************************

uint32_t Color4c::ColorToInt()
{
	uint32_t result = B;
	result |= G << 8;
	result |= R << 16;
	result |= 0 << 24;

	return result;
}