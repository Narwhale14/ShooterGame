/**
 * @file GameState.cpp
 * @author Niall Murray
 * @brief GameState implementation file
 * @date 2024-10-23
 */
#include "../Resource/GameState.h"

/**
 * @brief Construct a new Game State:: Game State object
 * 
 * @param window pointer to the window (takes it from Game class where it's called initially)
 * @param supportedKeys takes list of supported keys from Game class and runs it through State classes constructor
 */
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys) : State(window, supportedKeys) {
    // Both of these functions essentially just exist to clean up the constructor
    this->initializeKeybinds();
    this->initializeTextures();

    this->player = new Player(0, 0, &this->textures["PLAYER"]);
    this->shoot = new Mortar(30.f,&this->textures["XPLOSION"]);
    
}

GameState::~GameState() {
    delete this->player;
    delete this->shoot;
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
        this->player->move(dt, -1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        this->player->move(dt, 1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        this->player->move(dt, 0.f, -1.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        this->player->move(dt, 0.f, 1.f);
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
    this->updateMousePositions();
    this->updateInput(dt);
    this->player->update(dt);
    this->player->pointToCursor(mousePosView);
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

    this->player->render(target);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SHOOT")))){
        this->shoot->fire(mousePosView);
        this->shoot->render(target);
    }
}

/**
 * @brief Initializes available keybinds for specific GameState object by loading gamestate keybinds from file
 * 
 */
void GameState::initializeKeybinds() {
    std::ifstream inputFile("Config/gamestate_keybinds.ini");

    if(inputFile.is_open()) {
        std::string key = "";
        std::string key2 = "";

        while(inputFile >> key >> key2) {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    inputFile.close();
}

/**
 * @brief Loads all textures into map
 * 
 */
void GameState::initializeTextures() {
    sf::Texture temp; // Use this whenever loading a texture

    if(temp.loadFromFile("Textures/player.png")) {
        std::cout << "Player file loaded!\n";
        this->textures["PLAYER"] = temp; // Names player texture PLAYER
    }
    
    if(temp.loadFromFile("Textures/xplosion.png")) {
        std::cout << "Xplosion file loaded!\n";
        this->textures["XPLOSION"] = temp; // Names player texture PLAYER
    }
}