#pragma once

#include <enet/enet.h>

enum class GameState;
struct EngineContext;

struct PlayerInputPacket 
{
	bool up;
	bool down;
};

class NetworkSystem
{
public:
	NetworkSystem();
	~NetworkSystem();

	bool Init();
	GameState Update();
	void Exit();

private:
	ENetHost* server = nullptr;
};