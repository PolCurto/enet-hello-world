#include <enet/enet.h>
#include <iostream>
#include <cstring>

// HOLA DESDE EL SLN
int main() {
    if (enet_initialize() != 0) {
        std::cerr << "Error al inicializar ENet en el Cliente.\n";
        return 1;
    }
    atexit(enet_deinitialize);

    // Crear el Host del Cliente (nullptr significa que no se abre un puerto para escuchar)
    ENetHost* client = enet_host_create(nullptr, 1, 2, 0, 0);
    if (!client) {
        std::cerr << "No se pudo crear el host del cliente.\n";
        return 1;
    }

    // Configurar la dirección del servidor a donde nos queremos conectar
    ENetAddress address;
    enet_address_set_host(&address, "127.0.0.1"); // Localhost
    address.port = 8000;

    // Iniciar la conexión hacia el servidor (en el Canal 2)
    ENetPeer* peer = enet_host_connect(client, &address, 2, 0);
    if (!peer) {
        std::cerr << "No hay peers disponibles para iniciar la conexión.\n";
        return 1;
    }

    ENetEvent event;
    bool connected = false;

    std::cout << "[CLIENTE] Conectando al servidor...\n";

    // Esperar hasta 5 segundos a que el servidor acepte la conexión
    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        std::cout << "[CLIENTE] ¡Conexión establecida con éxito!\n";
        connected = true;
    }
    else {
        enet_peer_reset(peer);
        std::cerr << "[CLIENTE] La conexión falló por timeout.\n";
        enet_host_destroy(client);
        return 1;
    }

    if (connected) {
        // Enviar un mensaje
        const char* message = "¡Hola Servidor! Soy tu cliente en C++.";

        // Crear el paquete pasando los bytes, el tamaño (incluyendo el \0) y la flag de FIABLE (estilo TCP)
        ENetPacket* packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);

        // Enviar el paquete al peer por el Canal 0
        enet_peer_send(peer, 0, packet);

        // Forzar a ENet a que envíe los paquetes retenidos en el buffer inmediatamente
        enet_host_flush(client);
        std::cout << "[CLIENTE] Mensaje enviado.\n";

        // Esperar un momento para asegurar el envío y luego desconectar
        enet_host_service(client, &event, 1000);
        enet_peer_disconnect(peer, 0);

        // Procesar la desconexión
        enet_host_service(client, &event, 1000);
    }

    enet_host_destroy(client);
    std::cout << "[CLIENTE] Cerrando.\n";
    return 0;
}