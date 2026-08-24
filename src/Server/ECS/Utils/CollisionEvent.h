#pragma once

#include "../Components/CollisionComponent.h"

struct CollisionData
{
    int entityId;
    CollisionType collisionType;
    CollisionTag collisionTag;
};

struct CollisionEvent
{
    CollisionData entityA;
    CollisionData entityB;
};