#pragma once

//#include <windows.h>
//#include <stdlib.h>
#include <stdint.h>
#include "Math.h"
#include "Input.h"

class UnitBase
{
public:
	UnitBase(float width, float heigth, Vector2d& position, Vector2d& speed, Color4c& color);
	~UnitBase() = default;

	virtual void Process(float dt);
	virtual void Draw(uint32_t* buf, uint32_t w, uint32_t h);
	virtual void TestCollision(UnitBase* unit);

	float Width;
	float Heigth;
	Vector2d Position;
	Vector2d Speed;
	Vector2d Acceleration{0.0, 0.0};
	Color4c Color;
};

class Ball : public UnitBase
{
public:
	Ball(float width, float heigth, Vector2d& position, Vector2d& speed, Color4c& color);
	~Ball() = default;

	//virtual void Process(float dt) override;
	//virtual void Draw(uint32_t* buf) override;
};

class Brick : public UnitBase
{
public:
	Brick(float width, float heigth, Vector2d& position, Vector2d& speed, Color4c& color);
	~Brick() = default;

	//virtual void Process(float dt) override;
	//virtual void Draw(uint32_t* buf, uint32_t w, uint32_t h) override;
};

class Actor : public UnitBase, public InputBase
{
public:
	Actor(float width, float heigth, Vector2d& position, Vector2d& speed, Color4c& color);
	~Actor() = default;

	virtual void Input(InputKey& key) override;
	virtual void Process(float dt) override;

	float InputAcceleration{ 1000 };
	//virtual void Draw(uint32_t* buf, uint32_t w, uint32_t h) override;
};
