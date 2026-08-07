#include "MovementSystem.h"

#include <vector>

#include "../Components/MovementComponent.h"
#include "../Components/TransformComponent.h"

// TODO: DELETE
#include <iostream>

void MovementSystem::UpdateComponents(const std::vector<MovementComponent*>& movementComponents, 
                                      std::vector<TransformComponent*>& transformComponents, 
                                      const float deltaTime)
{
    for (size_t i = 0; i < movementComponents.size(); ++i)
    {
        const MovementComponent& movement = *movementComponents[i];
        TransformComponent& transform = *transformComponents[i];

        transform.x += movement.speedX * deltaTime;
        transform.y += movement.speedY * deltaTime;
    }
}