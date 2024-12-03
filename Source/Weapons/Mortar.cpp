/**
 * @file Mortar.cpp
 * @author William Wotherspoon
 * @brief fun relic from the games beginning
 * @version 0.1
 * @date 2024-8-29
 */
#include "../../Resource/Weapons/Mortar.h"

/**
 * @brief Construct a new Mortar:: Mortar object
 * 
 * @param r 
 * @param texture 
 */
Mortar::Mortar(float r, sf::Texture* texture){
    range=r;

    //createSprite(texture, 1);
}

/**
 * @brief does not do anything anymore used to fire the mortar where the mouse was
 * 
 * @param mouseLoc 
 * @param playerLoc 
 */
void Mortar::fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
{
    //sprite->setPosition(mouseLoc);
    //firing = true;
}