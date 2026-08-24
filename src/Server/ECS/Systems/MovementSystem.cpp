#include "MovementSystem.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "../Components/MovementComponent.h"
#include "../Components/TransformComponent.h"

constexpr float RESPAWN_SPEED = 400.0f;
constexpr float TWO_PI = 6.28318530718f;
constexpr float BOUNCE_SPEED_MULTIPLIER = 1.05f;
constexpr float MAX_BOUNCE_SPEED = 1000.0f;

void MovementSystem::UpdateComponents(const float deltaTime,
                                      const std::vector<int>& entityIds,
                                      const std::vector<MovementComponent*>& movementComponents, 
                                      std::vector<TransformComponent*>& transformComponents, 
                                      const std::vector<CollisionEvent>& collisionEvents)
{

    for (size_t i = 0; i < movementComponents.size(); ++i)
    {
        MovementComponent& movement = *movementComponents[i];
        TransformComponent& transform = *transformComponents[i];

        for (const CollisionEvent event : collisionEvents)
        {
            if (event.entityA.entityId == entityIds[i] && event.entityA.collisionTag == CollisionTag::Ball)
            {
                if (event.entityB.collisionTag == CollisionTag::Goal)
                {
                    RespawnBall(transform, movement);
                }
                else if (event.entityB.collisionTag == CollisionTag::Paddle)
                {
                    for (size_t j = 0; j < entityIds.size(); ++j)
                    {
                        if (entityIds[j] == event.entityB.entityId)
                        {
                            ApplyPaddleBounce(transform, movement, *transformComponents[j]);
                        }
                    }
                }
            }
            else if (event.entityB.entityId == entityIds[i] && event.entityA.collisionTag == CollisionTag::Ball)
            {
                if (event.entityA.collisionTag == CollisionTag::Goal)
                {
                    RespawnBall(transform, movement);
                }
                else if (event.entityA.collisionTag == CollisionTag::Paddle)
                {
                    for (size_t j = 0; j < entityIds.size(); ++j)
                    {
                        if (entityIds[j] == event.entityA.entityId)
                        {
                            ApplyPaddleBounce(transform, movement, *transformComponents[j]);
                        }
                    }
                }
            }
            else
            {
                continue;
            }
        }

        transform.x += movement.speedX * deltaTime;
        transform.y += movement.speedY * deltaTime;
    }
}

void MovementSystem::RespawnBall(TransformComponent& ballTransform, MovementComponent& ballMovement)
{
    std::cout << "Respawn ball" << std::endl;
    ballTransform.x = 400.0f;
    ballTransform.y = 400.0f;
    std::uniform_real_distribution<float> angleDistribution(0.0f, TWO_PI);
    const float angle = angleDistribution(randomEngine);
    ballMovement.speedX = RESPAWN_SPEED * std::cos(angle);
    ballMovement.speedY = RESPAWN_SPEED * std::sin(angle);
}

void MovementSystem::ApplyPaddleBounce(TransformComponent& ballTransform, MovementComponent& ballMovement, const TransformComponent& paddleTransform)
{
    std::cout << "Apply paddle bounce" << std::endl;

    const float ballCenterY = ballTransform.y + (ballTransform.h * 0.5f);
    const float paddleCenterY = paddleTransform.y + (paddleTransform.h * 0.5f);
    const float relativeIntersectY = ballCenterY - paddleCenterY;

    float normalizedRelativeIntersectionY = relativeIntersectY / (paddleTransform.h * 0.5f);
    normalizedRelativeIntersectionY = std::clamp(normalizedRelativeIntersectionY, -1.0f, 1.0f);

    constexpr float MAX_BOUNCE_ANGLE = 60.0f * (3.14159f / 180.0f);
    const float bounceAngle = normalizedRelativeIntersectionY * MAX_BOUNCE_ANGLE;

    const float currentSpeed = std::sqrt(ballMovement.speedX * ballMovement.speedX + ballMovement.speedY * ballMovement.speedY);
    const float speed = std::min(currentSpeed * BOUNCE_SPEED_MULTIPLIER, MAX_BOUNCE_SPEED);
    const float directionX = (ballMovement.speedX > 0.0f) ? -1.0f : 1.0f;

    ballMovement.speedX = speed * std::cos(bounceAngle) * directionX;
    ballMovement.speedY = speed * std::sin(bounceAngle);
}