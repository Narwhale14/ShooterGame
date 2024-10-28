#include "../Resource/Mortar.h"

Mortar::Mortar(float r, sf::Texture* texture){
    range=r;

    this->createSprite(texture);
}

void Mortar::fire(sf::Vector2f mLoc)
{
    this->sprite->setPosition(mLoc);
}