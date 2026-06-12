#pragma once

enum class GameState;
struct EngineContext;

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
	bool up;
	bool down;
};