#pragma once

#include "Task.h"
#include <memory>
#include <list>

class TaskManager
{
public:
	TaskManager() = default;
	~TaskManager() = default;

	static TaskManager* GetInstance();
	void Send(std::unique_ptr<Task> task);
	void Clean();

	std::list<std::unique_ptr<Task>> TaskList;

protected:
	static TaskManager* Instance;
};

