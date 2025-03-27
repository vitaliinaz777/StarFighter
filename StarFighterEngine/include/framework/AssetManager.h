#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace st 
{
    // Singelton class. Manages assets in the game (textures, sounds, etc.)
    class AssetManager 
    {
    public:
        static AssetManager& Get();
        shared<sf::Texture> LoadTexture(const std::string& path);
        void CleanCycle();
        void SetAssetRootDirectory(const std::string& directory);
    
    protected:
        // Constructor is protected to ensure AssetManager is instantiated only within the class itself using method Get()
        AssetManager();  
    
    private:
        static unique<AssetManager> assetManager;
        Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
        std::string mRootDirectory;
    };
}