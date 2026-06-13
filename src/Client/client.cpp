#include <iostream>
#include <cstring>

#include "InputSystem.h"
#include "Globals.h"
#include "EngineContext.h"
#include "NetworkSystem.h"
#include "RenderSystem.h"
#include <SDL3/SDL.h>

// TODO: MOVE WINDOW TO SYSTEM

int main()
{
    SDL_SetAppMetadata("Example Input Joystick Polling", "1.0", "com.example.input-joystick-polling");

	InputSystem* inputSystem = new InputSystem();
	NetworkSystem* networkSystem = new NetworkSystem();
	RenderSystem* renderSystem = new RenderSystem();

	const EngineContext context = { inputSystem };

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

    std::cout << "[CLIENTE] Cerrando.\n";
    return 0;
}