#pragma once

#include <vector>

#include "../Utils/CollisionEvent.h"

struct MovementComponent;
struct TransformComponent;
struct CollisionComponent;

class Registry;

class CollisionSystem
{
public:
    CollisionSystem() = default;
    ~CollisionSystem() = default;

    const std::vector<CollisionEvent>& UpdateComponents(const std::vector<int>& entityIds,
                                                        const std::vector<TransformComponent*>& transformComponents,
                                                        const std::vector<CollisionComponent*>& collisionComponents,
                                                        Registry& registry);

private:
    void CheckScreenBoundaries(TransformComponent& transformComponent,
                               CollisionComponent& collisionComponent,
                               Registry& registry,
                               int entityId);

    std::vector<CollisionEvent> collisionEvents;
};