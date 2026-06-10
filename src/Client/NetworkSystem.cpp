#include "NetworkSystem.h"

#include <iostream>

NetworkSystem::NetworkSystem()
{
}

NetworkSystem::~NetworkSystem()
{
}

bool NetworkSystem::Init()
{
    if (enet_initialize() != 0)
    {
        std::cerr << "Error al inicializar ENet en el Cliente.\n";
        return false;
    }
    atexit(enet_deinitialize);

    // Crear el Host del Cliente (nullptr significa que no se abre un puerto para escuchar)
    client = enet_host_create(nullptr, 1, 2, 0, 0);
    if (!client)
    {
        std::cerr << "No se pudo crear el host del cliente.\n";
        return false;
    }

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

void NetworkSystem::Update()
{
    // Enviar un mensaje
    const char* message = "�Hola Servidor! Soy tu cliente en C++.";

    // Crear el paquete pasando los bytes, el tama�o (incluyendo el \0) y la flag de FIABLE (estilo TCP)
    ENetPacket* packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);

    // Enviar el paquete al peer por el Canal 0
    enet_peer_send(peer, 0, packet);

    // Forzar a ENet a que env�e los paquetes retenidos en el buffer inmediatamente
    enet_host_flush(client);
    std::cout << "[CLIENTE] Mensaje enviado.\n";

    // Esperar un momento para asegurar el env�o y luego desconectar
    ENetEvent event;
    enet_host_service(client, &event, 1000);
    enet_peer_disconnect(peer, 0);
}

void NetworkSystem::Exit()
{
    // Procesar la desconexi�n
    ENetEvent event;
    enet_host_service(client, &event, 1000);

    enet_host_destroy(client);
}


