/**
 * @file MainMenu.cpp
 * @author Niall Murray
 * @brief Main menu class initialization
 * @date 2024-11-05
 */

#include "../../Resource/GameManager/MainMenu.h"

/**
 * @brief Construct a new Game State:: Game State object
 * 
 * @param window pointer to the window (takes it from Game class where it's called initially)
 * @param supportedKeys takes list of supported keys from Game class and runs it through State classes constructor
 */
MainMenu::MainMenu(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys) : State(window, supportedKeys) {
    initializeFonts();
    initializeTextures();

    background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setPosition(0, 0);

    background.setTexture(&textures["BACKGROUND"]);

    // play button
    playButton = new Button(fonts["SONO_R"], "PLAY", sf::Vector2f(window->getSize().x / 6, window->getSize().y / 8), sf::Color(70, 70, 70, 150), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
    playButton->setPosition(sf::Vector2f((window->getSize().x / 2) - playButton->getSize().x * 0.75f, window->getSize().y / 2));

    // exit button
    exitButton = new Button(fonts["SONO_R"], "EXIT", sf::Vector2f(window->getSize().x / 6, window->getSize().y / 8), sf::Color(70, 70, 70, 150), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
    exitButton->setPosition(sf::Vector2f((window->getSize().x / 2) + exitButton->getSize().x * 0.75f, window->getSize().y / 2));
}

/**
 * @brief Destroy the Main Menu:: Main Menu object
 * 
 */
MainMenu::~MainMenu() {
    delete playButton;
    delete exitButton;
}

/**
 * @brief Checks if user wants to quit state
 * 
 */
void MainMenu::checkForQuit() {
    if(playButton->getState() == 2)
        quit = true;
    if(exitButton->getState() == 2)
        flush = true;
}

/**
 * @brief Checks for input required in the state
 * 
 * @param dt deltaTime
 */
void MainMenu::updateInput(const float& dt) {
    checkForQuit();
}

/**
 * @brief Updates GameState based on deltaTime and any entities
 * 
 * @param dt deltaTime
 */
void MainMenu::update(const float& dt) {
    updateMousePositions();
    updateInput(dt);

    playButton->update(mousePosView);
    exitButton->update(mousePosView);
}

/**
 * @brief Renders the GameState
 * 
 * @param target target window
 */
void MainMenu::render(sf::RenderTarget* target) {
    if(!target)
        target = window;

    target->draw(background);
    playButton->render(*target);
    exitButton->render(*target);
}

/**
 * @brief Loads all textures into map
 * 
 */
void MainMenu::initializeFonts() {
    sf::Font temp;

    if(temp.loadFromFile("Fonts/Sono-Regular.ttf"))
        fonts["SONO_R"] = temp;
}

/**
 * @brief Loads all textures into map
 * 
 */
void MainMenu::initializeTextures() {
    sf::Texture temp;

    if(temp.loadFromFile("Textures/background.png"))
        textures["BACKGROUND"] = temp;
}