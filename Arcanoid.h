#pragma once

#include <stdint.h>
#include <list>
#include <memory>
#include "Units.h"
#include "Input.h"

class Arcanoid
{
public:
	Arcanoid();
	~Arcanoid();

	void Initialize(uint32_t balls, uint32_t brick);
	void Input(std::list<InputKey>& keys);
	void Process(float dt);
	void Draw(uint32_t* buf, uint32_t w, uint32_t h);

protected:
	std::list<std::unique_ptr<Actor>> ActorList;
	std::list<std::unique_ptr<UnitBase>> UnitList;
};