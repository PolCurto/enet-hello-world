#include "RenderSystem.h"

#include <iostream>
#include <SDL3/SDL.h>

#include "GameState.h"

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

bool RenderSystem::Init()
{
    if (!SDL_CreateWindowAndRenderer("My Game", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return false;
    }

    SDL_Log("Window and renderer created successfully.");
    return true;
}

GameState RenderSystem::Update(const EngineContext& engineContext)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    return GameState::Update;
}