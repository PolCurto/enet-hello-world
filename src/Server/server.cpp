#include <iostream>
#include <chrono>

#include "GameState.h"
#include "NetworkSystem.h"
#include "ECS/World.h"
#include "EngineContext.h"
#include "Clock.h"

int main() 
{
    GameState gameState = GameState::Init;   
    Clock clock;

    NetworkSystem* networkSystem = new NetworkSystem();
    World* world = new World();

    const EngineContext engineContext = { networkSystem, world };

    while (gameState != GameState::Exit)
    {
        switch (gameState)
        {
            case GameState::Init:
            {
                std::cout << "[SERVIDOR] Init.\n";

                if (!networkSystem->Init())
                {
                    gameState = GameState::Exit;
                    break;
                }
                world->Init();

                gameState = GameState::Update;
                break;
            }

            case GameState::Update:
            {
                const float deltaTime = clock.Restart();

                gameState = networkSystem->Update(engineContext);
                if (gameState != GameState::Update)
                {
                    break;
                }
                
                gameState = world->Update(deltaTime);
                if (gameState != GameState::Update)
                {
                    break;
                }

                break;
            }

            case GameState::Exit:
            {
                std::cout << "[SERVER] Exit.\n";
                networkSystem->Exit();
                break;
            }
        }
    }

    delete networkSystem;
    delete world;

    std::cout << "[SERVER] Closing.\n";
    return 0;
}