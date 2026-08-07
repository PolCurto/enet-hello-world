#pragma once
#include <chrono>

class Clock
{
public:
    Clock() : lastTime(std::chrono::high_resolution_clock::now()) {}

    float Restart()
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsed = currentTime - lastTime;
        lastTime = currentTime;

        float dt = elapsed.count();
        return (dt > 0.1f) ? 0.1f : dt;
    }

private:
    std::chrono::high_resolution_clock::time_point lastTime;
};