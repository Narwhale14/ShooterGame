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
 * @param s text
 * @param position vector position
 * @param size 
 * @param color 
 */
Button::Button(sf::Texture& texture, sf::Font& font, std::string s, sf::Vector2f size) {
    mTexture = texture;
    mFont = font;

    mButtonColor = sf::Color::White; // default
    mPosition = sf::Vector2f(0, 0);
    mSize = size;

    mPhrase = s;

    initializeButton();
    initializeText();
}

/**
 * @brief Sets position of button
 * 
 * @param position 
 */
void Button::setPosition(sf::Vector2f position) {
    mPosition = position;
    mButton.setPosition(position.x, position.y);

    unsigned int fontSize = mButton.getGlobalBounds().height / 2;
    mText.setCharacterSize(fontSize);
    mText.setPosition(position.x, position.y - fontSize / 4);
}

/**
 * @brief Sizes button size
 * 
 * @param size 
 */
void Button::setSize(sf::Vector2f size) {
    mButton.setScale(size.x / mTexture.getSize().x, size.y / mTexture.getSize().y);

    unsigned int fontSize = mButton.getGlobalBounds().height / 2;
    mText.setCharacterSize(fontSize);
    mText.setOrigin(mText.getGlobalBounds().width / 2, mText.getGlobalBounds().height / 2);
    mText.setPosition(mPosition.x, mPosition.y - fontSize / 4);

    mSize = size;
}

/**
 * @brief Sets button text
 * 
 * @param s 
 */
void Button::setText(std::string s) {
    mText.setString(s);
    mText.setOrigin(mText.getGlobalBounds().width / 2, mText.getGlobalBounds().height / 2);
}

/**
 * @brief Changes button color
 * 
 * @param btnColor 
 */
void Button::setColor(sf::Color btnColor) {
    mButtonColor = btnColor;
    mButton.setColor(mButtonColor);
}

/**
 * @brief Updates button per frame
 * 
 * @param e passed event by reference
 * @param window 
 */
void Button::update(sf::Event& e, sf::RenderWindow& window) {
    sf::Vector2i mPos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(mPos);

    bool mouseInButton =    mousePosition.x >= mButton.getPosition().x - mButton.getGlobalBounds().width/2
                            && mousePosition.x <= mButton.getPosition().x + mButton.getGlobalBounds().width/2
                            && mousePosition.y >= mButton.getPosition().y - mButton.getGlobalBounds().height/2
                            && mousePosition.y <= mButton.getPosition().y + mButton.getGlobalBounds().height/2;

    if(e.type == sf::Event::MouseMoved) {
        if(mouseInButton) {
            mText.setFillColor(mTextHover);
        } else {
            mText.setFillColor(mTextNormal);
        }
    }

    if(e.type == sf::Event::MouseButtonPressed) {
        if(e.mouseButton.button==sf::Mouse::Left) {
            if(mouseInButton) {
                mButton.setRotation(180);
            } else {
                mButton.setRotation(0);
            }
        }
    }
    
    if(e.type == sf::Event::MouseButtonReleased) {
        if (e.mouseButton.button == sf::Mouse::Left) {
            if(mouseInButton) {
                mText.setFillColor(mTextHover);
                mButton.setRotation(0);
            } else {
                mText.setFillColor(mTextNormal);
                mButton.setRotation(0);
            }
        }
    }
}

/**
 * @brief 
 * 
 * @param target 
 * @param states 
 */
void Button::draw(sf::RenderTarget& target,sf::RenderStates states) const {
    target.draw(mButton, states);
    target.draw(mText, states);
}

/**
 * @brief Saves code for the constructor
 * 
 */
void Button::initializeButton() {
    mButton.setTexture(mTexture);

    sf::Vector2u imageSize = mTexture.getSize();
    mButton.setOrigin(imageSize.x / 2, imageSize.y / 2);

    mButton.setScale(mSize.x / mTexture.getSize().x, mSize.y / mTexture.getSize().y);
    mButton.setPosition(mPosition.x, mPosition.y);
    mButton.setColor(mButtonColor);

    mBtnState = normal;
}

/**
 * @brief Also saves code for the contructor. 
 * 
 */
void Button::initializeText() {
    mText.setFont(mFont);

    unsigned int fontSize = mButton.getGlobalBounds().height / 2;
    mText.setCharacterSize(fontSize);

    mText.setString(mPhrase);

    mText.setOrigin(mText.getGlobalBounds().width / 2, mText.getGlobalBounds().height / 2);

    mText.setPosition(mPosition.x, mPosition.y - fontSize / 4);

    mTextNormal = sf::Color::Green;
    mTextHover = sf::Color::Red;
    mText.setFillColor(mTextNormal);
}