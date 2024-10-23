/**
 * @file GameState.cpp
 * @author Niall Murray
 * @brief GameState implementation file
 * @date 2024-10-23
 */
#include "GameState.h"

/**
 * @brief Construct a new Game State:: Game State object
 * 
 * @param window pointer to the window (takes it from Game class where it's called initially)
 * @param supportedKeys takes list of supported keys from Game class and runs it through State classes constructor
 */
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys) : State(window, supportedKeys) {
    this->initializeKeybinds();
}

GameState::~GameState() {

}

/**
 * @brief Checks for input required in the state
 * 
 * @param dt deltaTime
 */
void GameState::updateInput(const float& dt) {
    this->checkForQuit();

    // Updates player input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
        this->player.move(dt, -1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        this->player.move(dt, 1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        this->player.move(dt, 0.f, -1.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        this->player.move(dt, 0.f, 1.f);
}

/**
 * @brief Function called whenever state ends
 * 
 */
void GameState::endState() {
    std::cout << "Ending GameState!\n";
}

/**
 * @brief Updates GameState based on deltaTime and any entities
 * 
 * @param dt deltaTime
 */
void GameState::update(const float& dt) {
    this->updateInput(dt);

    this->player.update(dt);
}

/**
 * @brief Renders the GameState
 * 
 * @param target target window
 */
void GameState::render(sf::RenderTarget* target) {
    // If target is a nullptr, then set target to the window used from Game class
    if(!target) {
        target = this->window;
    }

    this->player.render(target);
}

/**
 * @brief Initializes available keybinds for specific GameState object
 * 
 */
void GameState::initializeKeybinds() {
    this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
    this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
    this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
    this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
    this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
}