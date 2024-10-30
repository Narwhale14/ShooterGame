#include "../../Resource/Entity/Entity.h"

/**
 * @brief Construct a new Entity:: Entity object
 * 
 * @param texture a pointer pointing to a texture
 */
Entity::Entity() {
    texture = nullptr;
    sprite = nullptr;

    movementSpeed = 100.f;
    angle = 0.f;
}

/**
 * @brief Destroy the Entity:: Entity object
 *        Deletes dynamically allocated sprite and texture
 */
Entity::~Entity() {
    delete sprite;
}

/**
 * @brief Initializes sprite and sets its origin to the center + scales it down to 5%
 * 
 * @param texture a pointer pointing to a texture
 */
void Entity::createSprite(sf::Texture* texture) {
    this->texture = texture;
    sprite = new sf::Sprite(*this->texture);

    // Sets origin to middle of shape
    sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
    sprite->setScale(0.05f, 0.05f);
}

/**
 * @brief Moves character based on values of x and y
 * 
 * @param dt deltaTime
 * @param dir_x from -1 to 1 in terms velocity on the X axis
 * @param dir_y from -1 to 1 in terms velocity on the Y axis
 */
void Entity::move(const float& dt, const float dir_x, const float dir_y) {
    if(sprite) {
        sprite->move(dir_x * movementSpeed * dt, dir_y * movementSpeed * dt);
    }
}