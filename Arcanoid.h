#pragma once

#include <stdint.h>
#include <list>
#include <map>

#include <memory>
#include "Units.h"
#include "Input.h"
#include "TaskManager.h"

class Arcanoid : public InputBase
{
public:
	Arcanoid();
	~Arcanoid();

	void Initialize(int32_t balls = 4, int32_t brick = 45, float width = 200);
	virtual void Input(Keys& kyes);
	void Process(float dt);
	void ProcessTask(std::unique_ptr<Task> task);
	void Draw(uint32_t* buf, int32_t w, int32_t h);
	void Clean();
	void DeleteUnit(uint32_t id);
	void RegisterUnit(std::shared_ptr<UnitBase>&& unit);
	void NewGame(bool win);

protected:
	std::map<uint32_t, std::shared_ptr<UnitBase>> Units;
	std::shared_ptr<UnitActor> CurrentActor{ nullptr };

	struct
	{
		int32_t Live{ 0 };
		int32_t Brick{ 0 };
		int32_t Ball{ 0 };
		int32_t Width{ 0 };
	} Level;

	int32_t StepBrick{ 15 };
};
//********************************************************************************
//********************************************************************************
