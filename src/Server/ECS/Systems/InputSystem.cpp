#include "InputSystem.h"

#include <vector>

#include "../Components/InputComponent.h"
#include "../Components/MovementComponent.h"

void InputSystem::UpdateComponents(const std::vector<InputComponent*>& inputComponents, 
                                   std::vector<MovementComponent*>& movementComponents)
{
    for (size_t i = 0; i < inputComponents.size(); ++i)
    {
        const InputComponent& input = *inputComponents[i];
        MovementComponent& movement = *movementComponents[i];

        movement.speedX = 0.0f;
        movement.speedY = 0.0f;

        if (input.up)
        {
            movement.speedY -= 1.0f;
        }   
        if (input.down)
        {
            movement.speedY += 1.0f;
        }
    }
}