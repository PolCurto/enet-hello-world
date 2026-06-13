#include <iostream>

#include "Globals.h"
#include "NetworkSystem.h"

int main() 
{
    GameState gameState = GameState::Init;   

    NetworkSystem* networkSystem = new NetworkSystem();

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
                gameState = GameState::Update;
                break;
            }

            case GameState::Update:
            {
                gameState = networkSystem->Update();
                if (gameState != GameState::Update)
                {
                    break;
                }
                break;
            }

            case GameState::Exit:
            {
                std::cout << "[SERVIDOR] Exit.\n";
                networkSystem->Exit();
                break;
            }
        }
    }

    return 0;
}