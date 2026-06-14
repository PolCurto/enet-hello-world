#pragma once

class Entity
{
    public:
        Entity() = default;
        Entity(int id) : id(id) {}
        ~Entity() = default;

    public:
        int id;
};