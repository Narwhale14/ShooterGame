/**
 * @file Enemy.cpp
 * @author Niall Murray
 * @brief Enemy class intialization
 * @date 2024-10-29
 */

#include "../../Resource/Entity/Enemy.h"

Enemy::Enemy(std::map<std::string, sf::Texture>& textures, int x, int y, float s) {
    setType(enemy);
    createSprite(&textures["PLAYER_NORMAL"], s);
    setPosition(sf::Vector2f(x, y));

    createHitbox(sprite, 0.f, 0.f, sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2, sf::Color::Green);
    createHealthBar(50, 50, sprite->getPosition().x, sprite->getPosition().y);
}

Enemy::~Enemy() {

}

void Enemy::render(sf::RenderTarget& target) {
    if(healthBar)
        healthBar->render(target);

    if(hitbox)
        hitbox->render(target);

    if(sprite)
        target.draw(*sprite);
}

void Enemy::update() {
    healthBar->setPosition(hitbox->getPosition().x, hitbox->getPosition().y + (hitbox->getGlobalBounds().height));
    hitbox->update();
}