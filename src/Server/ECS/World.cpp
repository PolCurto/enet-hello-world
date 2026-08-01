#include "World.h"

#include "Registry.h"
#include "GameState.h"

#include <iostream>

World::World()
{
}

World::~World()
{
}

void World::Init()
{
    registry = std::make_unique<Registry>();
}

GameState World::Update()
{
    return GameState::Update;
}

int World::OnPlayerConnected()
{
    const int entityId = registry->AddEntity();

    registry->AddComponent(entityId, InputComponent{ false, false });
    registry->AddComponent(entityId, PositionComponent{ 0.0f, 0.0f });
    registry->AddComponent(entityId, MovementComponent{ 0.0f, 0.0f });

    return entityId;
}

void World::OnPlayerInput(int entityId, bool up, bool down)
{
    std::cout << "ON PLAYER " << entityId << " INPUT: " << up << ", " << down << "\n";
    
}
