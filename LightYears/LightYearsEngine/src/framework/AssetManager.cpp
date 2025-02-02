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
        return LoadAsset(path, mLoadedTextureMap);
    }

    shared<sf::Font> AssetManager::LoadFont(const std::string &path)
    {
        return LoadAsset(path, mLoadedFontMap);
    }

    void AssetManager::CleanCycle() // Delete a loaded texture if not used by anyone except asset manager
    {
        CleanUniqueRef(mLoadedTextureMap);
        CleanUniqueRef(mLoadedFontMap);
    }
    AssetManager::AssetManager():mrootDirectory{}
    {

    }

    void AssetManager::SetAssetRootDirectory(const std::string &directoy)
    {
        mrootDirectory = directoy;
    }  
}