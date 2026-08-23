#pragma once

#include <vector>
#include <memory>

enum class GameState;

struct EngineContext;
struct SDL_FRect;
struct TTF_Font;

class SDL_Window;
class SDL_Renderer;
class ScoreDisplay;

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();
		
	bool Init();
	GameState Update(const EngineContext& engineContext);

	void FillRenderObjects(const std::vector<float>& values); 
	void SetScoresToDraw(const std::vector<int>& scores);

private:
	void RenderObjectsToScreen();
	void DrawScores();

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

	std::vector<SDL_FRect> renderObjects;
	std::vector<int> oldScores { -1, -1 };

	std::vector<std::unique_ptr<ScoreDisplay>> scoreDisplays;
	TTF_Font* font = nullptr;
};