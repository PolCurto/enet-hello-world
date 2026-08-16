#pragma once

#include <vector>

struct TransformComponent;

namespace Packet
{
    struct EntityState
    {
        int entityId;
        float x;
        float y;
        float w;
        float h;
    };

    struct GameState
    {
        int score[MAX_PLAYERS];
        // TODO: ADd state like: waiting, playing, game over
    };

    constexpr size_t MAX_ENTITIES = 32;
    constexpr size_t MAX_PLAYERS = 2;

    struct WorldStatePacket 
    {
        uint32_t count = 0;
        EntityState entities[MAX_ENTITIES];
        GameState gameState;
};
}

