#pragma once

#include"widgets/Widget.h"
#include"framework/Delegate.h"

namespace ly
{
    struct ButtonColor
    {
        sf::Color buttonDefaultColor;
        sf::Color buttonDownColor;
        sf::Color buttonHoverColor;
    };

    class Button : public Widget
    {
        public:
            Button(const std::string& textString = "Button", const std::string& buttonTexturePath = "SpaceShooterRedux/PNG/UI/buttonBlue.png");

            virtual sf::FloatRect GetBound() const;
            void SetTextString(const std::string& newStr);
            std::string GetTextString()const;
            void SetColor(const ButtonColor& newColor);
            void SetTextSize(unsigned int characterSize);
            virtual bool HandleEvent(const sf::Event& event)override;
            Delegate<> onButtonClicked;
        private:
            virtual void Draw(sf::RenderWindow& windowRef)override;
            virtual void LocationUpdated(const sf::Vector2f& location)override;
            virtual void RotationUpdated(float rotation)override;
            
            void CenterText();

            shared<sf::Texture> mButtonTexture;
            sf::Sprite mButtonSprite;
            
            shared<sf::Font> mButtonFont;
            sf::Text mButtonText;

            ButtonColor mButtonColor;

            bool mIsButtonDown;

            void ButtonUp();
            void ButtonDown();
            void MouseHovered();
    };
}