#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/World.h"

namespace st
{
    class World; // forward declaration

    class Application
    {
    public:
        Application(unsigned int windowWidth, unsigned int windowHeight,
                    const std::string& title, sf::Uint32 style);
        void Run();

        // template function to load different worlds
        template<typename WorldType>
        weak<WorldType> LoadWorld();

        sf::Vector2u GetWindowSize() const;

    private:
        void TickInternal(float deltaTime);
        void RenderInternal();

        virtual void Tick(float deltaTime);
        virtual void Render();

        sf::RenderWindow mWindow;
        float mTargetFrameRate;
        sf::Clock mTickClock; // used to measure time between frames

        shared<World> currentWorld;

        sf::Clock mCleanCycleClock;
        float mClaenCycleInterval;
    };

    // template implementation must be in the header file!
    template<typename WorldType>
    weak<WorldType> Application::LoadWorld()
    {
        shared<WorldType> newWorld{ new WorldType{this} };
        currentWorld = newWorld;
        currentWorld->BeginPlayInternal();
        return newWorld;
    }
}