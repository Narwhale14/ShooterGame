#include "../Resource/Entity.h"

/**
 * @brief Construct a new Entity:: Entity object
 * 
 * @param texture a pointer pointing to a texture
 */
Entity::Entity(sf::Texture* texture) {
    this->texture = nullptr;
    this->sprite = nullptr;

    this->movementSpeed = 100.f;
    this->angle = 0.f;
}

/**
 * @brief Destroy the Entity:: Entity object
 *        Deletes dynamically allocated sprite and texture
 */
Entity::~Entity() {
    delete this->sprite;
}

/**
 * @brief Initializes sprite and sets its origin to the center + scales it down to 5%
 * 
 * @param texture a pointer pointing to a texture
 */
void Entity::createSprite(sf::Texture* texture) {
    this->texture = texture;
    this->sprite = new sf::Sprite(*this->texture);

    // Sets origin to middle of shape
    this->sprite->setOrigin(this->sprite->getGlobalBounds().width / 2, this->sprite->getGlobalBounds().height / 2);
    this->sprite->setScale(0.05f, 0.05f);
}

/**
 * @brief Moves character based on values of x and y
 * 
 * @param dt deltaTime
 * @param dir_x from -1 to 1 in terms velocity on the X axis
 * @param dir_y from -1 to 1 in terms velocity on the Y axis
 */
void Entity::move(const float& dt, const float dir_x, const float dir_y) {
    if(this->sprite) {
        this->sprite->move(dir_x * this->movementSpeed * dt, dir_y * this->movementSpeed * dt);
    }
}

void Entity::update(const float& dt) {

}

/**
 * @brief Posts sprite to window
 * 
 * @param target 
 */
void Entity::render(sf::RenderTarget* target) {
    if(this->sprite) {
        target->draw(*this->sprite);
    }
}