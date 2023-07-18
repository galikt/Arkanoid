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
	{
		float w = 100.0f;
		float h = 15.0f;
		Vector2d position(SCREEN_WIDTH / 2.0f, (SCREEN_HEIGHT - h) - 10.0f);
		Vector2d speed(0.0f, 0.0f);
		Color4c color(200, 200, 255);
		ActorList.push_back(std::make_unique<Actor>(w, h, position, speed, color));
	}

	{
		float w = 20;
		float h = 20;
		Vector2d position(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
		Vector2d speed(0.0f, 0.0f);
		Color4c color(0, 255, 200);
		for (uint32_t i = 0; i < balls; ++i)
		{
			auto ball = std::make_unique<Ball>(w, h, position, speed, color);
			ball->Acceleration = {200.0f, -200.0f};
			UnitList.push_back(std::move(ball));
		}
	}
	{
		Vector2d speed(0.0f, 0.0f);
		Color4c color(255, 50, 50);

		float margin = 4.0f;
		float w = 60;
		float h = 20;

		float max_w = (w + margin * 2);
		float max_h = (h + margin * 2);

		int count_x = (SCREEN_WIDTH) / max_w;
		int count_y = (SCREEN_HEIGHT) / max_h;

		for (uint32_t i = 0; i < brick; ++i)
		{
			float x = i % count_x;
			float y = i / count_x;

			Vector2d position(x * max_w, y * max_h);
			UnitList.push_back(std::make_unique<Brick>(w, h, position, speed, color));
		}
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
	for (auto& unit : ActorList)
	{
		unit->Process(dt);

		for (auto& unit2 : UnitList)
		{
			unit->TestCollision(unit2.get());
		}

		if ((unit->Position.X <= 0.0f) && (unit->Position.X >= SCREEN_WIDTH))
		{
			/*unit->Acceleration.X = -unit->Acceleration.X;*/
			//unit->Position.X =
		}
		if ((unit->Position.Y <= 0.0f) && (unit->Position.Y >= SCREEN_HEIGHT))
		{
			//unit->Acceleration.Y = -unit->Acceleration.Y;
		}
	}

	for (auto iter = UnitList.begin(); iter != UnitList.end(); ++iter)
	{
		(*iter)->Process(dt);

		if (((*iter)->Position.X <= 0.0f) || (((*iter)->Position.X + (*iter)->Width) > SCREEN_WIDTH))
		{
			(*iter)->Acceleration.X = -(*iter)->Acceleration.X;
		}

		if (((*iter)->Position.Y < 0.0f) || (((*iter)->Position.Y + (*iter)->Heigth) > SCREEN_HEIGHT))
		{
			(*iter)->Acceleration.Y = -(*iter)->Acceleration.Y;
		}

		for (auto iter2 = iter; iter2 != UnitList.end(); ++iter2)
		{
			if (iter == iter2)
				continue;

			(*iter)->TestCollision((*iter2).get());
		}
	}
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
