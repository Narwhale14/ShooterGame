/**
 * @file GameState.cpp
 * @author Niall Murray
 * @brief GameState implementation file
 * @date 2024-10-23
 */
#include "../Resource/MainMap.h"

/**
 * @brief Construct a new Game State:: Game State object
 * 
 * @param window pointer to the window (takes it from Game class where it's called initially)
 * @param supportedKeys takes list of supported keys from Game class and runs it through State classes constructor
 */
MainMap::MainMap(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys) : State(window, supportedKeys) {
    // Both of these functions essentially just exist to clean up the constructor
    initializeKeybinds();
    initializeTextures();

    player = new Player(0, 0, &textures);
    keyPressed=false;
}

MainMap::~MainMap() {
    delete player;
}

/**
 * @brief Checks for input required in the state
 * 
 * @param dt deltaTime
 */
void MainMap::updateInput(const float& dt) {
    this->checkForQuit();

    // Updates player input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
        player->move(dt, -1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
        player->move(dt, 1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
        player->move(dt, 0.f, -1.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
        player->move(dt, 0.f, 1.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SHOOT"))))
        keyPressed=true;
    if(keyPressed)
        keyPressed=player->useHandheld(mousePosView);
}

/**
 * @brief Function called whenever state ends
 * 
 */
void MainMap::endState() {
    std::cout << "Ending GameState!\n";
}

/**
 * @brief Updates GameState based on deltaTime and any entities
 * 
 * @param dt deltaTime
 */
void MainMap::update(const float& dt) {
    updateMousePositions();
    updateInput(dt);
    player->pointToCursor(mousePosView);
}

/**
 * @brief Renders the GameState
 * 
 * @param target target window
 */
void MainMap::render(sf::RenderTarget* target) {
    // If target is a nullptr, then set target to the window used from State class
    if(!target) {
        target = window;
    }

    player->render(target);
}

/**
 * @brief Initializes available keybinds for specific GameState object by loading gamestate keybinds from file
 * 
 */
void MainMap::initializeKeybinds() {
    std::ifstream inputFile("Config/gamestate_keybinds.ini");

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
void MainMap::initializeTextures() {
    sf::Texture temp; // Use this whenever loading a texture

    if(temp.loadFromFile("Textures/player.png")) {
        std::cout << "Player file loaded!\n";
        textures["PLAYER"] = temp; // Names player texture PLAYER
    }
    
    if(temp.loadFromFile("Textures/explosion.png")) {
        std::cout << "Explosion file loaded!\n";
        textures["EXPLOSION"] = temp; // Names explosion texture EXPLOSION
    }
}