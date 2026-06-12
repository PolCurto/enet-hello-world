#include <iostream>
#include <cstring>

#include "InputSystem.h"
#include "Globals.h"
#include "EngineContext.h"
#include "NetworkSystem.h"

// TODO: MOVE WINDOW TO SYSTEM

int main()
{
	NetworkSystem* networkSystem = new NetworkSystem();
	InputSystem* inputSystem = new InputSystem();

	const EngineContext context = { inputSystem };

	GameState gameState = GameState::Init;

	while (gameState != GameState::Exit)
	{

		switch (gameState)
		{
			case GameState::Init:
			{
				std::cout << "[CLIENT] Init.\n";

				inputSystem->Init();
				networkSystem->Init();
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