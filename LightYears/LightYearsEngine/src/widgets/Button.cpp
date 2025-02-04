#include "widgets/Button.h"
#include"framework/AssetManager.h"

namespace ly
{
    Button::Button(const std::string &textString, const std::string &buttonTexturePath)
        : mButtonTexture{AssetManager::Get().LoadTexture(buttonTexturePath)},
        mButtonSprite{*(mButtonTexture.get())},
        mButtonFont{AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf")},
        mButtonText{textString, *(mButtonFont.get())},
        mButtonDefaultColor{128, 128, 128, 255},
        mButtonDownColor{64, 64, 64, 255},
        mButtonHoverColor{190, 190, 190, 255},
        mIsButtonDown{false}
    {
        mButtonSprite.setColor(mButtonDefaultColor);
        CenterText();
    }

    sf::FloatRect Button::GetBound() const
    {
        return mButtonSprite.getGlobalBounds();
    }

    void Button::SetTextString(const std::string &newStr)
    {
        mButtonText.setString(newStr);
        CenterText();
    }

    void Button::SetTextCharacterSize(unsigned int characterSize)
    {
        mButtonText.setCharacterSize(characterSize);
        CenterText();
    }

    bool Button::HandleEvent(const sf::Event &event)
    {
        bool handled = false;
        if(event.type == sf::Event::MouseButtonReleased)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                if(mButtonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && mIsButtonDown)
                {
                    onButtonClicked.Broadcast();
                }
            }
            ButtonUp();
            handled = true;
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if(mButtonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            {
                ButtonDown();
                handled = true;
            }
        }
        else if(event.type == sf::Event::MouseMoved)
        {
            if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(mButtonSprite.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                {
                    MouseHovered();
                }
                else
                {
                    ButtonUp();
                }
                handled = true;
            }
        }
        return handled || Widget::HandleEvent(event);
    }

    void Button::Draw(sf::RenderWindow &windowRef)
    {
        windowRef.draw(mButtonSprite);
        windowRef.draw(mButtonText);
    }

    void Button::LocationUpdated(const sf::Vector2f &location)
    {
        mButtonSprite.setPosition(location);
        CenterText();
    }

    void Button::RotationUpdated(float rotation)
    {
        mButtonSprite.setRotation(rotation);
        mButtonText.setRotation(rotation);
    }

    void Button::CenterText()
    {
        sf::Vector2f widgetCenter = GetCenterPosition();
        sf::FloatRect textBound = mButtonText.getGlobalBounds();
        mButtonText.setPosition(widgetCenter - sf::Vector2f(textBound.width/2.f , textBound.height));
    }

    void Button::ButtonUp()
    {
        mIsButtonDown = false;
        mButtonSprite.setColor(mButtonDefaultColor);
    }

    void Button::ButtonDown()
    {
        mIsButtonDown = true;
        mButtonSprite.setColor(mButtonDownColor);
    }

    void Button::MouseHovered()
    {
        mButtonSprite.setColor(mButtonHoverColor);
    }
}