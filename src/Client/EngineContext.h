#pragma once

class InputSystem;
class NetworkSystem;
class RenderSystem;

struct EngineContext
{
	InputSystem* inputSystem;
	NetworkSystem* networkSystem;
	RenderSystem* renderSystem;
};