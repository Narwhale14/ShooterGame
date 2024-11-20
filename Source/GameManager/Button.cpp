/**
 * @file button.cpp
 * @author Niall Murray
 * @brief Button class implementation file
 * @date 2024-10-15
 */

#include "../../Resource/GameManager/Button.h"

/**
 * @brief Construct a new Button:: Button object
 * 
 * @param font button text font
 * @param s text string
 * @param size size of button
 * @param idle idle color
 * @param hover hover color
 * @param active active color
 */
Button::Button(sf::Font& font, std::string s, sf::Vector2f size, sf::Color idle, sf::Color hover, sf::Color active) {
    idleColor = idle;
    hoverColor = hover;
    activeColor = active;

    button.setSize(size);
    button.setOrigin(button.getSize().x / 2, button.getSize().y / 2);
    button.setFillColor(idleColor);

    this->font = font;
    text.setFont(font);
    text.setCharacterSize(button.getGlobalBounds().height / 2);

    text.setString(s);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(button.getPosition().x / 2, button.getPosition().y / 2);

    text.setFillColor(sf::Color::Black);

    sprite = nullptr;
}

/**
 * @brief Construct a new Button:: Button object
 * 
 * @param size size of button
 * @param hover hover color
 * @param active active color
 * @param texture texture of button
 */
Button::Button(sf::Vector2f size, sf::Color hover, sf::Color active, sf::Texture* texture) {
    hoverColor = hover;
    activeColor = active;
    idleColor = sf::Color::Transparent;

    sprite = new sf::Sprite(*texture);

    sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
    sprite->setScale(size.x / texture->getSize().x, size.y / texture->getSize().y);

    button.setSize(size / 1.25f);
    button.setOrigin(button.getSize().x / 2, button.getSize().y / 2);
    button.setFillColor(idleColor);
}

/**
 * @brief Destroy the Button:: Button object
 * 
 */
Button::~Button() {
    delete sprite;
}

/**
 * @brief Sets position of button
 * 
 * @param position 
 */
void Button::setPosition(sf::Vector2f position) {
    button.setPosition(position.x, position.y);

    if(sprite)
        sprite->setPosition(position.x, position.y);

    text.setPosition(position.x, position.y - button.getGlobalBounds().height / 8);
}

/**
 * @brief Gets the button state
 * 
 * @return short unsigned 
 */
short unsigned Button::getState() {
    return state;
}

/**
 * @brief Returns button's size
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Button::getSize() const {
    return button.getSize();
}

/**
 * @brief Updates button per frame
 * 
 * @param e passed event by reference
 * @param window 
 */
void Button::update(const sf::Vector2f& mousePosition) {
    state = idle; // Default

    button.setFillColor(idleColor);

    if(button.getGlobalBounds().contains(mousePosition)) {
        state = hovered;
        button.setFillColor(hoverColor);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            state = clicked;
            button.setFillColor(activeColor);
        }
    }
}

/**
 * @brief 
 * 
 * @param target 
 * @param states 
 */
void Button::render(sf::RenderTarget& target) {
    if(sprite)
        target.draw(*sprite);
    else
        target.draw(button);

    target.draw(text);
}