#pragma once

#include <vector>

enum class GameState;

struct EngineContext;
struct SDL_FRect;

class SDL_Window;
class SDL_Renderer;

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();
		
	bool Init();
	GameState Update(const EngineContext& engineContext);

	void FillRenderObjects(const std::vector<float>& values); 
	void RenderObjectsToScreen();
	void SetScores(const std::vector<int>& scores);

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

	std::vector<SDL_FRect> renderObjects;
};