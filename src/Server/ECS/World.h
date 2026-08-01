#pragma once

#include <memory>

class Registry;
enum class GameState;

class World
{
public:
    World();
    ~World();

    void Init();
    GameState Update();

    int OnPlayerConnected();
    void OnPlayerInput(int entityId, bool up, bool down);

private:
    std::unique_ptr<Registry> registry;
};