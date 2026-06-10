#include "InputSystem.h"

#include "raylib.h"
#include <iostream>

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::Update()
{
	PollKeyboard();
}

void InputSystem::PollKeyboard()
{
	if (IsKeyDown(KEY_DOWN))
	{
		std::cout << "Abajo" << std::endl;
	}

	if (IsKeyDown(KEY_UP))
	{
		std::cout << "Arriba" << std::endl;
	}
}