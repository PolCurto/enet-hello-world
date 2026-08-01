#pragma once

class NetworkSystem;
class World;

struct EngineContext
{
    NetworkSystem* networkSystem;
    World* world;
};