#pragma once

#include <tuple>
#include "ECS/ComponentData.h"

#include "ECS/Components/InputComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/MovementComponent.h"

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