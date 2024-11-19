#include "../../Resource/Entity/Entity.h"

/**
 * @brief Construct a new Entity:: Entity object
 * 
 * @param texture a pointer pointing to a texture
 */
Entity::Entity() {
    texture = nullptr;
    sprite = nullptr;
    hitbox = nullptr;
    healthBar = nullptr;
    
    angle = 0.f;
    scale = 0.f;

    immunityTimeMS = 500;
}

/**
 * @brief Destroy the Entity:: Entity object
 *        Deletes dynamically allocated sprite and texture
 */
Entity::~Entity() {
    delete sprite;
    delete healthBar;
}

/**
 * @brief Set the position of entity
 * 
 * @param x 
 * @param y 
 */
void Entity::setPosition(sf::Vector2f pos) {
    sprite->setPosition(pos);
}

/**
 * @brief Returns the entity's movement speed
 * 
 * @return float 
 */
float Entity::getMovementSpeed() {
    return movementSpeed;
}

/**
 * @brief Returns the entity's position
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Entity::getPosition() {
    return sprite->getPosition();
}

/**
 * @brief Checks if entity is dead
 * 
 * @return true 
 * @return false 
 */
bool Entity::isAlive() {
    return healthBar->getHealth() > 0;
}

/**
 * @brief Changes the sprite
 * 
 * @param texture 
 */
void Entity::changeSprite(sf::Texture* texture) {
    this->texture = texture;
    sprite->setTexture(*(this->texture));
}

/**
 * @brief Creates healthbar
 * 
 * @param size_x 
 * @param size_y 
 */
void Entity::createHealthBar(float size_x, float size_y, float pos_x, float pos_y) {
    healthBar = new HealthBar(size_x, size_y, pos_x, pos_y);
}

/**
 * @brief Negates health of entity
 * 
 * @param damage 
 */
void Entity::negateHealth(int damage) {
    healthBar->setHealth(healthBar->getHealth() - damage);
    immunityTimer.restart();
}

/**
 * @brief Checks if hit clock is passed hit timer
 * 
 * @return true 
 * @return false 
 */
bool Entity::getImmunity() {
    return immunityTimer.getElapsedTime().asMilliseconds() < immunityTimeMS;
}

/**
 * @brief Moves character based on values of x and y
 * 
 * @param dt deltaTime
 * @param dir_x from -1 to 1 in terms velocity on the X axis
 * @param dir_y from -1 to 1 in terms velocity on the Y axis
 */
void Entity::move(const float& dt, const float dir_x, const float dir_y) {
    velocity.x = dir_x * movementSpeed * dt;
    velocity.y = dir_y * movementSpeed * dt;

    if(sprite)
        sprite->move(velocity.x, velocity.y);
}