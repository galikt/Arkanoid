#include "Arcanoid.h"
#include "cstdlib"
#include "time.h"
#include "Units.h"
#include "Engine.h"

Arcanoid::Arcanoid()
{
	std::srand(time(NULL));
}
//********************************************************************************

Arcanoid::~Arcanoid()
{
}
//********************************************************************************

void Arcanoid::Initialize(int32_t balls, int32_t brick, float width)
{
	Level.Brick = brick;
	Level.Ball = balls;
	Level.Width = width;

	//Боковые тригеры
	{
		float value = 100.0f;

		auto action = [](UnitBase* self, UnitBase* unit)
		{
			if ((unit->Type == UnitType::Ball) || ((unit->Type == UnitType::Pickup)))
			{
				auto task = std::make_unique<TaskDeleteUnit>();
				task->Id = unit->Id;
				TaskManager::GetInstance()->Send(std::move(task));
			}
		};
		auto down = std::make_shared<UnitTriger>(SCREEN_WIDTH, value, Vector2d(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT + (value * 0.5f)), action);
		RegisterUnit(std::move(down));

		auto top = std::make_shared<UnitTriger>(SCREEN_WIDTH, value, Vector2d(SCREEN_WIDTH * 0.5f, -(value * 0.5f)));
		RegisterUnit(std::move(top));

		auto left = std::make_shared<UnitTriger>(value, SCREEN_HEIGHT, Vector2d(-(value * 0.5f), SCREEN_HEIGHT * 0.5f));
		RegisterUnit(std::move(left));

		auto rigth = std::make_shared<UnitTriger>(value, SCREEN_HEIGHT, Vector2d(SCREEN_WIDTH + (value * 0.5f), SCREEN_HEIGHT * 0.5f));
		RegisterUnit(std::move(rigth));
	}

	//Кирпичи
	{
		float margin = 2.0f;
		uint32_t amount = 15;
		float aspect_ratio = 0.4f;

		float rect_x = (float)SCREEN_WIDTH / (float)amount;
		float rect_y = rect_x * aspect_ratio;

		float width = rect_x - (margin * 2.0f);
		float heigth = rect_y - (margin * 2.0f);

		float half_width = rect_x * 0.5f;
		float half_heigth = rect_y * 0.5f;

		for (uint32_t i = 0; i < Level.Brick; ++i)
		{
			//if ((std::rand() % 100) <= 10)
			//{
			//	continue;
			//}

			float x = i % amount;
			float y = i / amount;

			auto brick = std::make_shared<UnitBrick>(width, heigth, Vector2d(half_width + (x * rect_x), half_heigth + (y * rect_y)));
			RegisterUnit(brick);
		}
	}

	//Каретка
	{
		float w = Level.Width;
		float h = 15.0f;
		Vector2d position(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - h);
		Color4c color(200, 200, 255);

		auto actor = std::make_shared<UnitActor>(w, h, position, color);
		CurrentActor = actor;
		RegisterUnit(actor);
	}

	//шар
	{
		for (uint32_t i = 0; i < Level.Ball; ++i)
		{
			auto ball = std::make_shared<UnitBall>(Vector2d(0.0f, 0.0f));
			if (CurrentActor->AttachBall(CurrentActor, ball) == false)
				break;

			RegisterUnit(ball);
		}
	}
}
//********************************************************************************

void Arcanoid::Input(Keys& keys)
{
	for (auto& key : keys)
	{
		if (key.second.State)
		{
			if (key.second.State != key.second.OldState)
			{
				key.second.OnPush = true;
			}
			else
			{
				key.second.OnPush = false;
			}
		}
	}

	if (keys[InputKey::ESCAPE].OnPush)
	{
		schedule_quit_game();
	}

	if (CurrentActor != nullptr)
	{
		CurrentActor->Input(keys);
	}
}
//********************************************************************************

void Arcanoid::Process(float dt)
{
	for (auto unit : Units)
	{
		if (unit.second->Static == false)
		{
			unit.second->Process(dt);
		}
	}

	for (auto iter = Units.begin(); iter != Units.end(); ++iter)
	{
		auto& unit = iter->second;
		for (auto iter2 = iter; iter2 != Units.end(); ++iter2)
		{
			auto& unit2 = iter2->second;
			if ((iter == iter2) ||
				((unit->Static == true) && (unit2->Static == true)) ||
				(unit == unit2->Parent) || (unit2 == unit->Parent) ||
				((unit->Parent != nullptr) && unit->Parent == unit2->Parent))
				continue;

			unit->TestCollision(unit2.get());
		}
	}

	std::list<std::unique_ptr<Task>> task_list = std::move(TaskManager::GetInstance()->TaskList);
	for (auto& task : task_list)
	{
		ProcessTask(std::move(task));
	}
}
//********************************************************************************

void Arcanoid::DeleteUnit(uint32_t id)
{
	Units.erase(id);
}
//********************************************************************************

void Arcanoid::RegisterUnit(std::shared_ptr<UnitBase>&& unit)
{
	Units.insert(std::make_pair(unit->Id, unit));
}
//********************************************************************************

void Arcanoid::ProcessTask(std::unique_ptr<Task> task)
{
	switch (task->Type)
	{
		case TaskType::DeleteUnit:
		{
			auto task_p = static_cast<TaskDeleteUnit*>(task.get());
			DeleteUnit(task_p->Id);
			break;
		}
		case TaskType::NewGame:
		{
			auto task_p = static_cast<TaskNewGame*>(task.get());
			NewGame(task_p->Win);
			break;
		}
		case TaskType::AttachBall:
		{
			auto task_p = static_cast<TaskAttachBall*>(task.get());

			std::shared_ptr<UnitBase> parent_p {nullptr};
			std::shared_ptr<UnitBase> unit_p {nullptr};
			for (const auto& unit : Units)
			{
				if (unit.second->Id == task_p->UnitId)
				{
					unit_p = unit.second;
				}
				else if (unit.second->Id == task_p->ParentId)
				{
					parent_p = unit.second;
				}

				if (unit_p && parent_p)
					break;
			}

			auto actor = static_cast<UnitActor*>(parent_p.get());
			if (actor->AttachBall(parent_p, unit_p) == false)
			{
				DeleteUnit(task_p->UnitId);
			}
			
			break;
		}
		case TaskType::RegisterUnit:
		{
			auto task_p = static_cast<TaskRegisterUnit*>(task.get());
			RegisterUnit(std::move(task_p->Unit));
			break;
		}
		case TaskType::ChangeLive:
		{
			auto task_p = static_cast<TaskChangeLive*>(task.get());
			Level.Live += task_p->Change;
			if (task_p->Change < 0.0f)
			{
				if (Level.Live < 0)
				{
					NewGame(false);
				}
				else
				{
					auto ball = std::make_shared<UnitBall>(Vector2d(0.0f, 0.0f));

					auto task_registre = std::make_unique<TaskRegisterUnit>();
					task_registre->Unit = ball;
					TaskManager::GetInstance()->Send(std::move(task_registre));

					auto task_attach = std::make_unique<TaskAttachBall>();
					task_attach->UnitId = ball->Id;
					task_attach->ParentId = CurrentActor->Id;
					TaskManager::GetInstance()->Send(std::move(task_attach));
				}
			}
			break;
		}
	}
}
//********************************************************************************

void Arcanoid::NewGame(bool win)
{
	Clean();
	TaskManager::GetInstance()->Clean();

	if (win)
	{
		Level.Brick += StepBrick;
		Level.Ball = Level.Ball > 1 ? Level.Ball - 1 : 1;
		Level.Width = Level.Width > 15.0f ? Level.Width - 15.0f : 15.0f;
	}
	else
	{
		Level.Live = 0;
	}
	Initialize(Level.Ball, Level.Brick, Level.Width);
}
//********************************************************************************

void Arcanoid::Draw(uint32_t* buf, int32_t w, int32_t h)
{
	for (auto& unit : Units)
	{
		if (unit.second->Visible == false)
			continue;

		unit.second->Draw(buf, w, h);
	}
}
//********************************************************************************

void Arcanoid::Clean()
{
	Units.clear();
}
//********************************************************************************
//********************************************************************************