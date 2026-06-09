cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/polcu/Documents/Programming shits/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
set(VCPKG_MANIFEST_MODE ON CACHE BOOL "" FORCE)

project(EnetGameProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(unofficial-enet CONFIG REQUIRED)

# --- CONFIGURACIÓN DEL SERVIDOR ---
add_executable(GameServer src/server.cpp)
target_link_libraries(GameServer PRIVATE unofficial::enet::enet winmm wsock32 ws2_32)

# --- CONFIGURACIÓN DEL CLIENTE ---
add_executable(GameClient src/client.cpp)
target_link_libraries(GameClient PRIVATE unofficial::enet::enet winmm wsock32 ws2_32)