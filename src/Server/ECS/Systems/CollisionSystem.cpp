#include "CollisionSystem.h"

#include <vector>

#include "../Components/TransformComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Registry.h"

constexpr float SCREEN_WIDTH = 800.0f;
constexpr float SCREEN_HEIGHT = 600.0f;

const std::vector<CollisionEvent>& CollisionSystem::UpdateComponents(const std::vector<int>& entityIds,
                                                                     const std::vector<TransformComponent*>& transformComponents,
                                                                     const std::vector<CollisionComponent*>& collisionComponents,
                                                                     Registry& registry)
{
    collisionEvents.clear();

    for (size_t i = 0; i < transformComponents.size(); ++i)
    {
        TransformComponent& transform = *transformComponents[i];
        CollisionComponent& collision = *collisionComponents[i];

        CheckScreenBoundaries(transform, collision, registry, entityIds[i]);

        for (size_t j = i + 1; j < transformComponents.size(); ++j)
        {
            const TransformComponent& otherTransform = *transformComponents[j];
            const CollisionComponent& otherCollision = *collisionComponents[j];

            bool isColliding = !(transform.x + transform.w < otherTransform.x ||
                                transform.x > otherTransform.x + otherTransform.w ||
                                transform.y + transform.h < otherTransform.y ||
                                transform.y > otherTransform.y + otherTransform.h);

            if (isColliding)
            {
                CollisionData entityA = { entityIds[i], collision.type, collision.tag };
                CollisionData entityB = { entityIds[j], otherCollision.type, otherCollision.tag };
                collisionEvents.push_back({ entityA, entityB });
            }
        }
    }
    return collisionEvents; 
}    

void CollisionSystem::CheckScreenBoundaries(TransformComponent& transformComponent,
                                            CollisionComponent& collisionComponent,
                                            Registry& registry,
                                            int entityId)
{
    if (!registry.HasComponent<MovementComponent>(entityId))
    {
        return;
    }

    MovementComponent& movementComponent = registry.GetComponent<MovementComponent>(entityId);

    if (transformComponent.x < 0.0f)
    {
        transformComponent.x = 0.0f;
        if (collisionComponent.type == CollisionType::Bounce)
        {
            movementComponent.speedX = -movementComponent.speedX;
        }
    }
    else if (transformComponent.x + transformComponent.w > SCREEN_WIDTH)
    {
        transformComponent.x = SCREEN_WIDTH - transformComponent.w;
        if (collisionComponent.type == CollisionType::Bounce)
        {
            movementComponent.speedX = -movementComponent.speedX;
        }
    }

    if (transformComponent.y < 0.0f)
    {
        transformComponent.y = 0.0f;
        if (collisionComponent.type == CollisionType::Bounce)
        {
            movementComponent.speedY = -movementComponent.speedY;
        }
    }
    else if (transformComponent.y + transformComponent.h > SCREEN_HEIGHT)
    {
        transformComponent.y = SCREEN_HEIGHT - transformComponent.h;
        if (collisionComponent.type == CollisionType::Bounce)
        {
            movementComponent.speedY = -movementComponent.speedY;
        }
    }
}