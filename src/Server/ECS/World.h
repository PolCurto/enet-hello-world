#pragma once

#include <memory>
#include <vector>

#include "WorldStatePacket.h"

class Registry;
class InputSystem;
class MovementSystem;
class CollisionSystem;
class ScoreSystem;

enum class GameState;

struct InputComponent;
struct MovementComponent;
struct TransformComponent;
struct CollisionComponent;

class World
{
public:
    World();
    ~World();

    void Init();
    GameState Update(const float deltaTime);

    int OnPlayerConnected();
    void OnPlayerInput(int entityId, bool up, bool down);

    const Packet::WorldStatePacket& GetWorldState();

private:
    std::unique_ptr<Registry> registry;

    std::unique_ptr<InputSystem> inputSystem;
    std::unique_ptr<MovementSystem> movementSystem;
    std::unique_ptr<CollisionSystem> collisionSystem;
    std::unique_ptr<ScoreSystem> scoreSystem;

    std::vector<int> tempEntityIds;
    std::vector<InputComponent*> tempInputComponents;
    std::vector<MovementComponent*> tempMovementComponents;
    std::vector<TransformComponent*> tempTransformComponents;
    std::vector<CollisionComponent*> tempCollisionComponents;

    Packet::WorldStatePacket currentWorldState;

    bool playerConnected = false;
};