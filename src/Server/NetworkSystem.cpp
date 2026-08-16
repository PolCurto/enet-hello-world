#include "NetworkSystem.h"

#include <iostream>
#include <enet/enet.h>

#include "GameState.h"
#include "PlayerInputPacket.h"
#include "EngineContext.h"
#include "ECS/World.h"

NetworkSystem::NetworkSystem()
{
}

NetworkSystem::~NetworkSystem()
{
}

bool NetworkSystem::Init()
{
    if (enet_initialize() != 0) {
        std::cerr << "Error al inicializar ENet en el Servidor.\n";
        return false;
    }
    atexit(enet_deinitialize);

    ENetAddress address;
    address.host = ENET_HOST_ANY; // Escucha en cualquier IP de tu PC
    address.port = 8000;

    // Crear el Host del Servidor (Máximo 32 conexiones, 2 canales)
    server = enet_host_create(&address, 32, 2, 0, 0);
    if (!server) {
        std::cerr << "No se pudo crear el servidor.\n";
        return false;
    }

    std::cout << "[SERVIDOR] Escuchando en el puerto 1234...\n";

    return true;
}

GameState NetworkSystem::Update(const EngineContext& engineContext)
{
    ENetEvent event;

    BroadcastWorldState(engineContext);

    while (enet_host_service(server, &event, 0) > 0) 
    {
        switch (event.type) 
        {
            case ENET_EVENT_TYPE_CONNECT:
            {
                std::cout << "[SERVIDOR] ¡Cliente conectado desde "
                    << event.peer->address.host << ":"
                    << event.peer->address.port << "!\n";

                const int entityId = engineContext.world->OnPlayerConnected();
                event.peer->data = (void*)(uintptr_t)entityId;
                break;
            }   

            case ENET_EVENT_TYPE_RECEIVE:
            {
                PlayerInputPacket* inputPacket = reinterpret_cast<PlayerInputPacket*>(event.packet->data);
                engineContext.world->OnPlayerInput((int)(uintptr_t)event.peer->data, inputPacket->up, inputPacket->down);

                enet_packet_destroy(event.packet);
                break;
            } 
            case ENET_EVENT_TYPE_DISCONNECT:
            {
                std::cout << "[SERVIDOR] Cliente desconectado.\n";
                break;
            }
            
            default:
                break;
        }
    }
    
    return GameState::Update;
}

void NetworkSystem::Exit()
{
    enet_host_destroy(server);
}

void NetworkSystem::BroadcastWorldState(const EngineContext& engineContext)
{
    const Packet::WorldStatePacket& worldState = engineContext.world->GetWorldState();

    ENetPacket* packet = enet_packet_create(&worldState, sizeof(Packet::WorldStatePacket), ENET_PACKET_FLAG_RELIABLE);

    enet_host_broadcast(server, 0, packet);
}