#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/PhysicsSystem.h"


namespace st
{
    Application::Application(unsigned int windowWidth, unsigned int windowHeight,
                             const std::string& title, sf::Uint32 style)
        : mWindow{ sf::VideoMode(windowWidth, windowHeight), title, style },
        mTargetFrameRate(60.f),
        mTickClock{},
        currentWorld{ nullptr },
        mCleanCycleClock{},
        mClaenCycleInterval{ 2.f }
    {
    }

    void Application::Run()
    {
        mTickClock.restart();
        float accumulatedTime = 0.f;
        float targetDeltaTime = 1.f / mTargetFrameRate;

        // Game loop
        while (mWindow.isOpen())
        {
            // Event processing
            sf::Event windowEvent;
            while (mWindow.pollEvent(windowEvent))
            {
                // Request for closing the window
                if (windowEvent.type == sf::Event::EventType::Closed) {
                    mWindow.close();
                }
            }

            float frameDeltaTime = mTickClock.restart().asSeconds();
            accumulatedTime += frameDeltaTime;
            while (accumulatedTime >= targetDeltaTime)
            {
                accumulatedTime -= targetDeltaTime;
                TickInternal(targetDeltaTime);
                RenderInternal();
            }
            //LOG("ticking at framerate: %f", 1.f / frameDeltaTime);
        }
    }

    sf::Vector2u Application::GetWindowSize() const
    {
        return mWindow.getSize();
    }

    void Application::TickInternal(float deltaTime) {
        Tick(deltaTime);

        // Update World (if there is a world loaded)
        if (currentWorld) {
            currentWorld->TickInternal(deltaTime);
        }

        // Update Physics
        PhysicsSystem::Get().Step(deltaTime); 

        // Clean Cycle
        if (mCleanCycleClock.getElapsedTime().asSeconds() >= mClaenCycleInterval) {
            mCleanCycleClock.restart();

            // Clean unused textures
            AssetManager::Get().CleanCycle(); 

            // Clean objects pending to destroy
            if (currentWorld) {
                currentWorld->CleanCycle();
            }
        }
    }

    void Application::RenderInternal() {
        mWindow.clear();

        Render();

        mWindow.display();
    }

    void Application::Render()
    {
        if (currentWorld) {
            currentWorld->Render(mWindow);
        }
    }
    void Application::Tick(float deltaTime)
    {
        //LOG("Application tick");
    }
}
