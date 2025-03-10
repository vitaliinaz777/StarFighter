#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace st
{
    // Forward declaration of classes to avoid circular dependency
    // Full definition is included where needed
    class Application;
    class Actor;

    class World {
    public:
        World(Application* owningApp);

        void BeginPlayInternal();
        void TickInternal(float deltaTime);
        void Render(sf::RenderWindow& window);

        virtual ~World(); // CPP program without virtual destructor 
        // causing undefined behavior.

        template<typename ActorType>
        weak<ActorType> SpawnActor();

        sf::Vector2u GetWindowSize() const;

    private:
        void BeginPlay();
        void Tick(float deltaTime);

        Application* mOwningApp; // pointer to the application which owns this world
        bool mBeganPaly;

        List<shared<Actor>> mActors; // list of actors in the world
        List<shared<Actor>> mPendingActors; // list of actors to be added to the world at the beginning of the frame tick
    };

    template<typename ActorType>
    weak<ActorType> World::SpawnActor()
    {
        shared<ActorType> newActor{ new ActorType{this} };
        mPendingActors.push_back(newActor);
        return newActor;
    }
}