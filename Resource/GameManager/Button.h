#ifndef BUTTON_H
#define BUTTON_H

#include "../Entity/Enemy.h"

class Button {
    public:
        Button(sf::Font& font, std::string s, sf::Vector2f size, sf::Color idle, sf::Color hover, sf::Color active);
        Button(sf::Vector2f size, sf::Color hover, sf::Color active, sf::Texture* texture);
        ~Button();

        void setPosition(sf::Vector2f position);

        short unsigned getState();
        sf::Vector2f getSize() const;

        void update(const sf::Vector2f& mousePosition);
        void render(sf::RenderTarget& target);

    private:
        sf::RectangleShape button;
        sf::Sprite* sprite;

        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;

        sf::Text text;
        sf::Font font;

        short unsigned state;
        enum state {idle = 0, hovered, clicked};
};

#endif