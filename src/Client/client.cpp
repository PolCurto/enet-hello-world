#include <iostream>
#include <cstring>

#include <SDL3/SDL.h>

#include "InputSystem.h"
#include "GameState.h"
#include "EngineContext.h"
#include "NetworkSystem.h"
#include "RenderSystem.h"

// TODO: MOVE WINDOW TO SYSTEM

int main()
{
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        std::cerr << "Error crítico al inicializar SDL global: " << SDL_GetError() << std::endl;
        return 1;
    }
	
    SDL_SetAppMetadata("Example Input Joystick Polling", "1.0", "com.example.input-joystick-polling");

	InputSystem* inputSystem = new InputSystem();
	NetworkSystem* networkSystem = new NetworkSystem();
	RenderSystem* renderSystem = new RenderSystem();

	const EngineContext context = { inputSystem, networkSystem, renderSystem };

	GameState gameState = GameState::Init;

	while (gameState != GameState::Exit)
	{

		switch (gameState)
		{
			case GameState::Init:
			{
				std::cout << "[CLIENT] Init.\n";

				if (!inputSystem->Init() || !networkSystem->Init() || !renderSystem->Init())
				{
					gameState = GameState::Exit;
					break;
				}
				gameState = GameState::Update;
				break;
			}

			case GameState::Update:
			{
				gameState = inputSystem->Update(context);
				if (gameState != GameState::Update)
				{
					break;
				}

				gameState = networkSystem->Update(context);
				if (gameState != GameState::Update)
				{
					break;
				}

				gameState = renderSystem->Update(context);
				if (gameState != GameState::Update)
				{
					break;
				}

				break;
			}

			case GameState::Exit:
			{
				networkSystem->Exit();
				break;
			}
		}
	}

	delete networkSystem;
	delete inputSystem;
	delete renderSystem;

    std::cout << "[CLIENT] Closing.\n";
    return 0;
}