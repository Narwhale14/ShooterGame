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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SHOOT")))){
        keyPressed=true;
        player->useHandheld(mousePosView);
    } else if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SHOOT")))) && keyPressed){
            keyPressed=player->stopHandheld(mousePosView);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT")))) {
        moveView(dt, -1.f, 0.f, player->getMovementSpeed());
        movePlayer(dt, -1.f, 0.f);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT")))) {
        moveView(dt, 1.f, 0.f, player->getMovementSpeed());
        movePlayer(dt, 1.f, 0.f);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP")))) {
        moveView(dt, 0.f, -1.f, player->getMovementSpeed());
        movePlayer(dt, 0.f, -1.f);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN")))) {
        moveView(dt, 0.f, 1.f, player->getMovementSpeed());
        movePlayer(dt, 0.f, 1.f);
    }
}

/**
 * @brief Updates collisions
 * 
 */
void MainMap::updateCollisions() {
    if(player->checkCollision(enemy->getHitboxBounds()))
        player->negateHealth(1);
    if(enemy->checkCollision(player->getHitboxBounds()))
        enemy->negateHealth(1);
}

/**
 * @brief Moves camera and detects if camera's border is crossing map's borders
 * 
 * @param dt deltaTime
 * @param dir_x direction moving x
 * @param dir_y direction moving y
 * @param movementSpeed speed of player
 */
void MainMap::moveView(const float& dt, const float dir_x, const float dir_y, const float movementSpeed) {
    bool crossingX = false;
    bool crossingY = false;

    if(player->getPosition().x < map->getCameraSize().x / 2)
        crossingX = true;
    if(player->getPosition().y < map->getCameraSize().y / 2)
        crossingY = true;

    if(player->getPosition().x > map->getTotalSize() - map->getCameraSize().x / 2)
        crossingX = true;
    if(player->getPosition().y > map->getTotalSize() - map->getCameraSize().y / 2)
        crossingY = true;

    if(!crossingX)
        map->moveCamera(dir_x * dt * movementSpeed, 0);
    if(!crossingY)
        map->moveCamera(0, dir_y * dt * movementSpeed);
}

/**
 * @brief Moves the player and detects whether player's hitbox crosses map borders
 * 
 * @param dt deltaTime
 * @param dir_x direction moving x
 * @param dir_y direction moving y
 */
void MainMap::movePlayer(const float& dt, const float dir_x, const float dir_y) {
    if(player->getPosition().x < 0 + player->getHitboxBounds().width / 2) // Left wall
        player->setPosition(sf::Vector2f(player->getHitboxBounds().width / 2, player->getPosition().y));
    if(player->getPosition().y < 0 + player->getHitboxBounds().height / 2) // Top wall
        player->setPosition(sf::Vector2f(player->getPosition().x, player->getHitboxBounds().height / 2));

    if(player->getPosition().x > map->getTotalSize() - player->getHitboxBounds().width / 2) // Right wall
        player->setPosition(sf::Vector2f(map->getTotalSize() - player->getHitboxBounds().width / 2, player->getPosition().y));
    if(player->getPosition().y > map->getTotalSize() - player->getHitboxBounds().height / 2) // Bottom wall
        player->setPosition(sf::Vector2f(player->getPosition().x, map->getTotalSize() - player->getHitboxBounds().height / 2));

    player->move(dt, dir_x, dir_y);
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
    player->updateRotation(mousePosView);

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