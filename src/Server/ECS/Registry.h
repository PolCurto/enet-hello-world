#pragma once

#include <tuple>
#include "ComponentData.h"

#include "Components/InputComponent.h"
#include "Components/TransformComponent.h"
#include "Components/MovementComponent.h"
#include "Components/CollisionComponent.h"

class Registry
{
public:
    Registry() : components(std::make_tuple(
            ComponentData<InputComponent>{},
            ComponentData<TransformComponent>{},
            ComponentData<MovementComponent>{},
            ComponentData<CollisionComponent>{}
        )),
        nextEntityId(0)
    {
    }
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

    template <typename T>
    const ComponentData<T>& GetComponentData() const
    {
        return std::get<ComponentData<T>>(components);
    }

    template <typename... Comps>
    void GetComponentsUnion(std::vector<int>& outEntityIds, std::vector<Comps*>&... outComponents)
    {
        outEntityIds.clear();
        (outComponents.clear(), ...);

        if (((std::get<ComponentData<Comps>>(components).dense.empty()) || ...)) 
        {
            return;
        }

        const std::vector<int>* smallestDense = nullptr;
        size_t minSize = std::numeric_limits<size_t>::max();

        auto findSmallest = [&](const auto& componentData) {
            if (componentData.dense.size() < minSize) {
                minSize = componentData.dense.size();
                smallestDense = &componentData.dense;
            }
        };

        (findSmallest(std::get<ComponentData<Comps>>(components)), ...);

        if (!smallestDense) return;

        for (int entityId : *smallestDense)
        {
            bool hasAll = (HasComponent<Comps>(entityId) && ...);

            if (hasAll)
            {
                outEntityIds.push_back(entityId);
                (outComponents.push_back(&GetComponent<Comps>(entityId)), ...);
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
    std::tuple<
        ComponentData<InputComponent>, 
        ComponentData<TransformComponent>, 
        ComponentData<MovementComponent>,
        ComponentData<CollisionComponent>
    > components;

    int nextEntityId = 0;
};