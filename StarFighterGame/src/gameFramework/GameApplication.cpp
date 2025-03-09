#include "gameFramework/GameApplication.h"
#include "framework/World.h"

st::Application* GetApplication()
{
	return new st::GameApplication{};
}

namespace st
{
	GameApplication::GameApplication()
	{
		LoadWorld<World>();
	}
}