#pragma once

class InputSystem
{
public:
	InputSystem();
	~InputSystem();
		
	void Update();

private:
	void PollKeyboard();
};