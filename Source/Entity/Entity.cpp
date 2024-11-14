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
    
    movementSpeed = 300.f;
    angle = 0.f;
    scale = 0.f;
}

/**
 * @brief Destroy the Entity:: Entity object
 *        Deletes dynamically allocated sprite and texture
 */
Entity::~Entity() {
    delete sprite;
    delete health;
    delete hitbox;
}

/**
 * @brief Sets the scale
 * 
 * @param scale 
 */
void Entity::setScale(float s) {
    sprite->setScale(s, s);
    scale = s;
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
 * @brief Returns the entity's hitbox bounds
 * 
 * @return sf::FloatRect 
 */
sf::FloatRect Entity::getHitboxBounds() {
    return hitbox->getGlobalBounds();
}

/**
 * @brief Initializes sprite and sets its origin to the center
 * 
 * @param texture a pointer pointing to a texture
 */
void Entity::createSprite(sf::Texture* texture) {
    this->texture = texture;
    sprite = new sf::Sprite(*this->texture);

    // Sets origin to middle of shape
    sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
    setScale(scale);
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
 * @brief Creates hitbox
 * 
 * @param s sprite for hitbox
 * @param offset_x x offset (pos)
 * @param offset_y y offset (pos)
 * @param width width of hitbox
 * @param height height of hitbox
 */
void Entity::createHitbox(sf::Sprite* s, float offset_x, float offset_y, float width, float height, sf::Color color) {
    hitbox = new Hitbox(s, offset_x, offset_y, width, height, color);
}

/**
 * @brief Checks to see if hitbox collides with another FloatRect
 * 
 * @param rect 
 * @return true 
 * @return false 
 */
bool Entity::checkCollision(const sf::FloatRect rect) {
    return hitbox->getGlobalBounds().intersects(rect);
}

/**
 * @brief Creates healthbar
 * 
 * @param size_x 
 * @param size_y 
 */
void Entity::createHealthBar(float size_x, float size_y, float pos_x, float pos_y) {
    health = new HealthBar(size_x, size_y, pos_x, pos_y);
}

/**
 * @brief Negates health of entity
 * 
 * @param damage 
 */
void Entity::negateHealth(int damage) {
    health->setHealth(health->getHealth() - damage);
}

/**
 * @brief Moves character based on values of x and y
 * 
 * @param dt deltaTime
 * @param dir_x from -1 to 1 in terms velocity on the X axis
 * @param dir_y from -1 to 1 in terms velocity on the Y axis
 */
void Entity::move(const float& dt, const float dir_x, const float dir_y) {
    if(sprite)
        sprite->move(dir_x * movementSpeed * dt, dir_y * movementSpeed * dt);
}