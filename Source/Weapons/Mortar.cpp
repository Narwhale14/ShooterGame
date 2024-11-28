/**
 * @file Mortar.cpp
 * @author William Wotherspoon
 * @brief single shot pistol class definitions
 * @version 0.1
 * @date 2024-8-29
 */
#include "../../Resource/Weapons/Mortar.h"

Mortar::Mortar(float r, sf::Texture* texture){
    range=r;

    //createSprite(texture, 1);
}

Mortar::~Mortar() {

}

void Mortar::fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
{
    //sprite->setPosition(mouseLoc);
    //firing = true;
}