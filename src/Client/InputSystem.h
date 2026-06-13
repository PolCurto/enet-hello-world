#pragma once

enum class GameState;
struct EngineContext;

enum class KeyState
{
	Idle,
	Down,
	Repeat,
	Released
};

class InputSystem
{
public:
	InputSystem();
	~InputSystem();
		
	bool Init();
	GameState Update(const EngineContext& engineContext);

private:
	void PollKeyboard();

public:
	KeyState upKey = KeyState::Idle;
	KeyState downKey = KeyState::Idle;
};