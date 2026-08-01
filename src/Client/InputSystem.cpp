#include "InputSystem.h"

#include <iostream>
#include <SDL3/SDL.h>

#include "GameState.h"
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

	UpdateKeyState(upKey, keyboardState[SDL_SCANCODE_UP]);
	UpdateKeyState(downKey, keyboardState[SDL_SCANCODE_DOWN]);
}

void InputSystem::UpdateKeyState(KeyState& currentKey, const bool isPressed)
{
    if (isPressed)
    {
        currentKey = (currentKey == KeyState::Idle || currentKey == KeyState::Released) 
                     ? KeyState::Down 
                     : KeyState::Repeat;
    }
    else
    {
        currentKey = (currentKey == KeyState::Down || currentKey == KeyState::Repeat) 
                     ? KeyState::Released 
                     : KeyState::Idle;
    }
}

bool InputSystem::HasInputEventHappened() const
{
	return upKey == KeyState::Down || upKey == KeyState::Released ||
			downKey == KeyState::Down || downKey == KeyState::Released;
}
