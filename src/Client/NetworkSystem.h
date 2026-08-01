#pragma once

#include <enet/enet.h>

enum class GameState;
struct EngineContext;
struct PlayerInputPacket;

class NetworkSystem
{
public:
	NetworkSystem();
	~NetworkSystem();

	bool Init();
	GameState Update(const EngineContext& engineContext);
	void Exit();

private:
	bool EnetInit();
	bool SetupHost();
	bool SetupPeer();
	bool ConnectToServer();

	void SendInputData(const PlayerInputPacket& inputData);
	void ListenToServer();

private:
	ENetPeer* peer = nullptr;
	ENetHost* client = nullptr;
};