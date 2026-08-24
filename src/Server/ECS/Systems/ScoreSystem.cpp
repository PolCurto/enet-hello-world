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
        CollisionData entityA = collisionEvents[i].entityA;
        CollisionData entityB = collisionEvents[i].entityB;

        if (entityA.collisionTag == CollisionTag::Ball && entityB.collisionTag == CollisionTag::Goal)
        {
            HandleGoal(entityA.entityId, entityB.entityId, registry);
        }
        else if (entityB.collisionTag == CollisionTag::Goal && entityA.collisionTag == CollisionTag::Ball)
        {
            HandleGoal(entityA.entityId, entityB.entityId, registry);
        }
    }
}

void ScoreSystem::HandleGoal(int ballEntityId, int goalEntityId, Registry& registry)
{
    GoalComponent& goalComponent = registry.GetComponent<GoalComponent>(goalEntityId);
    goalComponent.score += 1;

    std::cout << "New score: " << goalComponent.score << std::endl;
}