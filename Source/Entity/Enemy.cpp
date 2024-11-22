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
            maxVelocity = 275;
            xpValue = 15;
            killHealthValue = 7;
            sightDistance = 13;
            damage = 10;
            break;
        case 1:
            createSprite(&textures["ENEMY_BULL"], 0.4f);
            maxVelocity = 175;
            xpValue = 10;
            sightDistance = 7;
            killHealthValue = 10;
            damage = 15;
            break;
        default:
            exit(1);
    }

    setPosition(sf::Vector2f(x, y));

    createHitbox(sprite, sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2, sf::Color::Red);
    createHealthBar(hitbox->getGlobalBounds().width, hitbox->getGlobalBounds().height, sprite->getPosition().x, sprite->getPosition().y);

    state = relaxed;
    relaxationTimeMS = 5000;

    thresholdHeath = healthBar->getHealth() / 4;
    fearSpeedMultiplier = 1.2f;
    injurySpeedMultiplier = 0.5f;
    angleDeviation = ((rand() % 60 + 1) - 30);

    biteTimeMS = 500;
    injuryTimeMS = 250;

    angle = (rand() % 360) + 1;
    relaxedAngle = angle;
    sprite->setRotation(angle);

    hasBeenRestarted = false;
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
 * @brief Returns enemy damage
 * 
 * @return int 
 */
int Enemy::getDamage() const {
    return damage;
}

/**
 * @brief Returns true if enemy is attacking
 * 
 * @return true 
 * @return false 
 */
bool Enemy::isAttacking() const {
    return state == enraged || state == determined;
}

/**
 * @brief Returns true if enemy is low
 * 
 * @return true 
 * @return false 
 */
bool Enemy::isLow() const {
    return healthBar->getHealth() < thresholdHeath;
}

/**
 * @brief Checks if enemy is close to a player relative to viewSize
 * 
 * @param objPos 
 * @param mapSize 
 * @return true 
 * @return false 
 */
bool Enemy::isCloseTo(const sf::Vector2f& objPos, const sf::Vector2f& viewSize) {
    return (getPosition().x > objPos.x - (viewSize.x / 10) && getPosition().x < objPos.x + (viewSize.x / 10) 
         && getPosition().y > objPos.y - (viewSize.y / 7) && getPosition().y < objPos.y + (viewSize.y / 7));
}

/**
 * @brief Gets relaxation timer
 * 
 * @return true 
 * @return false 
 */
bool Enemy::relaxationTimerPassed() {
    if(relaxationTimer.getElapsedTime().asMilliseconds() > relaxationTimeMS) {
        relaxationTimer.restart();
        return true;
    }

    return false;
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
 * @brief Checks if injury timer passed
 * 
 * @return true 
 * @return false 
 */
bool Enemy::injuryTimerPassed() {
    return injuryTimer.getElapsedTime().asMilliseconds() < injuryTimeMS;
}

/**
 * @brief Restarts injury timer
 * 
 */
void Enemy::resetInjuryTimer() {
    injuryTimer.restart();
    hasBeenRestarted = true;
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

    if(value <= 15)
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
void Enemy::track(const sf::Vector2f& pos) {
    float dist_x = pos.x - sprite->getPosition().x;
    float dist_y = pos.y - sprite->getPosition().y;

    angle = ((atan2(dist_y, dist_x)) * 180 / 3.14);
    
    if(state == enraged || state == determined)
        sprite->setRotation(angle - 90);
    else if(state == scared)
        sprite->setRotation(angle - 270 + angleDeviation);
    else if(state == relaxed)
        sprite->setRotation(relaxedAngle);
}

/**
 * @brief Moves enemy towards position
 * 
 * @param dt 
 * @param pos 
 */
void Enemy::follow(const float& dt, const sf::Vector2f& pos) {
    multiplier = 1; // Default speed
        
    if(state == scared) // Running away faster
        multiplier *= -1 * fearSpeedMultiplier;
    else if(state == determined) // Attacking faster
        multiplier *= fearSpeedMultiplier;

    if(injuryTimerPassed() && hasBeenRestarted)
        multiplier *= injurySpeedMultiplier;
        
    if(state == scared)
        move(dt, cos((angle + angleDeviation) * 3.14 / 180), sin((angle + angleDeviation) * 3.14 / 180));
    else
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

    if(healthBar->getHealth() < thresholdHeath && state != determined && state != relaxed)
        state = scared;
}