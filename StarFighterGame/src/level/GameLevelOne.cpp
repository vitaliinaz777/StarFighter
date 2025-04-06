#include "enemy/TwinBlade.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/Vanguard.h"
#include "enemy/VanguardStage.h"
#include "gameplay/GameStage.h"
#include "level/GameLevelOne.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include "framework/World.h"
#include "player/PlayerSpaceship.h"



namespace st
{
    GameLevelOne::GameLevelOne(Application* owningApp)
        : World(owningApp)
    {
        //newWorld.lock()->SpawnActor<Actor>();
        testPalyerSpaceship = SpawnActor<PlayerSpaceship>();
        //testPalyerSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
        testPalyerSpaceship.lock()->SetActorLocation(sf::Vector2f{ 300.f, 490.f });
        testPalyerSpaceship.lock()->SetActorRotation(-90.f);
        //testPalyerSpaceship.lock()->SetVelocity(sf::Vector2f(0.f, -200.f));

        //weak<Vanguard> testVanguard = SpawnActor<Vanguard>();
        //testVanguard.lock()->SetActorLocation(sf::Vector2f(100.f, 50.f));
        //testVanguard.lock()->SetTeamID(2);

        //weak<Spaceship> testSpaceship = SpawnActor<Spaceship>();
        //testSpaceship.lock()->SetActorLocation(sf::Vector2f(400.f, 50.f));
        //testSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
        //testSpaceship.lock()->SetTeamID(2);
    }

    void GameLevelOne::BeginPlay()
    {
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<VanguardStage>{new VanguardStage{this}});
        AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});
    }
}