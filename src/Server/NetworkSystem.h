#pragma once

#include <enet/enet.h>

enum class GameState;
struct EngineContext;

class NetworkSystem
{
public:
	NetworkSystem();
	~NetworkSystem();

	bool Init();
	GameState Update(const EngineContext& engineContext);
	void Exit();

private:
	ENetHost* server = nullptr;
};