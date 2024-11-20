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
            killHealthValue = 7;
            sightDistance = 8;
            break;
        case 1:
            createSprite(&textures["ENEMY_BULL"], 0.4f);
            movementSpeed = 200;
            xpValue = 10;
            sightDistance = 7;
            killHealthValue = 5;
            break;
        default:
            exit(1);
    }

    setPosition(sf::Vector2f(x, y));

    createHitbox(sprite, sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2, sf::Color::Red, true);
    createHealthBar(hitbox->getGlobalBounds().width, hitbox->getGlobalBounds().height, sprite->getPosition().x, sprite->getPosition().y);

    state = relaxed;
    relaxationTimeMS = 3000;

    thresholdHeath = healthBar->getHealth() / 3;
    fearSpeedMultiplier = 1.3f;

    biteTimeMS = 500;

    angle = (rand() % 360) + 1;
    sprite->setRotation(angle);
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
 * @brief Gets the amount of HP player gains from killing enemy
 * 
 * @return int 
 */
int Enemy::getKillHealthValue() const {
    return killHealthValue;
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
 * @brief Returns the enemy's mood
 * 
 * @return short unsigned 
 */
short unsigned Enemy::getState() const {
    return state;
}

/**
 * @brief Gets relaxation timer
 * 
 * @return true 
 * @return false 
 */
bool Enemy::relaxationTimerPassed() const {
    return relaxationTimer.getElapsedTime().asMilliseconds() > relaxationTimeMS;
}

/**
 * @brief Checks if hit clock is passed hit timer
 * 
 * @return true 
 * @return false 
 */
bool Enemy::biteTimerPassed() {
    if(biteTimer.getElapsedTime().asMilliseconds() > biteTimeMS) {
        biteTimer.restart();
        return true;
    }

    return false;
}

/**
 * @brief Restarts clock externally
 * 
 */
void Enemy::restartRelaxationTimer() {
    relaxationTimer.restart();
}

/**
 * @brief Sets the state
 * 
 * @param state 
 */
void Enemy::setState(short unsigned state) {
    this->state = state;
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
 * @brief Relaxes enemy
 * 
 */
void Enemy::relax() {
    state = relaxed;
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
    
    if(state == enraged || state == determined)
        sprite->setRotation(angle - 90);
    else if(state == scared)
        sprite->setRotation(angle - 270);
}

/**
 * @brief Moves enemy towards position
 * 
 * @param dt 
 * @param pos 
 */
void Enemy::follow(const float& dt, sf::Vector2f pos) {
    if(state == enraged) // Normal speed
        move(dt, cos(angle * 3.14 / 180), sin(angle * 3.14 / 180));
    else if(state == scared) // Running away faster
        move(dt, -cos(angle * 3.14 / 180) * fearSpeedMultiplier, -sin(angle * 3.14 / 180) * fearSpeedMultiplier);
    else if(state == determined) // Attacking faster
        move(dt, cos(angle * 3.14 / 180) * fearSpeedMultiplier, sin(angle * 3.14 / 180) * fearSpeedMultiplier);
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

    if(healthBar->getHealth() < thresholdHeath && state != determined && state != relaxed)
        state = scared;
}