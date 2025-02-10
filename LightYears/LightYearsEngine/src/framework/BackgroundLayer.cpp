#include"framework/BackgroundLayer.h"

namespace ly
{
    BackgroundLayer::BackgroundLayer(World *owningWorld, const List<std::string> &assetPaths, const sf::Vector2f &minVelocity, const sf::Vector2f &maxVelocity, float sizeMin, float sizeMax, int spriteCount, const sf::Color &colorTint)
        : Actor{owningWorld},
        mMinVelocity{minVelocity},
        mMaxVelocity{maxVelocity},
        mSizeMin{sizeMin},
        mSizeMax{sizeMax},
        mSpriteCount{spriteCount},
        mTintColor{colorTint}
    {
        SetEnablePhysics(false);
    }
}