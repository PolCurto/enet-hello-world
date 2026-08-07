#pragma once

#include <vector>

struct TransformComponent;

struct EntityState
{
    int entityId;
    float x;
    float y;
    float w;
    float h;
};

constexpr size_t MAX_ENTITIES = 32;

struct WorldStatePacket 
{
    uint32_t count = 0;
    EntityState entities[MAX_ENTITIES];
};