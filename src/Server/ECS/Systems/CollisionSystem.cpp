#include "CollisionSystem.h"

#include <vector>

#include "../Components/TransformComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/CollisionComponent.h"

constexpr float SCREEN_WIDTH = 800.0f;
constexpr float SCREEN_HEIGHT = 600.0f;

const std::vector<CollisionEvent>& CollisionSystem::UpdateComponents(const std::vector<int>& entityIds,
                                                                     const std::vector<TransformComponent*>& transformComponents,
                                                                     const std::vector<MovementComponent*>& movementComponents,
                                                                     const std::vector<CollisionComponent*>& collisionComponents)
{
    collisionEvents.clear();

    for (size_t i = 0; i < transformComponents.size(); ++i)
    {
        TransformComponent& transform = *transformComponents[i];
        MovementComponent& movement = *movementComponents[i];
        CollisionComponent& collision = *collisionComponents[i];

        CheckScreenBoundaries(transform, movement, collision);

        for (size_t j = 0; j < transformComponents.size(); ++j)
        {
            if (i == j) continue;
            const TransformComponent& otherTransform = *transformComponents[j];
            const CollisionComponent& otherCollision = *collisionComponents[j];

            bool isColliding = !(transform.x + transform.w < otherTransform.x ||
                                transform.x > otherTransform.x + otherTransform.w ||
                                transform.y + transform.h < otherTransform.y ||
                                transform.y > otherTransform.y + otherTransform.h);

            if (isColliding)
            {
                if (collision.type == CollisionType::Bounce)
                {
                    movement.speedX = -movement.speedX;
                    movement.speedY = -movement.speedY;
                }
                else if (collision.type == CollisionType::Static)
                {
                    movement.speedX = 0.0f;
                    movement.speedY = 0.0f;
                }

                collisionEvents.push_back({entityIds[i], entityIds[j]});
            }
        }
    }
    return collisionEvents; 
}    

void CollisionSystem::CheckScreenBoundaries(TransformComponent& transformComponent,
                                            MovementComponent& movementComponent,
                                            CollisionComponent& collisionComponent)
{
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