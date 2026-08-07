#pragma once

#include <vector>

struct MovementComponent;
struct TransformComponent;
struct CollisionComponent;

class CollisionSystem
{
public:
    CollisionSystem() = default;
    ~CollisionSystem() = default;

    void UpdateComponents(const std::vector<TransformComponent*>& transformComponents,
                          const std::vector<MovementComponent*>& movementComponents,
                          const std::vector<CollisionComponent*>& collisionComponents);

private:
    void CheckScreenBoundaries( TransformComponent& transformComponent,
                                MovementComponent& movementComponent,
                                CollisionComponent& collisionComponent);
};