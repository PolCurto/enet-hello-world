#include "ScoreSystem.h"

#include <vector>
#include <iostream>

#include "../Components/GoalComponent.h"
#include "../Components/BallComponent.h"
#include "../Utils/CollisionEvent.h"
#include "../Registry.h"

void ScoreSystem::UpdateComponents(Registry& registry, const std::vector<CollisionEvent>& collisionEvents)
{
    for (size_t i = 0; i < collisionEvents.size(); ++i)
    {
        int entityA = collisionEvents[i].entityA;
        int entityB = collisionEvents[i].entityB;

        if (registry.HasComponent<BallComponent>(entityA) && registry.HasComponent<GoalComponent>(entityB))
        {
            HandleGoal(entityA, entityB, registry);
        }
        else if (registry.HasComponent<BallComponent>(entityB) && registry.HasComponent<GoalComponent>(entityA))
        {
            HandleGoal(entityB, entityA, registry);
        }
    }
}

void ScoreSystem::HandleGoal(int ballEntityId, int goalEntityId, Registry& registry)
{
    GoalComponent& goalComponent = registry.GetComponent<GoalComponent>(goalEntityId);
    goalComponent.score += 1;

    std::cout << "New score: " << goalComponent.score << std::endl;
}