#include "TaskManager.h"

TaskManager* TaskManager::Instance { nullptr };

TaskManager* TaskManager::GetInstance()
{
	if (Instance == nullptr)
		Instance = new(TaskManager);

	return Instance;
}

void TaskManager::Send(std::unique_ptr<Task> task)
{
	TaskList.push_back(std::move(task));
}

void TaskManager::Clean()
{
	TaskList.clear();
}
