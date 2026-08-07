#pragma once

#include <vector>

struct MovementComponent;
struct TransformComponent;

class MovementSystem
{
public:
    MovementSystem() = default;
    ~MovementSystem() = default;

    void UpdateComponents(const std::vector<MovementComponent*>& movementComponents,
                          std::vector<TransformComponent*>& transformComponents,
                          const float deltaTime);
};