#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "config.h"

st::Application* GetApplication()
{
	return new st::GameApplication{};
}

namespace st
{
	GameApplication::GameApplication()
		: Application{ 600, 980, "Star Fighter. Project \"Armada\"" , sf::Style::Titlebar | sf::Style::Close }
	{
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();
		actorToDestory = newWorld.lock()->SpawnActor<Actor>();
		actorToDestory.lock()->SetTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerShip1_blue.png");
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