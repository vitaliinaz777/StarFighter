#pragma once
#include <SFML/Graphics.hpp>

namespace st
{
    class Application{
    public:
        Application();
        void Run();
    private:
        sf::RenderWindow mWindow;
    };
}