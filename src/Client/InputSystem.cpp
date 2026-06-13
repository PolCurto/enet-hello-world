#include "InputSystem.h"

#include <iostream>
#include <SDL3/SDL.h>

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
	SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            return GameState::Exit;
        }
    }

	PollKeyboard();

	return GameState::Update;
}

void InputSystem::PollKeyboard()
{
	const bool* keyboardState = SDL_GetKeyboardState(nullptr);

	if (keyboardState[SDL_SCANCODE_DOWN])
	{
		if (downKey == KeyState::Idle || downKey == KeyState::Released)
		{
			downKey = KeyState::Down;
		}
		else
		{
			downKey = KeyState::Repeat;
		}
	}
	else
	{
		if (downKey == KeyState::Down || downKey == KeyState::Repeat)
		{
			downKey = KeyState::Released;
		}
		else
		{
			downKey = KeyState::Idle;
		}
	}

	if (keyboardState[SDL_SCANCODE_UP])
	{
		if (upKey == KeyState::Idle || upKey == KeyState::Released)
		{
			upKey = KeyState::Down;
		}
		else
		{
			upKey = KeyState::Repeat;
		}
	}
	else
	{
		if (upKey == KeyState::Down || upKey == KeyState::Repeat)
		{
			upKey = KeyState::Released;
		}
		else
		{
			upKey = KeyState::Idle;
		}
	}
}