#pragma once

#include <enet/enet.h>

enum class GameState;

struct EngineContext;
struct PlayerInputPacket;
struct WorldStatePacket;

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
	void ListenToServer(const EngineContext& engineContext);

	void SendWorldStateToRender(const WorldStatePacket& worldStatePacket, const EngineContext& engineContext);

private:
	ENetPeer* peer = nullptr;
	ENetHost* client = nullptr;
};