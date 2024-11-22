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

    spawnIntervalMS = 1100; // Don't go below 1000 MS (1 second) because rand only updates every second
    enemyCap = 15;

    map = new Map(window, 20, 75.f, sf::Color(59, 104, 38, 255), sf::Color(49, 94, 28, 255));
    player = new Player(textures, map->getMapCenter().x, map->getMapCenter().y, 0.075f);
    levelBar = new LevelBar(fonts["SONO_B"], player->getHitboxBounds().width * 7, player->getHitboxBounds().height * 1.5f, player->getPosition().x, player->getPosition().y + (player->getHitboxBounds().height * 5.5f));

    dmgUp = new Button(sf::Vector2f(window->getSize().x/6, window->getSize().y/2), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), &textures["increaseDmgCard"]);
    fireRateUp = new Button(sf::Vector2f(window->getSize().x/6, window->getSize().y/2), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), &textures["increaseFireRateCard"]);
    bullSpeedUp = new Button(sf::Vector2f(window->getSize().x/6, window->getSize().y/2), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), &textures["increaseBullSpeedCard"]);

    tree = new Tree(textures["TREE_1"], 0.5f);
    tree->setPosition(player->getPosition());

    upgrading = false;
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
 * @brief Spawns an enemy in a random position
 * 
 */
void MainMap::spawnEnemy() {
    // Makes sure enemy spawns away from player
    sf::Vector2f getRandCoords;
    while(true) {
        int maxRange = map->getTotalSize() - (player->getHitboxBounds().width);
        int minRange = player->getHitboxBounds().width;

        getRandCoords.x = rand() % maxRange + minRange;
        getRandCoords.y = rand() % maxRange + minRange;

        if(!map->viewContains(getRandCoords) || map->getSizeAcross() < 15)
            break;
    }

    enemies.emplace_back(new Enemy(textures, getRandCoords.x, getRandCoords.y));
}

/**
 * @brief Updates GameState based on deltaTime and any entities
 * 
 * @param dt deltaTime
 */
void MainMap::update(const float& dt) {
    checkForQuit();
    updateMousePositions();

    if(upgrading) {
        dmgUp->update(mousePosView);
        fireRateUp->update(mousePosView);
        bullSpeedUp->update(mousePosView);

        updateUpgrade();
    } else if(player->isAlive() && !upgrading) {
        updateMobs(dt);
        player->update();
        updateInput(dt);

        if(checkSpawnTimer() && player->isAlive() && enemies.size() < enemyCap)
            spawnEnemy();

        updateLevelBar();
    }
}

/**
 * @brief Updates all enemies on screen
 * 
 * @param dt 
 */
void MainMap::updateMobs(const float& dt) {
    for(size_t i = 0; i < enemies.size(); i++) { // All enemies
        // If dead, delete enemy
        if(!enemies[i]->isAlive()) {
            delete enemies[i];
            enemies.erase(enemies.begin() + i);

            // Checks if player levels up from getting xp from killing enemy
            if(levelBar->addXp(enemies[i]->getXPValue()))
                upgrading = true;

            player->changeHealth(enemies[i]->getKillHealthValue());
            
            continue;
        }

        // Checks if player is close to enemy, and moves the enemy towards play when it is, or when enemy is enraged
        if(enemies[i]->getDistanceTo(player->getPosition()) < map->getGridSize() * enemies[i]->getSightDistance() || enemies[i]->getState() != 0) {
            if(enemies[i]->getState() != 2 && enemies[i]->getState() != 3)
                enemies[i]->setState(1); // Enraged if not scared

            enemies[i]->track(player->getPosition());

            // If not touching player then move towards
            if(!enemies[i]->checkCollision(player->getHitboxBounds()))
                enemies[i]->follow(dt, player->getPosition());

            map->updateCollision(enemies[i]);

            // If enemy is touching border while running from player, become determined
            if(map->borderIsTouching(enemies[i]->getPosition()) && enemies[i]->getState() == 2 && map->viewContains(enemies[i]->getPosition()))
                enemies[i]->setState(3);

            // If enemy is off screen for longer than a set despawn timer
            if(!map->viewContains(enemies[i]->getPosition()) && enemies[i]->relaxationTimerPassed())
                enemies[i]->setState(0); // Idle
        }

        enemies[i]->update();

        // If enemy is touching player and is alive, damage player
        if(player->checkCollision(enemies[i]->getHitboxBounds()) && enemies[i]->biteTimerPassed())
            player->changeHealth(-enemies[i]->getDamage());

        // If a bullet is touching enemy, damage enemy
        for(size_t j = 0; j < player->getActiveBullets().size(); j++) { // All active bullets
            if(enemies[i]->checkCollision(player->getActiveBullets()[j]->getHitboxBounds())) {
                enemies[i]->resetInjuryTimer();
                enemies[i]->changeHealth(-(player->getDmg()));

                // If enemy is not determined
                if(enemies[i]->getState() != 3)
                    enemies[i]->setState(1); // Enraged

                delete player->getActiveBullets()[j];
                player->getActiveBullets().erase(player->getActiveBullets().begin() + j);
            }
        }
    }
}

/**
 * @brief Checks for input required in the state
 * 
 * @param dt deltaTime
 */
void MainMap::updateInput(const float& dt) {
    sf::Vector2f velocity(0.f, 0.f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SHOOT"))) && player->getHandheldType() == 1)
        player->useHandheld(mousePosView);
    else if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SHOOT")))))
        player->stopHandheld(mousePosView);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
        velocity.x = -1;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
        velocity.x = 1;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
        velocity.y = -1;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
        velocity.y = 1;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SWAP_TO_FISTS"))))
        player->setHandheldType(0);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SWAP_TO_GUN_1"))))
        player->setHandheldType(1);

    if(abs(velocity.x) == abs(velocity.y) && velocity.x != 0) {
        velocity.x /= sqrt(2);
        velocity.y /= sqrt(2);
    }

    map->updateCollision(player);
    map->setViewCenter(player->getPosition().x, player->getPosition().y);

    player->move(dt, velocity.x, velocity.y);
    player->updateRotation(mousePosView);
}

/**
 * @brief Updates the upgrade menu
 * 
 */
void MainMap::updateUpgrade()
{
    dmgUp->setPosition(sf::Vector2f(player->getPosition().x - (dmgUp->getSize().x * 3 / 2), player->getPosition().y));
    bullSpeedUp->setPosition(player->getPosition());
    fireRateUp->setPosition(sf::Vector2f(player->getPosition().x + (fireRateUp->getSize().x * 3 / 2) ,player->getPosition().y));

    if(upgrading){
        //TO DO: generate random num and also then include that in if statement for which upgrades will apear
        if(dmgUp->getState()==2){
            player->increaseDmg();
            upgrading=false;
        }else if(fireRateUp->getState()==2){
            player->increasefireRate();
            upgrading=false;
        }else if(bullSpeedUp->getState()==2){
            player->increaseBullSpeed();
            upgrading=false;
        }
    }
}

/**
 * @brief Updates player level bar
 * 
 */
void MainMap::updateLevelBar() {
    levelBar->setPosition(map->getViewCenter().x, map->getViewCenter().y + (player->getHitboxBounds().height * 5.5f));
}

/**
 * @brief Renders the GameState
 * 
 * @param target target window
 */
void MainMap::render(sf::RenderTarget* target) {
    if(!target)
        target = window;

    map->render(*target);
    this->renderEnemies(target);

    if(levelBar)
        levelBar->render(*target);

    player->render(*target);
    
    if(upgrading){
        dmgUp->render(*target);
        fireRateUp->render(*target);
        bullSpeedUp->render(*target);
    }

    tree->render(*target);
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

    if(temp.loadFromFile("Textures/increaseDmgCard.png"))
        textures["increaseDmgCard"] = temp;   

    if(temp.loadFromFile("Textures/increaseBullSpeedCard.png"))
        textures["increaseBullSpeedCard"] = temp;  

    if(temp.loadFromFile("Textures/increaseFireRateCard.png"))
        textures["increaseFireRateCard"] = temp;   

    if(temp.loadFromFile("Textures/tree.png"))
        textures["TREE_1"] = temp;
}

/**
 * @brief Loads all textures into map
 * 
 */
void MainMap::initializeFonts() {
    sf::Font temp;

    if(temp.loadFromFile("Fonts/Sono-Regular.ttf"))
        fonts["SONO_R"] = temp;

    if(temp.loadFromFile("Fonts/Sono-Bold.ttf"))
        fonts["SONO_B"] = temp;
}