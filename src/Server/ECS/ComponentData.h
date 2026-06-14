#pragma once

#include <vector>

template <typename T>
struct ComponentData
{
    std::vector<int> dense;
    std::vector<T> components;
    std::vector<int> sparse;
};