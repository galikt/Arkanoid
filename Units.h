#pragma once

#include <stdint.h>
#include <memory>
#include <list>
#include <functional>
#include "Math.h"
#include "Input.h"

enum class UnitType
{
	Base,
	Ball,
	Brick,
	Actor,
	Triger,
	Pickup
};
//********************************************************************************
//********************************************************************************

class UnitBase
{
public:
	UnitBase(UnitType type, float width, float heigth, Vector2d position);
	~UnitBase() = default;

	virtual void Process(float dt);
	//virtual void PostProcess();
	virtual void Draw(uint32_t* buf, int32_t width, int32_t heigth);
	virtual void Attach(std::shared_ptr<UnitBase> parent, std::shared_ptr<UnitBase> unit);
	virtual void Detach(std::shared_ptr<UnitBase> unit);
	virtual void TestCollision(UnitBase* unit);
	virtual void OnCollision(UnitBase* unit, Vector2d& offset);

	UnitType Type{ UnitType::Base };
	uint32_t Id;
	float Width;
	float Heigth;
	Color4c Color{ 255,255,255 };
	Vector2d Position;
	Vector2d RelativePosition{ 0.0f, 0.0f };
	Vector2d Speed{ 0.0f, 0.0f };
	Vector2d Acceleration{ 0.0, 0.0 };

	bool Static{ true };
	bool Visible{ true };

	std::shared_ptr<UnitBase> Parent { nullptr };
	std::list<std::shared_ptr<UnitBase>> ChildList;
};
//********************************************************************************
//********************************************************************************

class UnitBall : public UnitBase
{
public:
	UnitBall(Vector2d position, float width = 15.0f, float heigth = 15.0f, Color4c color = Color4c(0, 255, 200));
	~UnitBall();

	virtual void Draw(uint32_t* buf, int32_t width, int32_t heigth) override;
	virtual void TestCollision(UnitBase* unit) override;
	virtual void OnCollision(UnitBase* unit, Vector2d& offset) override;
	static int32_t Count;
};
//********************************************************************************
//********************************************************************************

class UnitBrick : public UnitBase
{
public:
	UnitBrick(float width, float heigth, Vector2d position);
	~UnitBrick();

	virtual void OnCollision(UnitBase* unit, Vector2d& offset) override;
	void UpdateColor();

	bool Pickup{ false };
	int32_t Live{ 0 };
	static int32_t MaxLive;
	static uint32_t BaseColor;
	static int32_t Count;
};
//********************************************************************************
//********************************************************************************

class UnitActor : public UnitBase, public InputBase
{
public:
	UnitActor(float width, float heigth, Vector2d position, Color4c& color);
	~UnitActor() = default;

	virtual void Input(Keys& keys) override;
	virtual void OnCollision(UnitBase* unit, Vector2d& offset) override;
	bool AttachBall(std::shared_ptr<UnitBase> parent, std::shared_ptr<UnitBase> unit);

	float BallSpeed{ -300.0f };
	float InputSpeed{ 400.0f };
	bool Grab{ false };
};
//********************************************************************************
//********************************************************************************

class UnitTriger : public UnitBase
{
public:
	UnitTriger(float width, float heigth, Vector2d position, std::function<void(UnitBase*, UnitBase*)> action = nullptr);
	~UnitTriger() = default;

	virtual void OnCollision(UnitBase* unit, Vector2d& offset) override;

	std::function<void(UnitBase* self, UnitBase* unit)> Action{ nullptr };
};
//********************************************************************************
//********************************************************************************

class UnitPickup : public UnitBase
{
public:
	UnitPickup(Vector2d& position);
	~UnitPickup() = default;

	static float Size;
	float BonusWidth{ 0.0f };
	float BonusSpeed{ 0.0f };
	bool BonusBall{ false };
	int32_t BonusLive{ 0 };
private:
	enum class TypeBounus
	{
		Width = 0,
		Speed,
		Ball,
		Live,
		Count
	};
};
//********************************************************************************
//********************************************************************************