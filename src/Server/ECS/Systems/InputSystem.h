#pragma once

#include <vector>

struct MovementComponent;
struct InputComponent;

class InputSystem
{
public:
    InputSystem() = default;
    ~InputSystem() = default;

    void UpdateComponents(const std::vector<InputComponent*>& inputComponents,
                          std::vector<MovementComponent*>& movementComponents);
};