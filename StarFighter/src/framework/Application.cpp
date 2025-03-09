#include "framework/Application.h"

namespace st
{
	Application::Application()
		: mWindow{ sf::VideoMode(1024, 1024), "Star Fighter" }
	{
	}
	void Application::Run(){
		while (mWindow.isOpen()){
			sf::Event windowEvent;
			while (mWindow.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
				{
					mWindow.close();
				}
			}
		}
	}
}