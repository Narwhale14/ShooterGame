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
    initializeTextures();
    initializeFonts();

    playButton = new Button(textures["BUTTON"], fonts["COLLEGE"], "PLAY", sf::Vector2f(100.f, 100.f));
}

MainMenu::~MainMenu() {
    delete playButton;
    std::cout << "Main menu poof\n";
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
void MainMenu::initializeTextures() {
    sf::Texture temp; // Use this whenever loading a texture

    if(temp.loadFromFile("Textures/button.png"))
        textures["BUTTON"] = temp;
}

/**
 * @brief Loads all textures into map
 * 
 */
void MainMenu::initializeFonts() {
    sf::Font temp;

    if(temp.loadFromFile("Fonts/college.ttf"))
        fonts["COLLGE"] = temp;
}