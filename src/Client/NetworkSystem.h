#pragma once

#include <enet/enet.h>

enum class GameState;

struct EngineContext;
struct PlayerInputPacket;

namespace Packet
{
	struct WorldStatePacket;
}

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

	void SendWorldStateToRender(const Packet::WorldStatePacket& worldStatePacket, const EngineContext& engineContext);

private:
	ENetPeer* peer = nullptr;
	ENetHost* client = nullptr;
};