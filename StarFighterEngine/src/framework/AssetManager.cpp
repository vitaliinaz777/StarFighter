#include "framework/AssetManager.h"

namespace st
{
	unique<AssetManager> AssetManager::assetManager{ nullptr };

	AssetManager& AssetManager::Get()
	{
		if (!assetManager)
		{
			assetManager = unique<AssetManager>{ new AssetManager };
		}

		return *assetManager;
	}

	shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{
		auto found = mLoadedTextureMap.find(path);
		if (found != mLoadedTextureMap.end())
		{
			return found->second;
		}

		shared<sf::Texture> newTexture{ new sf::Texture };
		if (newTexture->loadFromFile(path))
		{
			mLoadedTextureMap.insert({ path, newTexture });
			return newTexture;
		}

		return shared<sf::Texture> {nullptr};
	}

	void AssetManager::CleanCycle()
	{
		for (auto iter = mLoadedTextureMap.begin(); iter != mLoadedTextureMap.end();)
		{
			if (iter->second.unique())
			{
				LOG("cleaning texture: %s", iter->first.c_str());
				iter = mLoadedTextureMap.erase(iter);
			} else
			{
				++iter;
			}
		}
	}

	AssetManager::AssetManager()
	{

	}
}