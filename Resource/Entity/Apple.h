/**
 * @file Apple.h
 * @author William Wotherspoon
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
        sf::Vector2f getPosition() const;
        void render(sf::RenderTarget &target);
    private:
};



#endif