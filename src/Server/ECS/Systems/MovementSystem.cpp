#include "MovementSystem.h"

#include <vector>

#include "../Components/MovementComponent.h"
#include "../Components/PositionComponent.h"

// TODO: DELETE
#include <iostream>

void MovementSystem::UpdateComponents(const std::vector<MovementComponent*>& movementComponents, 
                                      std::vector<PositionComponent*>& positionComponents, 
                                      const float deltaTime)
{
    for (size_t i = 0; i < movementComponents.size(); ++i)
    {
        const MovementComponent& movement = *movementComponents[i];
        PositionComponent& position = *positionComponents[i];

        position.x += movement.speedX * deltaTime;
        position.y += movement.speedY * deltaTime;
    }
}