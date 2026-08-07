#include "World.h"

#include "Registry.h"
#include "GameState.h"
#include "Systems/InputSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/CollisionSystem.h"
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
    collisionSystem = std::make_unique<CollisionSystem>();
}

World::~World()
{
    registry.reset();
    inputSystem.reset();
    movementSystem.reset();
    collisionSystem.reset();
}

void World::Init()
{
    const int entityId = registry->AddEntity();

    registry->AddComponent(entityId, TransformComponent { 0.0f, 0.0f, 15.0f, 15.0f });
    registry->AddComponent(entityId, MovementComponent { 400.0f, 200.0f });
    registry->AddComponent(entityId, CollisionComponent { 15.0f, 15.0f, CollisionType::Bounce });
}

GameState World::Update(const float deltaTime)
{
    registry->GetComponentsUnion(tempInputComponents, tempMovementComponents);
    inputSystem->UpdateComponents(tempInputComponents, tempMovementComponents);

    registry->GetComponentsUnion(tempMovementComponents, tempTransformComponents);
    movementSystem->UpdateComponents(tempMovementComponents, tempTransformComponents, deltaTime);

    registry->GetComponentsUnion(tempTransformComponents, tempMovementComponents, tempCollisionComponents);
    collisionSystem->UpdateComponents(tempTransformComponents, tempMovementComponents, tempCollisionComponents);

    return GameState::Update;
}

int World::OnPlayerConnected()
{
    const int entityId = registry->AddEntity();

    registry->AddComponent(entityId, InputComponent { false, false });

    if (!playerConnected)
    {
        registry->AddComponent(entityId, TransformComponent { 0.0f, 100.0f, 20.0f, 100.0f });       
        playerConnected = true;
    }
    else
    {
        registry->AddComponent(entityId, TransformComponent { 300.0f, 100.0f, 20.0f, 100.0f });
    }
    registry->AddComponent(entityId, MovementComponent { 0.0f, 0.0f });
    registry->AddComponent(entityId, CollisionComponent { 15.0f, 15.0f, CollisionType::Static });

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
        const float w = transformData.components[i].w;
        const float h = transformData.components[i].h;
        currentWorldState.entities[i] = { entityId, x, y, w, h };
    }
    return currentWorldState;
}