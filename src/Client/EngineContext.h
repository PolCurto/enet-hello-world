#pragma once

class InputSystem;
class NetworkSystem;

struct EngineContext
{
	InputSystem* inputSystem;
	NetworkSystem* networkSystem;
};