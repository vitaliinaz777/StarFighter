
#include "config.h"
#include "framework/AssetManager.h"
#include "gameFramework/GameApplication.h"
#include "level/GameLevelOne.h"

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
        weak<GameLevelOne> newWorld = LoadWorld<GameLevelOne>();
    }
}