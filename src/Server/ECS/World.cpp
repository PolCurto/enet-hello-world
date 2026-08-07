#include "World.h"

#include "Registry.h"
#include "GameState.h"
#include "Systems/InputSystem.h"
#include "Systems/MovementSystem.h"
#include "Components/InputComponent.h"
#include "Components/MovementComponent.h"
#include "Components/TransformComponent.h"
#include "WorldStatePacket.h"

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

GameState World::Update(const float deltaTime)
{
    tempInputComponents.clear();
    tempMovementComponents.clear();
    registry->GetComponentsUnion(tempInputComponents, tempMovementComponents);
    inputSystem->UpdateComponents(tempInputComponents, tempMovementComponents);

    tempMovementComponents.clear();
    tempTransformComponents.clear();
    registry->GetComponentsUnion(tempMovementComponents, tempTransformComponents);
    movementSystem->UpdateComponents(tempMovementComponents, tempTransformComponents, deltaTime);

    return GameState::Update;
}

int World::OnPlayerConnected()
{
    const int entityId = registry->AddEntity();

    registry->AddComponent(entityId, InputComponent{ false, false });
    registry->AddComponent(entityId, TransformComponent { 0.0f, 0.0f, 20.0f, 100.0f });
    registry->AddComponent(entityId, MovementComponent{ 0.0f, 0.0f });

    return entityId;
}

void World::OnPlayerInput(int entityId, bool up, bool down)
{
    //std::cout << "ON PLAYER " << entityId << " INPUT: " << up << ", " << down << "\n";

    InputComponent& input = registry->GetComponent<InputComponent>(entityId);
    input.up = up;
    input.down = down;
}

const WorldStatePacket& World::GetWorldState()
{
    const ComponentData<TransformComponent>& transformData = registry->GetComponentData<TransformComponent>();
    currentWorldState.count = transformData.dense.size();

    for (int i = 0; i < transformData.dense.size(); ++i)
    {
        const int entityId = transformData.dense[i];
        const float x = transformData.components[i].x;
        const float y = transformData.components[i].y;
        currentWorldState.entities[i] = { entityId, x, y };
    }
    return currentWorldState;
}