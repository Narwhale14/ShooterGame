#include "../Resource/Mortar.h"

Mortar::Mortar(float r, sf::Texture* texture){
    range=r;

    createSprite(texture);
}

Mortar::~Mortar() {

}

void Mortar::fire(sf::Vector2f mLoc)
{
    sprite->setPosition(mLoc);
    firing = true;
}