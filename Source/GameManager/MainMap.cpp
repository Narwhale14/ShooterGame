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
    enemyCap = 30;

    map = new Map(window, 40, 75.f, sf::Color(59, 104, 38, 255), sf::Color(49, 94, 28, 255));
    spawnTrees(3); // # Multiplier of trees (Scales with map size) (0 for no trees)

    player = new Player(textures, map->getMapCenter().x, map->getMapCenter().y, 0.075f);
    levelBar = new LevelBar(fonts["SONO_B"], window->getSize().x / 3, window->getSize().y / 12, map->getViewCenter().x, map->getViewCenter().y + (map->getCameraSize().y * 0.85f / 2));

    dmgUp = new Button(sf::Vector2f(window->getSize().x/6, window->getSize().y/2), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), &textures["increaseDmgCard"]);
    fireRateUp = new Button(sf::Vector2f(window->getSize().x/6, window->getSize().y/2), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), &textures["increaseFireRateCard"]);
    bullSpeedUp = new Button(sf::Vector2f(window->getSize().x/6, window->getSize().y/2), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), &textures["increaseBullSpeedCard"]);
    lazerGunSwitch = new Button(sf::Vector2f(window->getSize().x/6, window->getSize().y/2), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), &textures["SWITCHLAZERGUN"]);
    shotGunSwitch = new Button(sf::Vector2f(window->getSize().x/6, window->getSize().y/2), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), &textures["SWITCHSHOTGUN"]);
    sniperSwitch = new Button(sf::Vector2f(window->getSize().x/6, window->getSize().y/2), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), &textures["SWITCHSNIPER"]);


    upgrading=false;
    finalUp=false;
    playerUnderTree = false;
    //adds the upgrade options to the vector
    for(unsigned int i=0; i<10;i++)
        cardChoice2.push_back("DMG");
    for(unsigned int i=0; i<10;i++)
        cardChoice2.push_back("FIRERATE");
    for(unsigned int i=0; i<10;i++)
        cardChoice2.push_back("BULLSPEED");
    cardChoice2.push_back("LAZERGUN");
    cardChoice2.push_back("SHOTGUN");
    cardChoice2.push_back("SNIPER");
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

    while(!trees.empty()) {
        delete trees[trees.size() - 1];
        trees.pop_back();
    } 

    delete dmgUp;
    delete fireRateUp;
    delete bullSpeedUp;
    delete map;
    delete lazerGunSwitch;
    delete shotGunSwitch;
    delete sniperSwitch;
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
 * @brief Spawns an amount of trees all around the map
 * 
 * @param amount 
 */
void MainMap::spawnTrees(int sparsity) {
    size_t amount = sparsity * pow(map->getSizeAcross(), 2) / 200;

    // HARD CAP TO AVOID FUNCTION INFINITELY SEARCHING FOR NON-EXISTENT USABLE SPACE (still REALLY dense just won't crash)
    if(amount > pow(map->getSizeAcross(), 2) / 7)
        amount = pow(map->getSizeAcross(), 2) / 7;

    float scale = 1.f;
    int angle = 0;

    sf::Vector2f getRandCoords;
    int range = map->getTotalSize();

    for(size_t i = 0; i < amount; i++) {
        // 0.15 - 0.34 scale
        scale = (rand() % 20 + 15) / 100.f;
        trees.emplace_back(new Tree(textures["TREE_1"], scale));

        angle = (rand() % 360 + 1);
        trees[i]->setRotation(angle);

        while(true) {
            getRandCoords.x = rand() % range;
            getRandCoords.y = rand() % range;

            trees[i]->setPosition(sf::Vector2f(getRandCoords.x, getRandCoords.y));
            trees[i]->update();

            bool intersecting = false;
            for(size_t j = 0; j < trees.size() - 1; j++) {
                if(trees[i]->getHitboxBounds().intersects(trees[j]->getHitboxBounds()))
                    intersecting = true;
            }

            // Keeps tree in map
            if(map->mapContains(getRandCoords, trees[i]->getHitboxBounds()) && !intersecting)
                break;
        }
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
        int maxRange = map->getTotalSize() - map->getGridSize();
        int minRange = map->getGridSize();

        getRandCoords.x = rand() % maxRange + minRange;
        getRandCoords.y = rand() % maxRange + minRange;

        if(!map->viewContainsCoords(getRandCoords) || map->getSizeAcross() < 15)
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
        updateUpgrade();
    } else if(player->isAlive() && !upgrading) {
        updateMobs(dt);
        updateTrees(dt);

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
            if(levelBar->addXp(enemies[i]->getXPValue())){
                if(!finalUp){
                    upgrading = true;
                    //generates the the random menu choices
                    Menu1=rand() % 32;
                    if(Menu1<10){
                        Menu2=(rand()%22)+10;
                    }else if(Menu1<20){
                        int coin=rand()%2;
                        if(coin==1){
                            Menu2=rand()%9;
                        }else{
                           Menu2=(rand()%12)+20; 
                        }
                    }else if(Menu1>29){
                        Menu2=rand()%29;
                    }
                }
            }
            player->changeHealth(enemies[i]->getKillHealthValue());
            
            continue;
        }

        // (STATE SETTING) Determines the enemy's state based on promiximity to player
        if(enemies[i]->getDistanceTo(player->getPosition()) < map->getGridSize() * enemies[i]->getSightDistance() || enemies[i]->getState() != 0) {
            // Enraged if not idle
            if(enemies[i]->getState() == 0)
                enemies[i]->setState(1);

            // If enemy is off screen for longer than a set despawn timer
            if(!map->viewContainsObject(enemies[i]->getPosition(), enemies[i]->getHitboxBounds()) && enemies[i]->relaxationTimerPassed())
                enemies[i]->setState(0);

            // If enemy re-spots player emerging from the tree
            if(!playerUnderTree && enemies[i]->getState() == 2)
                enemies[i]->setState(1);

            // (ENEMY MOVEMENT) Behold, the great conditional
            if(((!enemies[i]->checkCollision(player->getHitboxBounds()) && enemies[i]->getState() != 0) 
                && ((!playerUnderTree || enemies[i]->isCloseTo(player->getPosition(), map->getCameraSize())) || (playerUnderTree && !player->immunityTimerPassed())))
            || (playerUnderTree && !(enemies[i]->getState() == 1))) {
                map->updateCollision(enemies[i]);

                enemies[i]->track(player->getPosition());
                enemies[i]->follow(dt, player->getPosition());
            }
        }
        
        enemies[i]->update();

        // If enemy is touching player and is alive, damage player
        if(player->checkCollision(enemies[i]->getHitboxBounds()) && enemies[i]->biteTimerPassed())
            player->changeHealth(-enemies[i]->getDamage());

        // If a bullet is touching enemy, damage enemy
        for(size_t j = 0; j < player->getActiveBullets().size(); j++) { // All active bullets
            if(enemies[i]->checkCollision(player->getActiveBullets()[j]->getHitboxBounds())) {

                /*IMPORTANT: when hitting with multiple bullets the game crashes*/
                if(!finalUp){
                    delete player->getActiveBullets()[j];
                    player->getActiveBullets().erase(player->getActiveBullets().begin() + j);
                }

                enemies[i]->resetInjuryTimer();
                enemies[i]->changeHealth(-(player->getDmg()));

                // If enemy is not determined
                if(enemies[i]->getState() != 3 && enemies[i]->getState() != 2)
                    enemies[i]->setState(1); // Enraged

                if(playerUnderTree && !enemies[i]->isCloseTo(player->getPosition(), map->getCameraSize()))
                    enemies[i]->setState(2);
            }
        }
    }
}

/**
 * @brief Updates trees on map
 * 
 * @param dt 
 */
void MainMap::updateTrees(const float& dt) {
    playerUnderTree = false;
    for(size_t i = 0; i < trees.size(); i++) {
        if(trees[i]->getHitboxBounds().intersects(player->getHitboxBounds())) {
            trees[i]->setOpacity(150);
            playerUnderTree = true;
        } else {
            trees[i]->setOpacity(255);
        }
    }

    if(!playerUnderTree)
        player->resetImmunityTimer();
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
    //based off random menu1 choose the upgrade from cardChoice which conatians the upgrade options
    if(cardChoice2[Menu1]=="DMG" || cardChoice2[Menu2]=="DMG"){
        dmgUp->update(mousePosView);
        if(cardChoice2[Menu1]=="DMG")
            dmgUp->setPosition(sf::Vector2f(player->getPosition().x - (dmgUp->getSize().x * 3 / 2), player->getPosition().y));
        if(cardChoice2[Menu2]=="DMG")
            dmgUp->setPosition(sf::Vector2f(player->getPosition().x + (dmgUp->getSize().x * 3 / 2), player->getPosition().y));
        if(dmgUp->getState()==2){
            player->increaseDmg();
            upgrading=false;
        }
    }if(cardChoice2[Menu1]=="FIRERATE" || cardChoice2[Menu2]=="FIRERATE"){
        fireRateUp->update(mousePosView);
        if(cardChoice2[Menu1]=="FIRERATE")
            fireRateUp->setPosition(sf::Vector2f(player->getPosition().x - (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(cardChoice2[Menu2]=="FIRERATE")
            fireRateUp->setPosition(sf::Vector2f(player->getPosition().x + (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(fireRateUp->getState()==2){
            player->increasefireRate();
            upgrading=false;
        } 
    }if(cardChoice2[Menu1]=="BULLSPEED" || cardChoice2[Menu2]=="BULLSPEED"){
        bullSpeedUp->update(mousePosView);
        if(cardChoice2[Menu1]=="BULLSPEED")
            bullSpeedUp->setPosition(sf::Vector2f(player->getPosition().x - (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(cardChoice2[Menu2]=="BULLSPEED")
            bullSpeedUp->setPosition(sf::Vector2f(player->getPosition().x + (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(bullSpeedUp->getState()==2){
            player->increaseBullSpeed();
            upgrading=false;
        }
    }if(cardChoice2[Menu1]=="LAZERGUN" || cardChoice2[Menu2]=="LAZERGUN"){
        lazerGunSwitch->update(mousePosView);
        if(cardChoice2[Menu1]=="LAZERGUN")
            lazerGunSwitch->setPosition(sf::Vector2f(player->getPosition().x - (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(cardChoice2[Menu2]=="LAZERGUN")
            lazerGunSwitch->setPosition(sf::Vector2f(player->getPosition().x + (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(lazerGunSwitch->getState()==2){
            player->equipLazergun(textures);
            upgrading=false;
            finalUp=true;
        }

    }if(cardChoice2[Menu1]=="SHOTGUN" || cardChoice2[Menu2]=="SHOTGUN"){
        shotGunSwitch->update(mousePosView);
        if(cardChoice2[Menu1]=="SHOTGUN")
            shotGunSwitch->setPosition(sf::Vector2f(player->getPosition().x - (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(cardChoice2[Menu2]=="SHOTGUN")
            shotGunSwitch->setPosition(sf::Vector2f(player->getPosition().x + (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(shotGunSwitch->getState()==2){
            player->equipShotgun(textures);
            upgrading=false;
            finalUp=true;
        }
    }if(cardChoice2[Menu1]=="SNIPER" || cardChoice2[Menu2]=="SNIPER"){
        sniperSwitch->update(mousePosView);
        if(cardChoice2[Menu1]=="SNIPER")
            sniperSwitch->setPosition(sf::Vector2f(player->getPosition().x - (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(cardChoice2[Menu2]=="SNIPER")
            sniperSwitch->setPosition(sf::Vector2f(player->getPosition().x + (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(sniperSwitch->getState()==2){
            player->equipSniper(textures);
            upgrading=false;
            finalUp=true;
        }
    }
}

/**
 * @brief Updates player level bar
 * 
 */
void MainMap::updateLevelBar() {
    levelBar->setPosition(map->getViewCenter().x, map->getViewCenter().y + (map->getCameraSize().y * 0.85f / 2));
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
    this->renderEnemies(*target);

    player->render(*target);
    this->renderTrees(*target);

    if(levelBar)
        levelBar->render(*target);
    
    if(upgrading){
        if(cardChoice2[Menu1]=="DMG"||cardChoice2[Menu2]=="DMG")
            dmgUp->render(*target);
        if(cardChoice2[Menu1]=="FIRERATE"||cardChoice2[Menu2]=="FIRERATE")  
            fireRateUp->render(*target);
        if(cardChoice2[Menu1]=="BULLSPEED"||cardChoice2[Menu2]=="BULLSPEED")
            bullSpeedUp->render(*target);
        if(cardChoice2[Menu1]=="LAZERGUN"||cardChoice2[Menu2]=="LAZERGUN")
            lazerGunSwitch->render(*target);
        if(cardChoice2[Menu1]=="SHOTGUN"||cardChoice2[Menu2]=="SHOTGUN")
            shotGunSwitch->render(*target);
        if(cardChoice2[Menu1]=="SNIPER"||cardChoice2[Menu2]=="SNIPER")
            sniperSwitch->render(*target);
    }
}

/**
 * @brief Renders active enemies
 * 
 * @param target 
 */
void MainMap::renderEnemies(sf::RenderTarget& target) {
    for(size_t i = 0; i < enemies.size(); i++) {
        if(enemies[i] != nullptr && enemies[i]->isAlive() && map->viewContainsObject(enemies[i]->getPosition(), enemies[i]->getHitboxBounds()))
            enemies[i]->render(target);
    }
}

/**
 * @brief Renders active trees
 * 
 * @param target 
 */
void MainMap::renderTrees(sf::RenderTarget& target) {
    for(size_t i = 0; i < trees.size(); i++) {
        if(trees[i] != nullptr && map->viewContainsObject(trees[i]->getPosition(), trees[i]->getHitboxBounds()))
            trees[i]->render(target);
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

    if(temp.loadFromFile("Textures/pellet.png"))
        textures["PELLET"] = temp;

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

    if(temp.loadFromFile("Textures/lazerBull.png"))
        textures["LAZERBULL"] = temp;  

    if(temp.loadFromFile("Textures/switchLazerGun.png"))
        textures["SWITCHLAZERGUN"] = temp;  
    
    if(temp.loadFromFile("Textures/switchShotGun.png"))
        textures["SWITCHSHOTGUN"] = temp; 

    if(temp.loadFromFile("Textures/switchSniper.png"))
        textures["SWITCHSNIPER"] = temp;   

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