#pragma once

enum class GameState;
struct EngineContext;
class SDL_Window;
class SDL_Renderer;

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();
		
	 bool Init();
	 GameState Update(const EngineContext& engineContext);

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};