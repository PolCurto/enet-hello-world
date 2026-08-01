#pragma once

#include <tuple>
#include "ComponentData.h"

#include "Components/InputComponent.h"
#include "Components/PositionComponent.h"
#include "Components/MovementComponent.h"

class Registry
{
public:
    Registry();
    ~Registry();

    void AddEntity();
    void RemoveEntity(int entityId);

    template <typename T>
    void AddComponent(int entityId, const T& component)
    {

    }

private:
    std::tuple<ComponentData<InputComponent>, 
               ComponentData<PositionComponent>, 
               ComponentData<MovementComponent>> components;
};