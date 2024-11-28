/**
 * @file Apple.cpp
 * @author Will and Niall
 * @brief 
 * @version 0.1
 * @date 2024-11-26
 */

#include "../../Resource/Entity/Apple.h"

/**
 * @brief Construct a new Apple:: Apple object simply for displaying
 * 
 * @param texture 
 */
Apple::Apple(sf::Texture &texture)
{
    createSprite(&texture, 0.1f);
}

/**
 * @brief used to set where the apple inventory item should display
 * 
 * @param position 
 */
void Apple::setPosition(const sf::Vector2f &position)
{
    sprite->setPosition(position);
}

/**
 * @brief retrieve the location of the apple inventory item
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Apple::getPosition() const
{
    return sprite->getPosition();
}

/**
 * @brief Rotates apple to mouse
 * 
 * @param mousePos 
 */
void Apple::rotateToMouse(const sf::Vector2f& mousePos) {
    float dist_x = mousePos.x - sprite->getPosition().x;
    float dist_y = mousePos.y - sprite->getPosition().y;

    int angle = (atan2(dist_y, dist_x)) * 180 / 3.14;
    sprite->setRotation(angle);
}

/**
 * @brief draws the apple inventory item to the screen if the texture is set
 * 
 * @param target 
 */
void Apple::render(sf::RenderTarget &target) {
    if(sprite)
        target.draw(*sprite);
}
