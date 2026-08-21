#pragma once

#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class ScoreDisplay 
{
private:
    int currentValue = -1;
    SDL_Texture* scoreTexture = nullptr;
    SDL_FRect renderQuad = { 0, 0, 0, 0 };
    TTF_Font* font = nullptr;
    float x = 0.0f;
    float y = 100.0f;

public:
    ScoreDisplay(TTF_Font* f, int id) : font(f) 
    {
        x = 50.0f + id * 200.0f;
    }
    ~ScoreDisplay() 
    {
        if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    }

    void UpdateNumber(SDL_Renderer* renderer, int newValue) 
    {
        if (newValue == currentValue) return;

        if (!font || !renderer) return;

        currentValue = newValue;

        if (scoreTexture) SDL_DestroyTexture(scoreTexture);

        std::string text = std::to_string(currentValue);
        SDL_Color white = { 255, 255, 255, 255 };
        
        SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), 0, white);
        if (!surface) return;

        scoreTexture = SDL_CreateTextureFromSurface(renderer, surface);
        
        renderQuad = { x, y, (float)surface->w, (float)surface->h };
        SDL_DestroySurface(surface);
    }

    void Render(SDL_Renderer* renderer) 
    {
        if (scoreTexture) 
        {
            SDL_RenderTexture(renderer, scoreTexture, NULL, &renderQuad);
        }
    }
};