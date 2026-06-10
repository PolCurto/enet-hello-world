#include <iostream>
#include <cstring>

#include "NetworkSystem.h"
#include "InputSystem.h"

int main()
{
	NetworkSystem networkSystem;
	InputSystem inputSystem;

	networkSystem.Init();
	inputSystem.Update();
	networkSystem.Update();

    std::cout << "[CLIENTE] Cerrando.\n";
    return 0;
}