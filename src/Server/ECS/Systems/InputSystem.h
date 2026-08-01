#pragma once

#include <vector>

struct MovementComponent;
struct InputComponent;

class InputSystem
{
public:
    InputSystem() = default;
    ~InputSystem() = default;

    void UpdateComponents(const std::vector<InputComponent>& inputComponents,
                          const std::vector<MovementComponent>& movementComponents);
};