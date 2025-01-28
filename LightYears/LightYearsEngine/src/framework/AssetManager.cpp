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
        if(newTexture->loadFromFile(mrootDirectory + path))//Loading new texture from path
        {
            mLoadedextureMap.insert({path,newTexture});
            return newTexture;
        }

        return shared<sf::Texture> {nullptr};//Invalid Path
    }

    void AssetManager::CleanCycle()// Delete a loaded texture if not used by anyone except asset manager
    {
        for(auto iter = mLoadedextureMap.begin();iter!=mLoadedextureMap.end();)
        {
            if(iter->second.unique())
            {
                // LOG("Cleaning texture: %s", iter->first.c_str());
                iter = mLoadedextureMap.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }
    AssetManager::AssetManager():mrootDirectory{}
    {

    }

    void AssetManager::SetAssetRootDirectory(const std::string &directoy)
    {
        mrootDirectory = directoy;
    }  
}