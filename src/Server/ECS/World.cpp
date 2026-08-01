#include "World.h"

#include "Registry.h"
#include "GameState.h"
#include "Systems/InputSystem.h"
#include "Systems/MovementSystem.h"
#include "Components/InputComponent.h"
#include "Components/MovementComponent.h"
#include "Components/PositionComponent.h"

#include <iostream>

World::World()
{
    registry = std::make_unique<Registry>();
    inputSystem = std::make_unique<InputSystem>();
    movementSystem = std::make_unique<MovementSystem>();
}

World::~World()
{
    registry.reset();
    inputSystem.reset();
    movementSystem.reset();
}

void World::Init()
{
}

GameState World::Update()
{
    tempInputComponents.clear();
    tempMovementComponents.clear();
    registry->GetComponentsUnion(tempInputComponents, tempMovementComponents);
    inputSystem->UpdateComponents(tempInputComponents, tempMovementComponents);

    tempMovementComponents.clear();
    tempPositionComponents.clear();
    registry->GetComponentsUnion(tempMovementComponents, tempPositionComponents);
    movementSystem->UpdateComponents(tempMovementComponents, tempPositionComponents);

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

    InputComponent& input = registry->GetComponent<InputComponent>(entityId);
    input.up = up;
    input.down = down;
}
