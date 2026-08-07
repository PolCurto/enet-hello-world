#pragma once

enum class CollisionType
{
    Static,
    Bounce
};

struct CollisionComponent
{
    float w = 0.0f;
    float h = 0.0f;
    CollisionType type = CollisionType::Static;
};