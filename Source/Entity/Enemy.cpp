/**
 * @file Enemy.cpp
 * @author Niall Murray
 * @brief Enemy class intialization
 * @date 2024-10-29
 */

#include "../../Resource/Entity/Enemy.h"

Enemy::Enemy(std::map<std::string, sf::Texture>& textures, int x, int y) {
    srand(time(0));

    switch(generateEnemyType()) {
        case 0:
            createSprite(&textures["ENEMY_WOLF"], 0.4f);
            movementSpeed = 300;
            xpValue = 15;
            break;
        case 1:
            createSprite(&textures["ENEMY_BULL"], 0.4f);
            movementSpeed = 200;
            xpValue = 10;
            break;
        default:
            exit(1);
    }

    setPosition(sf::Vector2f(x, y));

    createHitbox(sprite, 0.f, 0.f, sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2, sf::Color::Red);
    createHealthBar(hitbox->getGlobalBounds().width, hitbox->getGlobalBounds().height, sprite->getPosition().x, sprite->getPosition().y);
}

Enemy::~Enemy() {

}

int Enemy::getXPValue() const {
    return xpValue;
}

short unsigned Enemy::generateEnemyType() {
    int value = (rand() % 100) + 1;

    if(value <= 20)
        return wolf;
    else
        return bull;
}

void Enemy::trackToPlayer(sf::Vector2f playerPosition) {
    float dist_x = playerPosition.x - sprite->getPosition().x;
    float dist_y = playerPosition.y - sprite->getPosition().y;

    angle = ((atan2(dist_y, dist_x)) * 180 / 3.14);
    
    sprite->setRotation(angle - 90);
}

void Enemy::followPlayer(const float& dt, sf::Vector2f playerPosition) {
    move(dt, cos(angle * 3.14 / 180), sin(angle * 3.14 / 180));
}

void Enemy::render(sf::RenderTarget& target) {
    if(healthBar)
        healthBar->render(target);

    if(sprite)
        target.draw(*sprite);

    if(hitbox)
        hitbox->render(target);
}

void Enemy::update() {
    healthBar->setPosition(hitbox->getPosition().x, hitbox->getPosition().y + (hitbox->getGlobalBounds().height));
    hitbox->update();
}