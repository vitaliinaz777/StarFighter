#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

st::Application* GetApplication()
{
	return new st::GameApplication{};
}

namespace st
{
	GameApplication::GameApplication()
	{
		weak<World> testWorld = LoadWorld<World>();
		testWorld.lock()->SpawnActor<Actor>();
		testWorld.lock()->SpawnActor<Actor>();
		testWorld.lock()->SpawnActor<Actor>();

	}
}