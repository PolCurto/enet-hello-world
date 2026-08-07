#pragma once

#include <memory>
#include <vector>

class Registry;
class InputSystem;
class MovementSystem;
enum class GameState;

struct InputComponent;
struct MovementComponent;
struct PositionComponent;
struct WorldStatePacket;

class World
{
public:
    World();
    ~World();

    void Init();
    GameState Update();

    int OnPlayerConnected();
    void OnPlayerInput(int entityId, bool up, bool down);

    const WorldStatePacket& GetWorldState() const;

private:
    std::unique_ptr<Registry> registry;

    std::unique_ptr<InputSystem> inputSystem;
    std::unique_ptr<MovementSystem> movementSystem;

    std::vector<InputComponent*> tempInputComponents;
    std::vector<MovementComponent*> tempMovementComponents;
    std::vector<PositionComponent*> tempPositionComponents;
};