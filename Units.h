#pragma once

//#include <windows.h>
//#include <stdlib.h>
#include <stdint.h>
#include "Math.h"
#include "Input.h"

class UnitBase
{
public:
	UnitBase(float width, float heigth, Vector2d& position, Vector2d& speed);
	~UnitBase() = default;

	virtual void Process(float dt);
	virtual void Draw(uint32_t* buf, uint32_t w, uint32_t h);

	float Width;
	float Heigth;
	Vector2d Position;
	Vector2d Speed;
};

class Ball : public UnitBase
{
public:
	Ball(float width, float heigth, Vector2d& position, Vector2d& speed);
	~Ball() = default;

	//virtual void Process(float dt) override;
	//virtual void Draw(uint32_t* buf) override;
};

class Brick : public UnitBase
{
public:
	Brick(float width, float heigth, Vector2d& position, Vector2d& speed);
	~Brick() = default;

	//virtual void Process(float dt) override;
	virtual void Draw(uint32_t* buf, uint32_t w, uint32_t h) override;
};

class Actor : public UnitBase, public InputBase
{
public:
	Actor(float width, float heigth, Vector2d& position, Vector2d& speed);
	~Actor() = default;

	virtual void Input(InputKey& key) override;
	//virtual void Process(float dt) override;
	//virtual void Draw(uint32_t* buf, uint32_t w, uint32_t h) override;
};
