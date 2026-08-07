#include "Registry.h"

Registry::~Registry()
{
}

int Registry::AddEntity()
{
   int entityId = nextEntityId++;

    ForEachPool([entityId](auto& pool) 
    {
        pool.sparse.push_back(-1);
    });

    return entityId;
}

void Registry::RemoveEntity(int entityId)
{
  
}