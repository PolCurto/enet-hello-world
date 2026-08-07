#include "NetworkSystem.h"

#include <iostream>
#include <enet/enet.h>

#include "EngineContext.h"
#include "InputSystem.h"
#include "GameState.h"
#include "PlayerInputPacket.h"
#include "WorldStatePacket.h"
#include "RenderSystem.h"


NetworkSystem::NetworkSystem()
{
}

NetworkSystem::~NetworkSystem()
{
}

bool NetworkSystem::Init()
{
    if (!EnetInit())
    {
        return false;
    }

    if (!SetupHost())
    {
        return false;
    }

    if (!SetupPeer())
    {
        return false;
    }

    if (!ConnectToServer())
    {
        return false;
    }

    return true;
}

GameState NetworkSystem::Update(const EngineContext& engineContext)
{
    if (engineContext.inputSystem->HasInputEventHappened())
    {
        PlayerInputPacket inputData;
        inputData.up = (engineContext.inputSystem->upKey == KeyState::Down || engineContext.inputSystem->upKey == KeyState::Repeat);
        inputData.down = (engineContext.inputSystem->downKey == KeyState::Down || engineContext.inputSystem->downKey == KeyState::Repeat);
        SendInputData(inputData);
    }
    
    ListenToServer(engineContext);

    return GameState::Update; 
}

void NetworkSystem::Exit()
{
    enet_peer_disconnect(peer, 0);
    enet_host_destroy(client);
}

bool NetworkSystem::EnetInit()
{
    if (enet_initialize() != 0)
    {
        std::cerr << "Error al inicializar ENet en el Cliente.\n";
        return false;
    }
    atexit(enet_deinitialize);
    return true;
}

bool NetworkSystem::SetupHost()
{
    // Crear el Host del Cliente (nullptr significa que no se abre un puerto para escuchar)
    client = enet_host_create(nullptr, 1, 2, 0, 0);
    if (!client)
    {
        std::cerr << "No se pudo crear el host del cliente.\n";
        return false;
    }
    return true;
}

bool NetworkSystem::SetupPeer()
{
    // Configurar la direcci�n del servidor a donde nos queremos conectar
    ENetAddress address;
    enet_address_set_host(&address, "127.0.0.1"); // Localhost
    address.port = 8000;

    // Iniciar la conexi�n hacia el servidor (en el Canal 2)
    peer = enet_host_connect(client, &address, 2, 0);
    if (!peer)
    {
        std::cerr << "No hay peers disponibles para iniciar la conexi�n.\n";
        return false;
    }
    return true;
}

bool NetworkSystem::ConnectToServer()
{
    ENetEvent event;
    bool connected = false;

    std::cout << "[CLIENTE] Conectando al servidor...\n";

    // Esperar hasta 5 segundos a que el servidor acepte la conexi�n
    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) 
    {
        std::cout << "[CLIENTE] �Conexi�n establecida con �xito!\n";
        connected = true;
    }
    else
    {
        enet_peer_reset(peer);
        std::cerr << "[CLIENTE] La conexi�n fall� por timeout.\n";
        enet_host_destroy(client);
        return false;
    }

    return true;
}

void NetworkSystem::SendInputData(const PlayerInputPacket& inputData)
{
    ENetPacket* packet = enet_packet_create(&inputData, sizeof(inputData), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(client);
}

void NetworkSystem::ListenToServer(const EngineContext& engineContext)
{
    // Listen to the server (Split in methods in the future)
    ENetEvent event;
    while (enet_host_service(client, &event, 0) > 0)
    {
        switch (event.type) {
        case ENET_EVENT_TYPE_RECEIVE:
        {
            const WorldStatePacket* worldStatePacket = reinterpret_cast<const WorldStatePacket*>(event.packet->data);

            SendWorldStateToRender(*worldStatePacket, engineContext);

            enet_packet_destroy(event.packet);
            break;
        }
            
        case ENET_EVENT_TYPE_DISCONNECT:
            std::cout << "[CLIENTE] Desconectado.\n";
            break;
        }
    }
}

void NetworkSystem::SendWorldStateToRender(const WorldStatePacket& worldStatePacket, const EngineContext& engineContext)
{
    std::vector<float> renderValues;

    for (int i = 0; i < worldStatePacket.count; ++i)
    {
        const EntityState& entity = worldStatePacket.entities[i];
        renderValues.push_back(entity.x);
        renderValues.push_back(entity.y);
        renderValues.push_back(20.0f);
        renderValues.push_back(50.0f);
    }

    engineContext.renderSystem->FillRenderObjects(renderValues);
}