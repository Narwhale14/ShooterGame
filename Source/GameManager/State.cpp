/**
 * @file State.cpp
 * @author Niall Murray
 * @brief State class implementation
 * @date 2024-10-23
 */
#include "../../Resource/GameManager/State.h"

/**
 * @brief Construct a new State:: State object
 * 
 * @param window takes pointer to window and bases a state off of it
 * @param supportedKeys map of supported keybinds (found in Game class) and stores it in it's own version in State class
 */
State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys) {
    this->window = window;
    this->supportedKeys = supportedKeys;

    view.setSize(window->getSize().x, window->getSize().y);
    view.setCenter(window->getSize().x / 2.f, window->getSize().y / 2.f);
    viewSpeed = 100.f;

    quit = false;
    flush = false;
}

State::~State() {

}

void State::moveView(const float& dt, const float dir_x, const float dir_y) {
    view.move(dir_x * dt * viewSpeed, dir_y * dt * viewSpeed);
}

/**
 * @brief Returns current open state of state
 * 
 * @return true 
 * @return false 
 */
const bool& State::getQuit() const {
    return quit;
}

/**
 * @brief Returns whether the user wants to exit the program
 * 
 * @return true 
 * @return false 
 */
const bool& State::getFlush() const {
    return flush;
}

/**
 * @brief Ends state
 * 
 */
void State::endState() {
    quit = true;
}

/**
 * @brief Updates mouse positions
 * 
 */
void State::updateMousePositions() {
    mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}