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

    multiplier = 1;
    velocity.x = 0;
    velocity.y = 0;
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
float Entity::getMaxVelocity() {
    return maxVelocity;
}

/**
 * @brief Stops X velocity
 * 
 */
void Entity::stopVelocityX() {
    velocity.x = 0.f;
}

/**
 * @brief Stops Y velocity
 * 
 */
void Entity::stopVelocityY() {
    velocity.y = 0.f;
}

/**
 * @brief Returns the entity's position
 * 
 * @return sf::Vector2f 
 */
const sf::Vector2f Entity::getPosition() {
    return sprite->getPosition();
}

/**
 * @brief Gets the distance to an obj from the entity
 * 
 * @param objPos 
 * @return float 
 */
float Entity::getDistanceTo(sf::Vector2f objPos) {
    return sqrt(pow(objPos.x - sprite->getPosition().x, 2) + pow(objPos.y - sprite->getPosition().y, 2));
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

const sf::FloatRect& Entity::getNextPositionBounds() const {
    return hitbox->getNextPosition(velocity);
}

/**
 * @brief Checks to see if another hitbox collides with this hitbox
 * 
 * @param rect 
 * @return true 
 * @return false 
 */
void Entity::checkCollision(Entity* entity) {
    sf::FloatRect homeBounds = hitbox->getGlobalBounds();
    sf::FloatRect entityBounds = entity->getHitboxBounds();
    sf::FloatRect nextPosition = entity->getNextPositionBounds();

    if(hitbox->getGlobalBounds().intersects(nextPosition)) {
        // Bottom collision
        
        if(entityBounds.top < homeBounds.top && entityBounds.top + entityBounds.height < homeBounds.top + homeBounds.height 
        && entityBounds.left < homeBounds.left + homeBounds.width && entityBounds.left + entityBounds.width > homeBounds.left) {
            entity->stopVelocityY();
            entity->setPosition(sf::Vector2f(entityBounds.left + (entityBounds.width / 2.f), homeBounds.top - (entityBounds.height / 2.f)));
        }

        // Top collision
        else if(entityBounds.top > homeBounds.top && entityBounds.top + entityBounds.height > homeBounds.top + homeBounds.height
        && entityBounds.left < homeBounds.left + homeBounds.width && entityBounds.left + entityBounds.width > homeBounds.left) {
            entity->stopVelocityY();
            entity->setPosition(sf::Vector2f(entityBounds.left + (entityBounds.width / 2.f), homeBounds.top + homeBounds.height + (entityBounds.height / 2.f)));
        }
        
        // Right collision
        if(entityBounds.left < homeBounds.left && entityBounds.left + homeBounds.width < homeBounds.left + homeBounds.width
        && entityBounds.top < homeBounds.top + homeBounds.height && entityBounds.top + entityBounds.height > homeBounds.top) {
            entity->stopVelocityX();
            entity->setPosition(sf::Vector2f(homeBounds.left - (entityBounds.width / 2.f), entityBounds.top + (entityBounds.height / 2.f)));
        }
        
        // Left collision
        else if(entityBounds.left > homeBounds.left && entityBounds.left + homeBounds.width > homeBounds.left + homeBounds.width
        && entityBounds.top < homeBounds.top + homeBounds.height && entityBounds.top + entityBounds.height > homeBounds.top) {
            entity->stopVelocityX();
            entity->setPosition(sf::Vector2f(homeBounds.left + homeBounds.width + (entityBounds.width / 2.f), entityBounds.top + (entityBounds.height / 2.f)));
        }
    }
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
void Entity::changeHealth(int incoming) {
    healthBar->setHealth(healthBar->getHealth() + incoming);
}

/**
 * @brief Moves character based on values of x and y
 * 
 * @param dt deltaTime
 * @param dir_x from -1 to 1 in terms velocity on the X axis
 * @param dir_y from -1 to 1 in terms velocity on the Y axis
 */
void Entity::move(const float& dt, const float dir_x, const float dir_y) {
    velocity.x = maxVelocity * dir_x;
    velocity.y = maxVelocity * dir_y;

    sprite->move(velocity.x * multiplier * dt, velocity.y * multiplier * dt);
}