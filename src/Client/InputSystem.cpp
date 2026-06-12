#include "InputSystem.h"

#include "raylib.h"
#include <iostream>

#include "Globals.h"
#include "EngineContext.h"

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

bool InputSystem::Init()
{
	return true;
}

GameState InputSystem::Update(const EngineContext& context)
{
	PollKeyboard();

	return GameState::Update;
}

void InputSystem::PollKeyboard()
{
	down = IsKeyPressed(KEY_DOWN);
	up = IsKeyPressed(KEY_UP);

	if (down)
	{
		std::cout << "[CLIENTE] Tecla Abajo presionada.\n";
	}
	if (up)
	{
		std::cout << "[CLIENTE] Tecla Arriba presionada.\n";
	}

	if (IsKeyPressed(KEY_W))
	{
		std::cout << "[CLIENTE] Tecla W presionada.\n";
	}
}