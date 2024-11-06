#ifndef BUTTON_H
#define BUTTON_H

#include "../Entity/Enemy.h"

class Button: public sf::Drawable {
    public:
        Button(sf::Texture& texture, sf::Font& font, std::string s, sf::Vector2f size);
        ~Button() { };

        void setPosition(sf::Vector2f position);
        void setSize(sf::Vector2f size);
        void setColor(sf::Color btnColor);

        void setText(std::string s);
        void setColorTextNormal(sf::Color textNormalColor) { mTextNormal = textNormalColor; };
        void setColorTextHover(sf::Color textHoverColor) { mTextHover = textHoverColor; };

        sf::Vector2f getPosition() { return mPosition; };
        sf::Vector2f getDimensions() { return sf::Vector2f(mButton.getGlobalBounds().width, mButton.getGlobalBounds().height); };
        sf::Uint32 getState() { return mBtnState; };

        void initializeButton();
        void initializeText();

        void update(sf::Event& e, sf::RenderWindow& window);
        virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;

    private:
        sf::Sprite mButton;
        sf::Texture mTexture;

        sf::Color mButtonColor;
        sf::Vector2f mPosition;
        sf::Vector2f mSize;
        sf::Uint32 mBtnState;

        std::string mPhrase;

        sf::Text mText;
        sf::Font mFont;
        sf::Color mTextNormal;
        sf::Color mTextHover;

        enum state {normal, hovered, clicked};
};

#endif