#include "World.h"

#include "Registry.h"
#include "GameState.h"

World::World()
{
}

World::~World()
{
}

void World::Init()
{
    registry = std::make_unique<Registry>();
}

GameState World::Update()
{
    return GameState::Update;
}