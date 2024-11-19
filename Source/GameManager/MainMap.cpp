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
    initializeFonts();
    initializeTextures();
    srand(time(0));

    spawnIntervalMS = 5000;
    enemyCap = 10;

    map = new Map(window, 10, 100.f, sf::Color(59, 104, 38, 255), sf::Color(49, 94, 28, 255));
    player = new Player(textures, map->getMapCenter().x, map->getMapCenter().y, 0.075f);

    dmgUp = new Button(fonts["SONO_R"], "DAMAGE +", sf::Vector2f(window->getSize().x/6, window->getSize().y/2), sf::Color(70, 70, 70, 150), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
    fireRateUp = new Button(fonts["SONO_R"], "FIRE RATE +", sf::Vector2f(window->getSize().x/6, window->getSize().y/2), sf::Color(70, 70, 70, 150), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
    bullSpeedUp = new Button(fonts["SONO_R"], "BULLET SPEED +", sf::Vector2f(window->getSize().x/6, window->getSize().y/2), sf::Color(70, 70, 70, 150), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
    
    upAvailable={500,400,300,200,150,100,80,60,40,30,20,10,1};
    pause=false;
}

/**
 * @brief Destroy the Main Map:: Main Map object
 * 
 */
MainMap::~MainMap() {
    while(!enemies.empty()) {
        delete enemies[enemies.size() - 1];
        enemies.pop_back();
    }
    delete dmgUp;
    delete fireRateUp;
    delete bullSpeedUp;
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
 * @brief Checks if enough time passed since last enemy spawn
 * 
 * @return true 
 * @return false 
 */
bool MainMap::checkSpawnTimer() {
    if(spawnTimer.getElapsedTime().asMilliseconds() > spawnIntervalMS) {
        spawnTimer.restart();
        return true;
    } else {
        return false;
    }
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
    map->containInMap(player);

    player->move(dt, dir_x, dir_y);
    map->setViewCenter(player->getPosition().x, player->getPosition().y);
}

/**
 * @brief Updates GameState based on deltaTime and any entities
 * 
 * @param dt deltaTime
 */
void MainMap::update(const float& dt) {
    checkForQuit();
    updateMousePositions();
    checkUpgrade(player->getScore());
    if(!pause){
        updateMobs(dt, player->isAlive());

        if(player->isAlive()) {
            updateInput(dt);
            player->update();
        }
    }
    if(upgrading){
        dmgUp->update(mousePosView);
        fireRateUp->update(mousePosView);
        bullSpeedUp->update(mousePosView);
    }

}

/**
 * @brief Updates all enemies on screen
 * 
 * @param dt 
 */
void MainMap::updateMobs(const float& dt, bool spawn) {
    int maxRange = map->getTotalSize() - (player->getHitboxBounds().width);
    int minRange = player->getHitboxBounds().width;

    sf::Vector2u getRandCoords(rand() % maxRange + minRange, rand() % maxRange + minRange);

    for(size_t i = 0; i < enemies.size(); i++) { // All enemies
        // If dead, delete enemy
        if(!enemies[i]->isAlive() || enemies[i] == nullptr) {
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
            player->increaseScore();
            
            continue;
        } else {
            enemies[i]->update();

            // Tracks enemy to player and follows them
            enemies[i]->trackToPlayer(player->getPosition());
            if(!enemies[i]->checkCollision(player->getHitboxBounds()))
                enemies[i]->followPlayer(dt, player->getPosition());

            // If enemy is touching player and is alive, damage player
            if(player->checkCollision(enemies[i]->getHitboxBounds()))
                player->negateHealth(10);

            // If a bullet is touching enemy, damage enemy
            for(size_t j = 0; j < player->getActiveBullets().size(); j++) { // All active bullets
                if(enemies[i]->checkCollision(player->getActiveBullets()[j]->getHitboxBounds()))
                    enemies[i]->negateHealth(25);
            }
        }
    }

    // Spawns new enemy if timer passes interval (ADDS TO VECTOR)
    if(checkSpawnTimer() && spawn && enemies.size() < enemyCap)
        enemies.emplace_back(new Enemy(textures, getRandCoords.x, getRandCoords.y));
}

/**
 * @brief Checks for input required in the state
 * 
 * @param dt deltaTime
 */
void MainMap::updateInput(const float& dt) {
    // Updates weapon input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SHOOT"))))
        player->useHandheld(mousePosView);
    else if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SHOOT")))))
        player->stopHandheld(mousePosView);

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
    this->renderEnemies(target);

    player->render(*target);
    
    if(upgrading){
        dmgUp->render(*target);
        fireRateUp->render(*target);
        bullSpeedUp->render(*target);
    }
}

/**
 * @brief Renders active enemies
 * 
 * @param target 
 */
void MainMap::renderEnemies(sf::RenderTarget* target) {
    for(size_t i = 0; i < enemies.size(); i++) {
        if(enemies[i] != nullptr && enemies[i]->isAlive() && map->viewContains(enemies[i]->getPosition()))
            enemies[i]->render(*target);
    }
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

    if(temp.loadFromFile("Textures/shotgun.png"))
        textures["SHOTGUN"] = temp;

    if(temp.loadFromFile("Textures/wolf.png"))
        textures["ENEMY_WOLF"] = temp;

    if(temp.loadFromFile("Textures/bull.png"))
        textures["ENEMY_BULL"] = temp;
}

void MainMap::checkUpgrade(int score)
{

    if(score==upAvailable[upAvailable.size()-1]&&upgrading==false){
        dmgUp->setPosition(sf::Vector2f(player->getPosition().x - (dmgUp->getSize().x * 3 / 2), player->getPosition().y));
        bullSpeedUp->setPosition(player->getPosition());
        fireRateUp->setPosition(sf::Vector2f(player->getPosition().x + (fireRateUp->getSize().x * 3 / 2) ,player->getPosition().y));
        upAvailable.pop_back();
        runUpgrade();
        upgrading=true;
        pause=true;
    }else if(upgrading==true){
        runUpgrade();
    }
}

void MainMap::runUpgrade()
{
    if(dmgUp->getState()==2){
        player->increaseDmg();
        upgrading=false;
        pause=false;
    }else if(fireRateUp->getState()==2){
        player->increasefireRate();
        upgrading=false;
        pause=false;
    }else if(bullSpeedUp->getState()==2){
        player->increaseBullSpeed();
        upgrading=false;
        pause=false;
    }
}

/**
 * @brief Loads all textures into map
 * 
 */
void MainMap::initializeFonts() {
    sf::Font temp;

    if(temp.loadFromFile("Fonts/Sono-Regular.ttf"))
        fonts["SONO_R"] = temp;
}