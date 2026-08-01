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

    void AddPlayer();

private:
    std::unique_ptr<Registry> registry;
};