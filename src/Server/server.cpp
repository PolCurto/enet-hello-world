#include <enet/enet.h>
#include <iostream>
#include <cstring>

int main() {
    if (enet_initialize() != 0) {
        std::cerr << "Error al inicializar ENet en el Servidor.\n";
        return 1;
    }
    atexit(enet_deinitialize);

    ENetAddress address;
    address.host = ENET_HOST_ANY; // Escucha en cualquier IP de tu PC
    address.port = 8000;

    // Crear el Host del Servidor (Máximo 32 conexiones, 2 canales)
    ENetHost* server = enet_host_create(&address, 32, 2, 0, 0);
    if (!server) {
        std::cerr << "No se pudo crear el servidor.\n";
        return 1;
    }

    std::cout << "[SERVIDOR] Escuchando en el puerto 1234...\n";

    ENetEvent event;
    bool running = true;

    while (running) {
        // Enet_host_service espera eventos de red (en este caso, timeout de 10ms)
        while (enet_host_service(server, &event, 10) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "[SERVIDOR] ¡Cliente conectado desde "
                    << event.peer->address.host << ":"
                    << event.peer->address.port << "!\n";
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "[SERVIDOR] Mensaje recibido: "
                    << (char*)event.packet->data << "\n";

                // Destruir el paquete tras leerlo
                enet_packet_destroy(event.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "[SERVIDOR] Cliente desconectado.\n";
                break;

            default:
                break;
            }
        }
    }

    enet_host_destroy(server);
    return 0;
}