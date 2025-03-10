#include "framework/AssetManager.h"

namespace st {
    // Singelton class to manage assets in the game (textures, sounds, etc.)
    unique<AssetManager> AssetManager::assetManager{ nullptr };

    AssetManager::AssetManager()
        : mRootDirectory{ "" }
    {
    }

    AssetManager& AssetManager::Get()
    {
        if (!assetManager) {
            assetManager = unique<AssetManager>{ new AssetManager{} };
        }

        return *assetManager;
    }

    shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
    {
        // if the texture is already in the map, return it
        auto found = mLoadedTextureMap.find(path); // iterator to the texture in the map
        if (found != mLoadedTextureMap.end()) {
            return found->second;
        }

        // If the texture is not in the map: 
        // 1) Load it. 
        // 2) Add it to the map. 
        // 3) Than return it.
        shared<sf::Texture> newTexture{ new sf::Texture{} }; // create a new texture
        // if the texture is loaded successfully, add it to the map and then return it
        if (newTexture->loadFromFile(mRootDirectory + path)) {
            mLoadedTextureMap.insert({ path, newTexture });
            return newTexture;
        }

        // if the texture is not loaded successfully(path is wrong, etc.), return empty texture
        return shared<sf::Texture>{ nullptr };
    }

    void AssetManager::CleanCycle()
    {
        // remove all textures that are not used
        for (auto iter = mLoadedTextureMap.begin(); iter != mLoadedTextureMap.end();) {
            if (iter->second.unique()) {
                LOG("cleaning texture: %s", iter->first.c_str());
                iter = mLoadedTextureMap.erase(iter);
            } else {
                ++iter;
            }
        }
    }
    void AssetManager::SetAssetRootDirectory(const std::string& directory)
    {
        mRootDirectory = directory;
    }
}