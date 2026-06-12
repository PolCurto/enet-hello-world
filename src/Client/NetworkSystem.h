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
	GameState Update(const EngineContext& engineContext);
	void Exit();

private:
	ENetPeer* peer = nullptr;
	ENetHost* client = nullptr;
};