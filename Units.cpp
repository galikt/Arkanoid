#include "Units.h"
#include <iostream>

UnitBase::UnitBase(float width, float heigth, Vector2d& position, Vector2d& speed, Color4c& color) :
	Width(width), Heigth(heigth), Position(position), Speed(speed), Color(color)
{
}

void UnitBase::Process(float dt)
{
	Speed.X += Acceleration.X;
	Speed.Y += Acceleration.Y;

	Position.X += Speed.X * dt;
	Position.Y += Speed.Y * dt;

	Speed.X = 0.0f;
	Speed.Y = 0.0f;
}

void UnitBase::Draw(uint32_t* buf, uint32_t w, uint32_t h)
{
	uint32_t begin_x = (uint32_t)Position.X;
	uint32_t begin_y = (uint32_t)Position.Y;

	uint32_t max_x = begin_x + (uint32_t)Width;
	uint32_t max_y = begin_y + (uint32_t)Heigth;

	if (max_x > w)
		max_x = w;

	if (max_y > h)
		max_y = h;

	for (uint32_t y = begin_y; y < max_y; ++y)
	{
		for (uint32_t x = begin_x; x < max_x; ++x)
		{
			buf[(y * w) + x] = Color.GetColor();
		}
	}
}

void UnitBase::TestCollision(UnitBase* unit)
{
	if ((Position.X >= unit->Position.X) && (Position.X <= unit->Position.X + unit->Width))
	{
		if ((Position.Y >= unit->Position.Y) && (Position.Y <= unit->Position.Y + unit->Heigth))
		{
			Acceleration.Y = -Acceleration.Y;
			Acceleration.X = -Acceleration.X;
			unit->Acceleration.Y = -unit->Acceleration.Y;
			unit->Acceleration.X = -unit->Acceleration.X;
		}
	}
}

Ball::Ball(float width, float heigth, Vector2d& position, Vector2d& speed, Color4c& color) :
	UnitBase(width, heigth, position, speed, color)
{
}

Brick::Brick(float width, float heigth, Vector2d& position, Vector2d& speed, Color4c& color) :
	UnitBase(width, heigth, position, speed, color)
{
}

Actor::Actor(float width, float heigth, Vector2d& position, Vector2d& speed, Color4c& color) :
	UnitBase(width, heigth, position, speed, color), InputBase()
{
	Acceleration = { 1000.0f, 0.0f };
}

void Actor::Input(InputKey& key)
{
	switch (key)
	{
	case InputKey::LEFT:
	{
		Acceleration.X = -InputAcceleration;
		break;
	}
	case InputKey::RIGHT:
	{
		Acceleration.X = InputAcceleration;
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

void Actor::Process(float dt)
{
	UnitBase::Process(dt);

	Acceleration.X = 0.0f;
	Acceleration.Y = 0.0f;
}

//void Brick::Draw(uint32_t* buf, uint32_t w, uint32_t h)
//{
//
//}
