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
	if (!SDL_Init(SDL_INIT_EVENTS))
	{
		std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
		return false;
	}
	std::cout << "Input system inicializado" << std::endl;
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

	down = keyboardState[SDL_SCANCODE_DOWN];
	up = keyboardState[SDL_SCANCODE_UP];

	if (down)
	{
		std::cout << "[CLIENTE] Tecla Abajo presionada.\n";
	}
	if (up)
	{
		std::cout << "[CLIENTE] Tecla Arriba presionada.\n";
	}
}