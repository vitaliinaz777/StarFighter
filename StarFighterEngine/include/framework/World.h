#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/Object.h"

namespace st
{
    // Forward declaration of classes to avoid circular dependency
    // Full definition is included where needed
    class Actor;
    class Application;
    class GameStage;

    class World : public Object
    {
    public:
        World(Application* owningApp);

        void BeginPlayInternal();
        void TickInternal(float deltaTime);
        void Render(sf::RenderWindow& window);

        virtual ~World(); // CPP program without virtual destructor 
        // causing undefined behavior.

        // variadic tamplate parameters
        template<typename ActorType, typename... Args>
        weak<ActorType> SpawnActor(Args... args);

        sf::Vector2u GetWindowSize() const;
        void CleanCycle();

        void AddStage(const shared<GameStage>& newStage);

    private:
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);

        Application* mOwningApp; // pointer to the application which owns this world
        bool mBeganPaly;

        List<shared<Actor>> mActors; // list of actors in the world
        List<shared<Actor>> mPendingActors; // list of actors to be added to the world at the beginning of the frame tick
        
        virtual void InitGameStages();
        virtual void AllGameStageFinished();
        void NextGameStage();
        void StartStages();

        // 'GameStage' which is implementing 'Object' should be stored as shared pointer in List,
        // to be able to get a weak reference through function in 'Object' class:
        // weak<Object> Object::GetWeakRef()
        List<shared<GameStage>> mGameStages;
        List<shared<GameStage>>::iterator mCurrentStageIter;

    };

    // variadic tamplate parameters
    template<typename ActorType, typename... Args>
    weak<ActorType> World::SpawnActor(Args... args)
    {
        shared<ActorType> newActor{ new ActorType(this, args...) };
        mPendingActors.push_back(newActor);
        return newActor;
    }
}