#include "Units.h"
#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include "TaskManager.h"

UnitBase::UnitBase(UnitType type, float width, float heigth, Vector2d position) :
	Type(type), Width(width * 0.5f), Heigth(heigth * 0.5f), Position(position)
{
	static uint32_t counter{ 0 };
	Id = counter;
	++counter;
}
//********************************************************************************

void UnitBase::Process(float dt)
{
	if (Parent == nullptr)
	{
		Speed += Acceleration * dt;
		Position += Speed * dt;
	}
	else
	{
		Position = RelativePosition + Parent->Position;
	}
}
//********************************************************************************

void UnitBase::Draw(uint32_t* buf, int32_t width, int32_t heigth)
{
	int32_t w = (int32_t)Width;
	int32_t h = (int32_t)Heigth;
	int32_t px = (int32_t)Position.X;
	int32_t py = (int32_t)Position.Y;

	int32_t begin_x = px - w;
	int32_t begin_y = py - h;
	int32_t max_x = px + w;
	int32_t max_y = py + h;

	if (begin_x < 0)
		begin_x = 0;
	else if (begin_x > width)
		begin_x = width;

	if (begin_y < 0)
		begin_y = 0;
	else if (begin_y > heigth)
		begin_y = heigth;

	if (max_x < 0)
		max_x = 0;
	else if (max_x > width)
		max_x = width;

	if (max_y < 0)
		max_y = 0;
	else if (max_y > heigth)
		max_y = heigth;

	uint32_t color = Color.GetColor();

	for (uint32_t y = begin_y; y < max_y; ++y)
	{
		for (uint32_t x = begin_x; x < max_x; ++x)
		{
			buf[(y * width) + x] = color;
		}
	}
}
//********************************************************************************

void UnitBase::TestCollision(UnitBase* unit)
{
	Vector2d& u_pos = unit->Position;
	float& uw = unit->Width;
	float& uh = unit->Heigth;

	Vector2d offset((Width + uw) - std::abs(u_pos.X - Position.X), (Heigth + uh) - std::abs(u_pos.Y - Position.Y));
	if ((offset.X > 0.0f) && (offset.Y > 0.0f))
	{
		Vector2d direction = unit->Position - Position;
		direction.Normalize();
		direction *= offset;

		if (Static == false)
		{
			if (offset.X > offset.Y)
			{
				Position.Y += -direction.Y;
			}
			else
			{
				Position.X += -direction.X;
			}
		}

		if (unit->Static == false)
		{
			if (offset.X > offset.Y)
			{
				unit->Position.Y += direction.Y;
			}
			else
			{
				unit->Position.X += direction.X;
			}
		}

		if (Parent != nullptr)
		{
			Parent->OnCollision(unit, offset);
		}
		else
		{
			OnCollision(unit, offset);
		}

		if (unit->Parent != nullptr)
		{
			unit->Parent->OnCollision(this, offset);
		}
		else
		{
			unit->OnCollision(this, offset);
		}
	}
}
//********************************************************************************

void UnitBase::OnCollision(UnitBase* unit, Vector2d& offset)
{
}
//********************************************************************************

void UnitBase::Attach(std::shared_ptr<UnitBase> parent, std::shared_ptr<UnitBase> unit)
{
	unit->Parent = parent;
	ChildList.push_back(unit);

	unit->RelativePosition = unit->Position;
	unit->Position = unit->RelativePosition + Position;
}
//********************************************************************************

void UnitBase::Detach(std::shared_ptr<UnitBase> unit)
{
	//Parent = unit;
}
//********************************************************************************
//********************************************************************************

int32_t UnitBall::Count{ 0 };
//********************************************************************************

UnitBall::UnitBall(Vector2d position, float width, float heigth, Color4c color) :
	UnitBase(UnitType::Ball, width, heigth, position)
{
	Color = color;
	Static = false;
	++Count;
}
//********************************************************************************

UnitBall::~UnitBall()
{
	--Count;
	if (Count < 1)
	{
		auto task = std::make_unique<TaskChangeLive>();
		task->Change = -1;
		TaskManager::GetInstance()->Send(std::move(task));
	}
}
//********************************************************************************

void UnitBall::Draw(uint32_t* buf, int32_t width, int32_t heigth)
{
	int32_t w = (int32_t)Width;
	int32_t h = (int32_t)Heigth;
	int32_t px = (int32_t)Position.X;
	int32_t py = (int32_t)Position.Y;

	int32_t begin_x = px - w;
	int32_t begin_y = py - h;
	int32_t max_x = px + w;
	int32_t max_y = py + h;

	if (begin_x < 0)
		begin_x = 0;
	else if (begin_x > width)
		begin_x = width;

	if (begin_y < 0)
		begin_y = 0;
	else if (begin_y > heigth)
		begin_y = heigth;

	if (max_x < 0)
		max_x = 0;
	else if (max_x > width)
		max_x = width;

	if (max_y < 0)
		max_y = 0;
	else if (max_y > heigth)
		max_y = heigth;

	uint32_t color = Color.GetColor();
	uint32_t black = Color4c(0, 0, 0).GetColor();;

	for (int32_t y = begin_y; y < max_y; ++y)
	{
		int32_t yc = (max_y - y) - w;
		for (int32_t x = begin_x; x < max_x; ++x)
		{
			int32_t xc = (max_x - x) - w;

			uint32_t c = (xc * xc) + (yc * yc) <= w * w ? color : black;
			buf[(y * width) + x] = c;
		}
	}
}
//********************************************************************************

void UnitBall::TestCollision(UnitBase* unit)
{
	if (unit->Type != UnitType::Pickup)
	{
		UnitBase::TestCollision(unit);
	}
}
//********************************************************************************

void UnitBall::OnCollision(UnitBase* unit, Vector2d& offset)
{
	if (offset.X > offset.Y)
	{
		Speed.Y = -Speed.Y;
	}
	else
	{
		Speed.X = -Speed.X;
	}
}
//********************************************************************************
//********************************************************************************

int32_t UnitBrick::MaxLive{ 3 };
uint32_t UnitBrick::BaseColor{ 70 };
int32_t UnitBrick::Count{ 0 };
//********************************************************************************

UnitBrick::UnitBrick(float width, float heigth, Vector2d position) :
	UnitBase(UnitType::Brick, width, heigth, position)
{
	++Count;
	Live = (std::rand() % MaxLive) + 1;
	Pickup = (std::rand() % 100) < 10 ? true : false;

	UpdateColor();
}
//********************************************************************************

UnitBrick::~UnitBrick()
{
	--Count;
	if (Count < 1)
	{
		auto task = std::make_unique<TaskNewGame>();
		task->Win = true;
		TaskManager::GetInstance()->Send(std::move(task));
	}
}
//********************************************************************************

void UnitBrick::OnCollision(UnitBase* unit, Vector2d& offset)
{
	if (unit->Type == UnitType::Ball)
	{
		--Live;
		if (Live > 0)
		{
			UpdateColor();
			return;
		}

		{
			auto task = std::make_unique<TaskDeleteUnit>();
			task->Id = Id;
			TaskManager::GetInstance()->Send(std::move(task));
		}

		if (Pickup == true)
		{
			auto pickup = std::make_shared<UnitPickup>(Position);
			auto task = std::make_unique<TaskRegisterUnit>();
			task->Unit = std::move(pickup);
			TaskManager::GetInstance()->Send(std::move(task));
		}
	}
}
//********************************************************************************

void UnitBrick::UpdateColor()
{
	uint32_t r{ BaseColor };
	uint32_t g{ BaseColor };
	uint32_t step = (255 - BaseColor) / (MaxLive);
	uint32_t value = BaseColor + (step * (Live));

	if (Pickup)
	{
		g = value;
	}
	else
	{
		r = value;
	}

	Color.SetColor(r, g, BaseColor);
}
//********************************************************************************
//********************************************************************************

UnitActor::UnitActor(float width, float heigth, Vector2d position, Color4c& color) :
	UnitBase(UnitType::Actor, width, heigth, position), InputBase()
{
	Color = color;
	Static = false;
}
//********************************************************************************

void UnitActor::Input(Keys& keys)
{
	if (keys[InputKey::LEFT].State)
	{
		Speed.X = -InputSpeed;
	}
	else if (keys[InputKey::RIGHT].State)
	{
		Speed.X = InputSpeed;
	}
	else
	{
		Speed.X = 0.0f;
	}

	if (keys[InputKey::SPACE].OnPush)
	{
		if (ChildList.empty() == false)
		{
			auto unit = ChildList.back();
			ChildList.pop_back();

			float left = (float)keys[InputKey::LEFT].State;
			float rigth = (float)keys[InputKey::RIGHT].State;

			unit->Speed.X = (left * BallSpeed) + (rigth * -BallSpeed);
			unit->Speed.Y = BallSpeed;
			unit->Parent.reset();
		}
		else
		{
			Grab = true;
		}
	}
}
//********************************************************************************

bool UnitActor::AttachBall(std::shared_ptr<UnitBase> parent, std::shared_ptr<UnitBase> unit)
{
	float margin = 1.0f;
	float childs_width = 0.0f;
	for (auto child : ChildList)
	{
		childs_width += child->Width + margin;
	}

	float new_width = childs_width + unit->Width + margin;
	if ((Width - new_width) > 0.0f)
	{
		UnitBase::Attach(parent, unit);

		float offset_x = -new_width;
		for (auto child : ChildList)
		{
			offset_x += child->Width + margin;
			child->RelativePosition.X = offset_x;
			child->RelativePosition.Y = -(Heigth + unit->Heigth);

			child->Position = Position + child->RelativePosition;

			offset_x += child->Width + margin;
		}

		return true;
	}

	return false;
}
//********************************************************************************

void UnitActor::OnCollision(UnitBase* unit, Vector2d& offset)
{
	if (unit->Type == UnitType::Pickup)
	{
		auto unit_p = static_cast<UnitPickup*>(unit);

		{
			auto task = std::make_unique<TaskDeleteUnit>();
			task->Id = unit->Id;
			TaskManager::GetInstance()->Send(std::move(task));
		}

		if (unit_p->BonusLive != 0)
		{
			auto task = std::make_unique<TaskChangeLive>();
			task->Change = unit_p->BonusLive;
			TaskManager::GetInstance()->Send(std::move(task));
		}

		if (unit_p->BonusBall == true)
		{
			auto ball = std::make_shared<UnitBall>(Vector2d(0.0f, 0.0f));

			auto task_register = std::make_unique<TaskRegisterUnit>();
			task_register->Unit = ball;
			TaskManager::GetInstance()->Send(std::move(task_register));

			auto task_attach = std::make_unique<TaskAttachBall>();
			task_attach->ParentId = Id;
			task_attach->UnitId = ball->Id;
			TaskManager::GetInstance()->Send(std::move(task_attach));
		}

		InputSpeed += unit_p->BonusSpeed;
		Width += unit_p->BonusWidth;
	}
	else if (unit->Type == UnitType::Ball)
	{
		if (Grab)
		{
			Grab = false;

			auto task = std::make_unique<TaskAttachBall>();
			task->UnitId = unit->Id;
			task->ParentId = Id;
			TaskManager::GetInstance()->Send(std::move(task));
		}
	}
}
//********************************************************************************
//********************************************************************************

UnitTriger::UnitTriger(float width, float heigth, Vector2d position, std::function<void(UnitBase*, UnitBase*)> action) :
	UnitBase(UnitType::Triger, width, heigth, position), Action(action)
{
	//Visible = false;
}
//********************************************************************************

void UnitTriger::OnCollision(UnitBase* unit, Vector2d& offset)
{
	if (Action != nullptr)
	{
		Action(this, unit);
	}
}
//********************************************************************************
//********************************************************************************

float UnitPickup::Size{ 20 };
//********************************************************************************

UnitPickup::UnitPickup(Vector2d& position) :
	UnitBase(UnitType::Pickup, Size, Size, position)
{
	Static = false;
	Speed = { 0.0f, 200.0f };

	TypeBounus type = (TypeBounus)(std::rand() % (uint32_t)TypeBounus::Count);
	switch (type)
	{
		case TypeBounus::Ball:
		{
			BonusBall = true;
			Color = {0, 255, 200};
			break;
		}
		case TypeBounus::Live:
		{
			BonusLive = 1;
			Color = { 255, 50, 50 };
			break;
		}
		case TypeBounus::Speed:
		{
			BonusSpeed = 50.0f;
			Color = { 50, 255, 50 };
			break;
		}
		case TypeBounus::Width:
		{
			BonusWidth = 15.0f;
			Color = { 200, 200, 255 };
			break;
		}
	}
}
//********************************************************************************