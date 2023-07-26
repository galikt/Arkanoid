#pragma once

#include <stdint.h>
#include <memory>
#include "Math.h"
#include "Units.h"

class UnitBase;

enum class TaskType
{
	None,
	NewGame,
	RegisterUnit,
	DeleteUnit,
	AttachBall,
	ChangeLive
};

class Task
{
public:
	Task(TaskType type);
	virtual ~Task() = default;

	TaskType Type{ TaskType::None };
};
//********************************************************************************
//********************************************************************************

class TaskDeleteUnit : public Task
{
public:
	TaskDeleteUnit();
	virtual ~TaskDeleteUnit() = default;

	uint32_t Id{ 0 };
};
//********************************************************************************
//********************************************************************************

class TaskNewGame : public Task
{
public:
	TaskNewGame();
	virtual ~TaskNewGame() = default;
	bool Win{ false };
};
//********************************************************************************
//********************************************************************************

class TaskAttachBall : public Task
{
public:
	TaskAttachBall();
	virtual ~TaskAttachBall() = default;

	uint32_t ParentId{ 0 };
	uint32_t UnitId{ 0 };
	//std::shared_ptr<UnitBase> Unit{ nullptr};
};
//********************************************************************************
//********************************************************************************

class TaskRegisterUnit : public Task
{
public:
	TaskRegisterUnit();
	virtual ~TaskRegisterUnit() = default;

	std::shared_ptr<UnitBase> Unit{ nullptr};
};
//********************************************************************************
//********************************************************************************

class TaskChangeLive : public Task
{
public:
	TaskChangeLive();
	virtual ~TaskChangeLive() = default;

	int32_t Change{ 0 };
};
//********************************************************************************
//********************************************************************************
