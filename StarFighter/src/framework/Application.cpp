#include <iostream>
#include "framework/Application.h"

namespace st
{
	Application::Application()
		: mWindow{ sf::VideoMode(1024, 1024), "Star Fighter.Project \"Armada\"" },
		mTargetFrameRate{ 30.f },
		mTickClock{}
	{

	}

	void Application::Run()
	{
		mTickClock.restart();
		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / mTargetFrameRate;
		while (mWindow.isOpen())
		{
			sf::Event windowEvent;
			while (mWindow.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
				{
					mWindow.close();
				}
			}
			float frameDeltaTime = mTickClock.restart().asSeconds();
			accumulatedTime += frameDeltaTime;
			while (accumulatedTime > targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;
				TickInternal(targetDeltaTime);
				RenderInternal();
			}
			std::cout << "ticking at framerate: " << 1.f / frameDeltaTime << std::endl;
		}
	}

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
	}

	void Application::RenderInternal()
	{
		mWindow.clear();

		Render();

		mWindow.display();
	}

	void Application::Render()
	{
		sf::RectangleShape rect{ sf::Vector2f(100.f, 100.f) };
		rect.setFillColor(sf::Color::Red);
		rect.setOrigin(100, 100);
		rect.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);

		mWindow.draw(rect);
	}

	void Application::Tick(float deltaTime)
	{
	}
}