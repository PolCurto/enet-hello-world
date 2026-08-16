#pragma once

#include <vector>

struct CollisionEvent;
struct GoalComponent;

class Registry;

class ScoreSystem
{
public:
    ScoreSystem() = default;
    ~ScoreSystem() = default;

    void UpdateComponents(Registry& registry, const std::vector<CollisionEvent>& collisionEvents);

private:
    void HandleGoal(int ballEntityId, int goalEntityId, Registry& registry);
};