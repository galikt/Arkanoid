#pragma once

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

class InputBase
{
public:
	InputBase() = default;
	~InputBase() = default;

	virtual void Input(InputKey& key);
};