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
    initializeKeybinds();
    initializeFonts();

    playButton = new Button(fonts["SONO_R"], "PLAY", sf::Vector2f(window->getSize().x / 6, window->getSize().y / 8), sf::Color(70, 70, 70, 150), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
    playButton->setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));

    exitButton = new Button(fonts["SONO_R"], "EXIT", sf::Vector2f(window->getSize().x / 6, window->getSize().y / 8), sf::Color(70, 70, 70, 150), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
    exitButton->setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2 + playButton->getSize().y * 1.5f));
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
    // If target is a nullptr, then set target to the window used from State class
    if(!target)
        target = window;

    playButton->render(*target);
    exitButton->render(*target);
}

/**
 * @brief Initializes available keybinds for specific GameState object by loading gamestate keybinds from file
 * 
 */
void MainMenu::initializeKeybinds() {
    std::ifstream inputFile("Config/mainmenu_keybinds.ini");

    if(inputFile.is_open()) {
        std::string key = "";
        std::string key2 = "";

        while(inputFile >> key >> key2) {
            keybinds[key] = supportedKeys->at(key2);
        }
    }

    inputFile.close();
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