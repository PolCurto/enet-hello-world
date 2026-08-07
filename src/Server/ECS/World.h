#pragma once

#include <memory>
#include <vector>

#include "WorldStatePacket.h"

class Registry;
class InputSystem;
class MovementSystem;
enum class GameState;

struct InputComponent;
struct MovementComponent;
struct TransformComponent;

class World
{
public:
    World();
    ~World();

    void Init();
    GameState Update(const float deltaTime);

    int OnPlayerConnected();
    void OnPlayerInput(int entityId, bool up, bool down);

    const WorldStatePacket& GetWorldState();

private:
    std::unique_ptr<Registry> registry;

    std::unique_ptr<InputSystem> inputSystem;
    std::unique_ptr<MovementSystem> movementSystem;

    std::vector<InputComponent*> tempInputComponents;
    std::vector<MovementComponent*> tempMovementComponents;
    std::vector<TransformComponent*> tempTransformComponents;

    WorldStatePacket currentWorldState;
};