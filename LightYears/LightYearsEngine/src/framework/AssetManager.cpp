#include"framework/AssetManager.h"

namespace ly
{
    unique<AssetManager> AssetManager :: assetManager{nullptr};
    AssetManager &AssetManager::Get()
    {
        if(!assetManager)
        {
            assetManager = std::move(unique<AssetManager>{new AssetManager});
        }
        return *assetManager;
    }
    shared<sf::Texture> AssetManager::LoadTexture(const std::string &path)
    {
        auto found = mLoadedextureMap.find(path);
        if(found != mLoadedextureMap.end())//Texture already loaded
        {
            return found->second;
        }

        shared<sf::Texture> newTexture {new sf::Texture};
        if(newTexture->loadFromFile(path))//Loading new texture from path
        {
            mLoadedextureMap.insert({path,newTexture});
            return newTexture;
        }

        return shared<sf::Texture> {nullptr};//Invalid Path
    }
    AssetManager::AssetManager()
    {

    }
}