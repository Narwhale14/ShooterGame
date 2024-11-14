/**
 * @file GameState.cpp
 * @author Niall Murray
 * @brief GameState implementation file
 * @date 2024-10-23
 */
#include "../../Resource/GameManager/MainMap.h"

/**
 * @brief Construct a new Game State:: Game State object
 * 
 * @param window pointer to the window (takes it from Game class where it's called initially)
 * @param supportedKeys takes list of supported keys from Game class and runs it through State classes constructor
 */
MainMap::MainMap(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys) : State(window, supportedKeys) {
    initializeKeybinds();
    initializeTextures();
    registerTimeMS = 100;

    map = new Map(window, 20, 100.f, sf::Color(59, 104, 38, 255), sf::Color(49, 94, 28, 255));
    player = new Player(textures, map->getTotalSize() / 2, map->getTotalSize() / 2, 0.075f);
    enemy = new Enemy(textures, map->getTotalSize() / 2 - 100, map->getTotalSize() / 2 - 100, 0.075f);

    keyPressed = false;
}

/**
 * @brief Destroy the Main Map:: Main Map object
 * 
 */
MainMap::~MainMap() {
    delete player;
    delete enemy;
    delete map;
}

/**
 * @brief Checks if user wants to quit state
 * 
 */
void MainMap::checkForQuit() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE")))) {
        quit = true;
    }
}

/**
 * @brief Checks for input required in the state
 * 
 * @param dt deltaTime
 */
void MainMap::updateInput(const float& dt) {
    checkForQuit();

    // Updates weapon input
    if(player->isAlive()) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SHOOT")))){
            keyPressed=true;
            player->useHandheld(mousePosView);
        } else if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SHOOT")))) && keyPressed){
                keyPressed=player->stopHandheld(mousePosView);
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
            move(dt, -1.f, 0.f, player->getMovementSpeed());

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
            move(dt, 1.f, 0.f, player->getMovementSpeed());

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
            move(dt, 0.f, -1.f, player->getMovementSpeed());

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
            move(dt, 0.f, 1.f, player->getMovementSpeed());

        player->updateRotation(mousePosView);
    }
}

/**
 * @brief Updates collision
 * 
 * @return true 
 * @return false 
 */
void MainMap::updateCollisions() {
    // if(registerTimePassed()) {
    //     // If enemy touches player
    //     if(enemy->checkCollision(player->getHitboxBounds()))
    //         enemy->negateHealth(10);

    //     // If player touches enemy
    //     if(player->checkCollision(enemy->getHitboxBounds()))
    //         player->negateHealth(10);
    // }
}

/**
 * @brief Updates internal clock and resets when it passes a threshold
 * 
 * @return true 
 * @return false 
 */
bool MainMap::registerTimePassed() {
    if(internalClock.getElapsedTime().asMilliseconds() > registerTimeMS) {
        internalClock.restart();
        return true;
    }

    return false;
}

/**
 * @brief Moves camera and detects if camera's border is crossing map's borders
 * 
 * @param dt deltaTime
 * @param dir_x direction moving x
 * @param dir_y direction moving y
 * @param movementSpeed speed of player
 */
void MainMap::move(const float& dt, const float dir_x, const float dir_y, const float movementSpeed) {
    // If player is touching wall
    if(player->getPosition().x < 0 + player->getHitboxBounds().width / 2) // Left wall
        player->setPosition(sf::Vector2f(player->getHitboxBounds().width / 2, player->getPosition().y));
    if(player->getPosition().y < 0 + player->getHitboxBounds().height / 2) // Top wall
        player->setPosition(sf::Vector2f(player->getPosition().x, player->getHitboxBounds().height / 2));
    if(player->getPosition().x > map->getTotalSize() - player->getHitboxBounds().width / 2) // Right wall
        player->setPosition(sf::Vector2f(map->getTotalSize() - player->getHitboxBounds().width / 2, player->getPosition().y));
    if(player->getPosition().y > map->getTotalSize() - player->getHitboxBounds().height / 2) // Bottom wall
        player->setPosition(sf::Vector2f(player->getPosition().x, map->getTotalSize() - player->getHitboxBounds().height / 2));

    player->move(dt, dir_x, dir_y);
    map->setViewCenter(player->getPosition().x, player->getPosition().y);
}

/**
 * @brief Updates GameState based on deltaTime and any entities
 * 
 * @param dt deltaTime
 */
void MainMap::update(const float& dt) {
    updateMousePositions();
    updateCollisions();
    updateInput(dt);

    player->update();
    enemy->update();
}

/**
 * @brief Renders the GameState
 * 
 * @param target target window
 */
void MainMap::render(sf::RenderTarget* target) {
    // If target is a nullptr, then set target to the window used from State class
    if(!target)
        target = window;

    map->render(*target);
    enemy->render(*target);
    player->render(*target);
}

/**
 * @brief Initializes available keybinds for specific GameState object by loading gamestate keybinds from file
 * 
 */
void MainMap::initializeKeybinds() {
    std::ifstream inputFile("Config/mainmap_keybinds.ini");

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

    if(temp.loadFromFile("Textures/player_normal.png"))
        textures["PLAYER_NORMAL"] = temp;

    if(temp.loadFromFile("Textures/player_aimed.png"))
        textures["PLAYER_AIMED"] = temp;
    
    if(temp.loadFromFile("Textures/explosion.png"))
        textures["EXPLOSION"] = temp;

    if(temp.loadFromFile("Textures/bullet.png"))
        textures["BULLET"] = temp;

    if(temp.loadFromFile("Textures/glock.png"))
        textures["GLOCK"] = temp;
}