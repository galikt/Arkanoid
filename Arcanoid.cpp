#include "Arcanoid.h"
#include "Units.h"
#include "Engine.h"

Arcanoid::Arcanoid()
{
}

Arcanoid::~Arcanoid()
{
}

void Arcanoid::Initialize(uint32_t balls, uint32_t brick)
{
	float w = 100.0f;
	float h = 10.0f;
	Vector2d position(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - h);
	Vector2d speed(0.0f, 0.0f);
	ActorList.push_back(std::make_unique<Actor>(w, h, position, speed));

	for (uint32_t i = 0; i <= balls; ++i)
	{
		float w = 30;
		float h = 30;
		Vector2d position(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
		Vector2d speed(0.0f, 10.0f);
		UnitList.push_back(std::make_unique<Ball>(w, h, position, speed));
	}

	for (uint32_t i = 0; i <= brick; ++i)
	{
		float w = 60;
		float h = 20;
		Vector2d position(100.f, 100.0f);
		Vector2d speed(0.0f, 10.0f);
		UnitList.push_back(std::make_unique<Brick>(w, h, position, speed));
	}
}

void Arcanoid::Input(std::list<InputKey>& keys)
{
	std::list<InputKey> key_list = std::move(keys);

	for (auto& key : key_list)
	{
		for (auto& actor : ActorList)
		{
			actor->Input(key);
		}
	}
}

void Arcanoid::Process(float dt)
{

}

void Arcanoid::Draw(uint32_t* buf, uint32_t w, uint32_t h)
{
	for (auto& unit : ActorList)
	{
		unit->Draw(buf, w, h);
	}

	for (auto& unit : UnitList)
	{
		unit->Draw(buf, w, h);
	}
}
