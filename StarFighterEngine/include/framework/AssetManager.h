#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace st {
    // Singelton class to manage assets in the game (textures, sounds, etc.)
    class AssetManager {
    public:
        static AssetManager& Get(); // return link to AssetManager
        shared<sf::Texture> LoadTexture(const std::string& path);
        void CleanCycle();
        void SetAssetRootDirectory(const std::string& directory);
    protected:
        AssetManager();
    private:
        static unique<AssetManager> assetManager;
        Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
        std::string mRootDirectory;
    };
}