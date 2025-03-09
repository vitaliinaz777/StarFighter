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
        actorToDestory = testWorld.lock()->SpawnActor<Actor>();
        counter = 0;
    }

    void GameApplication::Tick(float deltaTime)
    {
        counter += deltaTime;
        if (counter > 2.f)
        {
            if (!actorToDestory.expired())
            {
                actorToDestory.lock()->Destory();
            }
        }
	}
}