#pragma once

#include <map>

enum class InputKey
{
	ESCAPE,
	SPACE,
	LEFT,
	UP,
	RIGHT,
	DOWN,
	RETURN
};

struct KeyState
{
	KeyState(char os_key) { OsKey = os_key; };
	KeyState() {};

	bool State{ false };
	bool OldState{ false };
	bool OnPush{ false };
	char OsKey{ 0 };
};

using Keys = std::map<InputKey, KeyState>;

class InputBase
{
public:
	InputBase() = default;
	~InputBase() = default;

	virtual void Input(Keys& keys) = 0;
};