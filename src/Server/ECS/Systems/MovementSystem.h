#pragma once

#include <random>
#include <vector>

#include "../Utils/CollisionEvent.h"

struct MovementComponent;
struct TransformComponent;

class MovementSystem
{
public:
    MovementSystem() = default;
    ~MovementSystem() = default;

    void UpdateComponents(const float deltaTime, 
                          const std::vector<int>& entityIds,
                          const std::vector<MovementComponent*>& movementComponents,
                          std::vector<TransformComponent*>& transformComponents,
                          const std::vector<CollisionEvent>& collisionEvents);
                        
private:
    void RespawnBall(TransformComponent& ballTransform, MovementComponent& ballMovement);

    void ApplyPaddleBounce(TransformComponent& ballTransform, MovementComponent& ballMovement, const TransformComponent& paddleTransform);

    std::mt19937 randomEngine { std::random_device{}() };
};