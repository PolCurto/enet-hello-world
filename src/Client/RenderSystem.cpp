#include "RenderSystem.h"

#include <iostream>
#include <SDL3/SDL.h>
#include <string>

#include "GameState.h"
#include "ScoreDisplay.h"

constexpr int CHAR_WIDTH = 16;
constexpr int CHAR_HEIGHT = 24;

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
    if (font) 
    {
        TTF_CloseFont(font);
    }
}

bool RenderSystem::Init()
{
    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize SDL_ttf: %s", SDL_GetError());
        return false;
    }

    if (!SDL_CreateWindowAndRenderer("My Game", 800, 600, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return false;
    }

    SDL_Log("Window and renderer created successfully.");

    font = TTF_OpenFont("assets/Tenada.ttf", 32);
    if (!font) 
    {
        SDL_Log("Couldn't load font: %s", SDL_GetError());
        return false;
    }
    const std::vector<int> initialScores = { 0, 0 };
    SetScoresToDraw(initialScores);
    return true;
}

GameState RenderSystem::Update(const EngineContext& engineContext)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderRect(renderer, nullptr);

    DrawScores();
    RenderObjectsToScreen();

    SDL_RenderPresent(renderer);

    return GameState::Update;
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

void RenderSystem::SetScoresToDraw(const std::vector<int>& scores)
{
    if (scores.size() > scoreDisplays.size())
    {
        for (int i = scoreDisplays.size(); i < scores.size(); ++i)
        {
            scoreDisplays.push_back(std::make_unique<ScoreDisplay>(font, i));
        }
    }

    if (scores.size() != oldScores.size())
    {
        oldScores.resize(scores.size());
    }
    
    for (int i = 0; i < scores.size(); ++i)
    {
        if (scores[i] != oldScores[i])
        {
            std::cout << "Score from player " << i << ". Current score: " << scores[i] << std::endl;
            scoreDisplays[i]->UpdateNumber(renderer, scores[i]);
        }
    }

    oldScores = scores; 
}

void RenderSystem::RenderObjectsToScreen()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for (const SDL_FRect& rect : renderObjects)
    {
        SDL_RenderFillRect(renderer, &rect);
    }
}

void RenderSystem::DrawScores()
{
    for (const auto& display : scoreDisplays)
    {
        display->Render(renderer);
    }
}