#pragma once

#include <vector>

#include "../Utils/CollisionEvent.h"

struct MovementComponent;
struct TransformComponent;
struct CollisionComponent;

class CollisionSystem
{
public:
    CollisionSystem() = default;
    ~CollisionSystem() = default;

    const std::vector<CollisionEvent>& UpdateComponents(const std::vector<int>& entityIds,
                                                        const std::vector<TransformComponent*>& transformComponents,
                                                        const std::vector<MovementComponent*>& movementComponents,
                                                        const std::vector<CollisionComponent*>& collisionComponents);

private:
    void CheckScreenBoundaries(TransformComponent& transformComponent,
                               MovementComponent& movementComponent,
                               CollisionComponent& collisionComponent);

    std::vector<CollisionEvent> collisionEvents;
};