#include "Units.h"
#include <iostream>

UnitBase::UnitBase(float width, float heigth, Vector2d& position, Vector2d& speed) :
	Width(width), Heigth(heigth), Position(position), Speed(speed)
{
}

void UnitBase::Process(float dt)
{
}

void UnitBase::Draw(uint32_t* buf, uint32_t w, uint32_t h)
{
}

Ball::Ball(float width, float heigth, Vector2d& position, Vector2d& speed) :
	UnitBase(width, heigth, position, speed)
{
}

Brick::Brick(float width, float heigth, Vector2d& position, Vector2d& speed) :
	UnitBase(width, heigth, position, speed)
{
}

Actor::Actor(float width, float heigth, Vector2d& position, Vector2d& speed) :
	UnitBase(width, heigth, position, speed), InputBase()
{
}

void Actor::Input(InputKey& key)
{
	switch (key)
	{
		case InputKey::LEFT:
		{

			break;
		}
		case InputKey::RIGHT:
		{

			break;
		}
		case InputKey::UP:
		{

			break;
		}
		case InputKey::DOWN:
		{

			break;
		}
	}
}

void Brick::Draw(uint32_t* buf, uint32_t w, uint32_t h)
{
	uint32_t begin_x = (uint32_t)Position.X;
	uint32_t begin_y = (uint32_t)Position.Y;

	uint32_t max_x = begin_x + (uint32_t)Width;
	uint32_t max_y = begin_y + (uint32_t)Heigth;

	for (uint32_t y = begin_y; y < max_y; ++y)
	{
		for (uint32_t x = begin_x; x < max_x; ++x)
		{
			buf[(y * w) + x] = ColorTo(255, 50, 50);
		}
	}
}
