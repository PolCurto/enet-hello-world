#include "World.h"

#include "Registry.h"
#include "GameState.h"
#include "Systems/InputSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/ScoreSystem.h"
#include "Components/InputComponent.h"
#include "Components/MovementComponent.h"
#include "Components/TransformComponent.h"
#include "Components/GoalComponent.h"
#include "WorldStatePacket.h"

#include <iostream>
#include <algorithm>

constexpr float PLAYER_1_POS = 0.0f;
constexpr float PLAYER_2_POS = 800.0f;

constexpr int MAX_PLAYERS = 2;

World::World()
{
    registry = std::make_unique<Registry>();
    inputSystem = std::make_unique<InputSystem>();
    movementSystem = std::make_unique<MovementSystem>();
    collisionSystem = std::make_unique<CollisionSystem>();
    scoreSystem = std::make_unique<ScoreSystem>();
}

World::~World()
{
    registry.reset();
    inputSystem.reset();
    movementSystem.reset();
    collisionSystem.reset();
    scoreSystem.reset();
}

void World::Init()
{
    // Ball
    int entityId = registry->AddEntity();
    registry->AddComponent(entityId, TransformComponent { 400.0f, 400.0f, 15.0f, 15.0f });
    registry->AddComponent(entityId, MovementComponent { 400.0f, 200.0f });
    registry->AddComponent(entityId, CollisionComponent { 15.0f, 15.0f, CollisionType::Bounce, CollisionTag::Ball });
    registry->AddComponent(entityId, BallComponent {});
}

GameState World::Update(float deltaTime)
{
    if (worldStatus != WorldStatus::Playing)
    {
        deltaTime = 0.0f;
    }

    registry->GetComponentsUnion(tempEntityIds, tempTransformComponents, tempCollisionComponents);
    const std::vector<CollisionEvent>& collisionEvents = collisionSystem->UpdateComponents(tempEntityIds, tempTransformComponents, tempCollisionComponents, *registry);

    registry->GetComponentsUnion(tempEntityIds, tempInputComponents, tempMovementComponents);
    inputSystem->UpdateComponents(tempInputComponents, tempMovementComponents);

    registry->GetComponentsUnion(tempEntityIds, tempMovementComponents, tempTransformComponents);
    movementSystem->UpdateComponents(deltaTime, tempEntityIds, tempMovementComponents, tempTransformComponents, collisionEvents);

    scoreSystem->UpdateComponents(*registry, collisionEvents);

    return GameState::Update;
}

int World::OnPlayerConnected()
{
    // Paddle
    const int playerEntityId = registry->AddEntity();
    const float x = players == 0 ? PLAYER_1_POS : PLAYER_2_POS;
    const float y = 300.0f;
    registry->AddComponent(playerEntityId, TransformComponent { x, y, 20.0f, 100.0f });     
    registry->AddComponent(playerEntityId, InputComponent { false, false });
    registry->AddComponent(playerEntityId, MovementComponent { 0.0f, 0.0f });
    registry->AddComponent(playerEntityId, CollisionComponent { 20.0f, 100.0f, CollisionType::Static, CollisionTag::Paddle });

    // Goal
    const int goalEntityId = registry->AddEntity();
    registry->AddComponent(goalEntityId, TransformComponent { x - (5 * players), 0.0f, 5.0f, 800.0f });
    registry->AddComponent(goalEntityId, CollisionComponent { 15.0f, 1000.0f, CollisionType::Static, CollisionTag::Goal });
    registry->AddComponent(goalEntityId, GoalComponent {0, players + 1});  

    ++players;
    if (players == MAX_PLAYERS)
    {
        worldStatus = WorldStatus::Playing;
    }

    return playerEntityId;
}

void World::OnPlayerInput(int entityId, bool up, bool down)
{
    InputComponent& input = registry->GetComponent<InputComponent>(entityId);
    input.up = up;
    input.down = down;
}

const Packet::WorldStatePacket& World::GetWorldState()
{
    const ComponentData<TransformComponent>& transformData = registry->GetComponentData<TransformComponent>();
    currentWorldState.count = std::min(transformData.dense.size(), Packet::MAX_ENTITIES);
    for (size_t i = 0; i < currentWorldState.count; ++i)
    {
        if (i >= Packet::MAX_ENTITIES)
        {
            std::cerr << "Trying to send more entities than max over the network" << std::endl;
        }

        const int entityId = transformData.dense[i];
        const float x = transformData.components[i].x;
        const float y = transformData.components[i].y;
        const float w = transformData.components[i].w;
        const float h = transformData.components[i].h;
        currentWorldState.entities[i] = { entityId, x, y, w, h };
    }

    const ComponentData<GoalComponent> goalData = registry->GetComponentData<GoalComponent>();
    currentWorldState.gameState.playerCount = std::min(goalData.dense.size(), Packet::MAX_PLAYERS);
    for (size_t i = 0; i < currentWorldState.gameState.playerCount; ++i)
    {
        if (i >= Packet::MAX_PLAYERS)
        {
            std::cerr << "Trying to send more players score than max over the network" << std::endl;
        }

        currentWorldState.gameState.score[i] = goalData.components[i].score;
    }
    return currentWorldState;
}