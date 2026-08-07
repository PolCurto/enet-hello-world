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

    SDL_RenderRect(renderer, nullptr);

    RenderObjectsToScreen();

    SDL_RenderPresent(renderer);

    return GameState::Update;
}

void RenderSystem::RenderObjectsToScreen()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for (const SDL_FRect& rect : renderObjects)
    {
        SDL_RenderFillRect(renderer, &rect);
    }
}

void RenderSystem::FillRenderObjects(const std::vector<float>& values)
{
    renderObjects.clear();
    for (int i = 0; i < values.size(); i = i + 4)
    {
        SDL_FRect rect;
        rect.x = values[i];
        rect.y = values[i + 1];
        rect.w = values[i + 2];
        rect.h = values[i + 3];
        renderObjects.push_back(rect);
    }
}