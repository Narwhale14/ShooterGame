/**
 * @file Apple.h
 * @author Will and Niall
 * @brief 
 * @version 0.1
 * @date 2024-11-26
 */

#ifndef APPLE_H
#define APPLE_H

#include "../GameManager/Button.h"

class Apple : public Object{
    public:
        Apple(sf::Texture &texture);
        void setPosition(const sf::Vector2f &pos);
        void rotateToMouse(const sf::Vector2f& mousePos);

        sf::Vector2f getPosition() const;

        virtual void render(sf::RenderTarget &target);
    private:
};

#endif