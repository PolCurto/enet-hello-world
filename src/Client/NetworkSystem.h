#pragma once

#include <enet/enet.h>

class NetworkSystem
{
public:
	NetworkSystem();
	~NetworkSystem();

	bool Init();
	void Update();
	void Exit();

private:
	ENetPeer* peer = nullptr;
	ENetHost* client = nullptr;
};