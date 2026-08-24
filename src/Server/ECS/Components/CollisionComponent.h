#pragma once

enum class CollisionType
{
    Static,
    Bounce
};

enum class CollisionTag
{
    Default,
    Paddle,
    Ball,
    Goal
};

struct CollisionComponent
{
    float w = 0.0f;
    float h = 0.0f;
    CollisionType type = CollisionType::Static;
    CollisionTag tag = CollisionTag::Default;
};