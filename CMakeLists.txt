cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/polcu/Documents/Programming shits/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
set(VCPKG_MANIFEST_MODE ON CACHE BOOL "" FORCE)

project(EnetGameProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(unofficial-enet CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)

# --- CONFIGURACIÓN DEL SERVIDOR ---
add_executable(GameServer 
	src/Server/server.cpp
	src/Server/NetworkSystem.h
	src/Server/NetworkSystem.cpp
	src/Server/ECS/Entity.h
	src/Server/ECS/Components/MovementComponent.h
	src/Server/ECS/Components/InputComponent.h
	src/Server/ECS/Components/PositionComponent.h
	src/Server/ECS/Systems/MovementSystem.h
	src/Server/ECS/Systems/MovementSystem.cpp
	src/Server/ECS/ComponentData.h
	src/Server/ECS/Registry.h
	src/Server/ECS/Registry.cpp
	src/Server/ECS/Systems/InputSystem.h
	src/Server/ECS/Systems/InputSystem.cpp
	src/Server/ECS/World.h
	src/Server/ECS/World.cpp
	src/Server/EngineContext.h
	src/Shared/GameState.h
)

target_link_libraries(GameServer PRIVATE 
	unofficial::enet::enet
	winmm wsock32 ws2_32
)

# --- CONFIGURACIÓN DEL CLIENTE ---
add_executable(GameClient 
	src/Client/client.cpp
	src/Client/EngineContext.h
	src/Client/InputSystem.h
	src/Client/InputSystem.cpp
	src/Client/NetworkSystem.h
	src/Client/NetworkSystem.cpp
	src/Client/RenderSystem.h
	src/Client/RenderSystem.cpp
)

target_link_libraries(GameClient PRIVATE
	unofficial::enet::enet 
	SDL3::SDL3
	winmm wsock32 ws2_32
)

target_include_directories(GameClient PRIVATE src/Shared)
target_include_directories(GameServer PRIVATE src/Shared)