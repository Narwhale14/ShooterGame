/**
 * @file Enemy.cpp
 * @author Niall Murray
 * @brief Enemy class intialization
 * @date 2024-10-29
 */

#include "../../Resource/Entity/Enemy.h"

/**
 * @brief Construct a new Enemy:: Enemy object
 * 
 * @param textures 
 * @param x 
 * @param y 
 */
Enemy::Enemy(std::map<std::string, sf::Texture>& textures, int x, int y) {
    srand(time(0));

    type = generateEnemyType();
    switch(type) {
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

    sightDistance = 8;
}

/**
 * @brief Destroy the Enemy:: Enemy object
 * 
 */
Enemy::~Enemy() {

}

/**
 * @brief Gets the enemy's xp value for the player's level bar
 * 
 * @return int 
 */
int Enemy::getXPValue() const {
    return xpValue;
}

/**
 * @brief Gets the enemy's sight distance
 * 
 * @return int 
 */
int Enemy::getSightDistance() const {
    return sightDistance;
}

/**
 * @brief Gets the enemy type
 * 
 * @return short unsigned 
 */
short unsigned Enemy::getType() const {
    return type;
}

/**
 * @brief Generates a type of enemy based on probability
 * 
 * @return short unsigned 
 */
short unsigned Enemy::generateEnemyType() {
    int value = (rand() % 100) + 1;

    if(value <= 20)
        return wolf;
    else
        return bull;
}

/**
 * @brief Tracks enemy to position
 * 
 * @param playerPosition 
 */
void Enemy::track(sf::Vector2f pos) {
    float dist_x = pos.x - sprite->getPosition().x;
    float dist_y = pos.y - sprite->getPosition().y;

    angle = ((atan2(dist_y, dist_x)) * 180 / 3.14);
    
    sprite->setRotation(angle - 90);
}

/**
 * @brief Moves enemy towards position
 * 
 * @param dt 
 * @param pos 
 */
void Enemy::follow(const float& dt, sf::Vector2f pos) {
    move(dt, cos(angle * 3.14 / 180), sin(angle * 3.14 / 180));
}

/**
 * @brief Renders all components for enemy
 * 
 * @param target 
 */
void Enemy::render(sf::RenderTarget& target) {
    if(healthBar)
        healthBar->render(target);

    if(sprite)
        target.draw(*sprite);

    if(hitbox)
        hitbox->render(target);
}

/**
 * @brief Updates enemy
 * 
 */
void Enemy::update() {
    healthBar->setPosition(hitbox->getPosition().x, hitbox->getPosition().y + (hitbox->getGlobalBounds().height));
    hitbox->update();
}