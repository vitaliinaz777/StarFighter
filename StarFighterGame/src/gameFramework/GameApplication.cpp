
#include "config.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/World.h"
#include "gameFramework/GameApplication.h"
#include "player/PlayerSpaceship.h"





st::Application* GetApplication()
{
    return new st::GameApplication{};
}

namespace st
{
    GameApplication::GameApplication()
        : Application{ 600, 980, "Star Fighter. Project Armada",
                        sf::Style::Titlebar | sf::Style::Close }
    {
        AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
        weak<World> newWorld = LoadWorld<World>();
        //newWorld.lock()->SpawnActor<Actor>();
        testPalyerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
        //testPalyerSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
        testPalyerSpaceship.lock()->SetActorLocation(sf::Vector2f{ 300.f, 490.f });
        testPalyerSpaceship.lock()->SetActorRotation(-90.f);
        //testPalyerSpaceship.lock()->SetVelocity(sf::Vector2f(0.f, -200.f));

        weak<Spaceship> testSpaceship = newWorld.lock()->SpawnActor<Spaceship>();
        testSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
        testSpaceship.lock()->SetActorLocation(sf::Vector2f(100.f, 50.f));

        counter = 0.f;
    }
    void GameApplication::Tick(float deltaTime)
    {
        counter += deltaTime;
        if (counter > 10.f) {
            if (!testPalyerSpaceship.expired()) {
                testPalyerSpaceship.lock()->Destroy();
            }
        }


        //counter += deltaTime;
        //if (counter > 0.5f)
        //{
        //    actorToDestroy.lock()->AddActorRotationOffset(5.f);

        //    LOG("Angle: %i, cos: %f, sin: %f",
        //        static_cast <int>(actorToDestroy.lock()->GetActorRotation()),
        //        actorToDestroy.lock()->GetActorForwardDirection().x,
        //        actorToDestroy.lock()->GetActorForwardDirection().y);

        //    counter = 0.f;
        //    //if (!actorToDestroy.expired()) {
        //    //    actorToDestroy.lock()->Destroy();
        //    //}
        //}

        ////LOG("GameApplication tick");
    }
}