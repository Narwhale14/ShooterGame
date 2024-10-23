/**
 * @file State.cpp
 * @author Niall Murray
 * @brief State class implementation
 * @date 2024-10-23
 */
#include "../Resource/State.h"

/**
 * @brief Construct a new State:: State object
 * 
 * @param window takes pointer to window and bases a state off of it
 * @param supportedKeys map of supported keybinds (found in Game class) and stores it in it's own version in State class
 */
State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys) {
    this->window = window;

    this->supportedKeys = supportedKeys;

    this->quit = false;
}

State::~State() {

}

/**
 * @brief Returns current open state of state
 * 
 * @return true 
 * @return false 
 */
const bool& State::getQuit() const {
    return this->quit;
}

/**
 * @brief Checks if user wants to quit state
 * 
 */
void State::checkForQuit() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
        this->quit = true;
    }
}

/**
 * @brief Updates mouse positions
 * 
 */
void State::updateMousePositions() {
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}