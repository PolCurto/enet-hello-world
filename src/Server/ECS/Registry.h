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

    int AddEntity();
    void RemoveEntity(int entityId);

    template <typename T>
    void AddComponent(int entityId, const T& component)
    {
        ComponentData<T>& data = std::get<ComponentData<T>>(components);
        const int denseIdx = static_cast<int>(data.dense.size());

        data.dense.push_back(entityId);
        data.components.push_back(component);

        data.sparse[entityId] = denseIdx;
    }

    template <typename T>
    bool HasComponent(int entityId) const
    {
        const ComponentData<T>& data = std::get<ComponentData<T>>(components);
        return data.sparse[entityId] != -1;
    }

    template <typename T>
    T& GetComponent(const int entityId)
    {
        ComponentData<T>& data = std::get<ComponentData<T>>(components);
        
        const int componentIdx = data.sparse[entityId];
        return data.components[componentIdx];
    }

    template <typename T, typename U>
    void GetComponentsUnion(std::vector<T*>& outComponentsT, std::vector<U*>& outComponentsU)
    {
        ComponentData<T>& dataT = std::get<ComponentData<T>>(components);
        ComponentData<U>& dataU = std::get<ComponentData<U>>(components);

        const std::vector<int>& smallDense = (dataT.dense.size() < dataU.dense.size()) ? dataT.dense : dataU.dense;

        for (int entityId : smallDense)
        {
            if (HasComponent<T>(entityId) && HasComponent<U>(entityId))
            {
                outComponentsT.push_back(&GetComponent<T>(entityId));
                outComponentsU.push_back(&GetComponent<U>(entityId));
            }
        }
    }
    

private:
    template <typename T>
        void ForEachPool(T&& func) {
            std::apply([&](auto&... pool) {
                (func(pool), ...);
            }, components);
        }

private:
    std::tuple<ComponentData<InputComponent>, 
               ComponentData<PositionComponent>, 
               ComponentData<MovementComponent>> components;

    int nextEntityId = 0;
};