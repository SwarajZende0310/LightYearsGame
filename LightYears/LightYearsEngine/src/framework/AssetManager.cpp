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
        auto found = mLoadedTextureMap.find(path);
        if(found != mLoadedTextureMap.end())//Texture already loaded
        {
            return found->second;
        }

        shared<sf::Texture> newTexture {new sf::Texture};
        if(newTexture->loadFromFile(mrootDirectory + path))//Loading new texture from path
        {
            mLoadedTextureMap.insert({path,newTexture});
            return newTexture;
        }

        return shared<sf::Texture> {nullptr};//Invalid Path
    }

    shared<sf::Font> AssetManager::LoadFont(const std::string &path)
    {
        auto found = mLoadedFontMap.find(path);
        if(found != mLoadedFontMap.end())//Font already loaded
        {
            return found->second;
        }

        shared<sf::Font> newFont {new sf::Font};
        if(newFont->loadFromFile(mrootDirectory + path))//Loading new Font from path
        {
            mLoadedFontMap.insert({path,newFont});
            return newFont;
        }

        return shared<sf::Font> {nullptr};//Invalid Path
    }

    void AssetManager::CleanCycle() // Delete a loaded texture if not used by anyone except asset manager
    {
        for(auto iter = mLoadedTextureMap.begin();iter!=mLoadedTextureMap.end();)
        {
            if(iter->second.unique())
            {
                // LOG("Cleaning texture: %s", iter->first.c_str());
                iter = mLoadedTextureMap.erase(iter);
            }
            else
            {
                ++iter;
            }
        }

        for(auto iter = mLoadedFontMap.begin();iter!=mLoadedFontMap.end();)
        {
            if(iter->second.unique())
            {
                // LOG("Cleaning texture: %s", iter->first.c_str());
                iter = mLoadedFontMap.erase(iter);
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