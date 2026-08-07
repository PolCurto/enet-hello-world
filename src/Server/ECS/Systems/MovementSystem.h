#pragma once

#include <vector>

struct MovementComponent;
struct PositionComponent;

class MovementSystem
{
public:
    MovementSystem() = default;
    ~MovementSystem() = default;

    void UpdateComponents(const std::vector<MovementComponent*>& movementComponents,
                          std::vector<PositionComponent*>& positionComponents,
                          const float deltaTime);
};