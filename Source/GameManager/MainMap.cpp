/**
 * @file GameState.cpp
 * @author Niall Murray and Will Wotherspoon
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

    spawnIntervalMS = 2000; // Don't go below 1000 MS (1 second) because rand only updates every second
    enemyCap = 20;

    // Map creation
    map = new Map(window, 50, 75.f, sf::Color(59, 104, 38, 255), sf::Color(49, 94, 28, 255));
    spawnTrees(3); // # Multiplier of trees (Scales with map size) (0 for no trees)

    // Player creation
    player = new Player(textures, map->getMapCenter().x, map->getMapCenter().y, 0.075f);
    levelBar = new LevelBar(fonts["SONO_B"], map->getCameraSize().x / 3, map->getCameraSize().y / 12, map->getCameraCenter().x, map->getCameraCenter().y + (map->getCameraSize().y * 0.85f / 2));

    // Apple bag display creation
    appleBagDisplay.setSize(sf::Vector2f(map->getCameraSize().x / 13, map->getCameraSize().y / 13));
    appleBagDisplay.setOrigin(sf::Vector2f(appleBagDisplay.getSize().x / 2, appleBagDisplay.getSize().y / 2));
    appleBagDisplay.setPosition(map->getMapCenter().x, map->getMapCenter().y);
    appleBagDisplay.setFillColor(sf::Color(0, 0, 0, 100));

    appleBagText.setFont(fonts["SONO_R"]);
    appleBagText.setCharacterSize(appleBagDisplay.getGlobalBounds().width / 6);
    appleBagText.setString("Apples");
    appleBagText.setOrigin(appleBagText.getGlobalBounds().width / 2, appleBagText.getGlobalBounds().height / 2);
    appleBagText.setPosition(appleBagDisplay.getPosition().x, appleBagDisplay.getPosition().y - (appleBagDisplay.getSize().y / 3));
    appleBagText.setFillColor(sf::Color::White);

    // Death screen creation
    tint.setSize(sf::Vector2f(map->getCameraSize().x, map->getCameraSize().y));
    tint.setOrigin(tint.getSize().x / 2, tint.getSize().y / 2);
    tint.setPosition(sf::Vector2f(map->getCameraCenter().x, map->getCameraCenter().y));
    tint.setFillColor(sf::Color(0, 0, 0, 100));
    menuButton = new Button(fonts["SONO_R"], "QUIT", sf::Vector2f(map->getCameraSize().x / 6, map->getCameraSize().y / 8), sf::Color(70, 70, 70, 150), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
    menuButton->setPosition(sf::Vector2f(map->getCameraSize().x / 2, map->getCameraSize().y / 2 + menuButton->getSize().y * 1.5f));
    scoreDisplay.setFont(fonts["SONO_B"]);
    scoreDisplay.setCharacterSize(map->getCameraSize().x / 65);
    scoreDisplay.setString("");
    scoreDisplay.setFillColor(sf::Color::White);

    // Upgrade buttons creation
    dmgUp = new Button(sf::Vector2f(map->getCameraSize().x/6, map->getCameraSize().y/2), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), &textures["increaseDmgCard"]);
    fireRateUp = new Button(sf::Vector2f(map->getCameraSize().x/6, map->getCameraSize().y/2), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), &textures["increaseFireRateCard"]);
    bullSpeedUp = new Button(sf::Vector2f(map->getCameraSize().x/6, map->getCameraSize().y/2), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), &textures["increaseBullSpeedCard"]);
    lazerGunSwitch = new Button(sf::Vector2f(map->getCameraSize().x/6, map->getCameraSize().y/2), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), &textures["SWITCHLAZERGUN"]);
    shotGunSwitch = new Button(sf::Vector2f(map->getCameraSize().x/6, map->getCameraSize().y/2), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), &textures["SWITCHSHOTGUN"]);
    sniperSwitch = new Button(sf::Vector2f(map->getCameraSize().x/6, map->getCameraSize().y/2), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200), &textures["SWITCHSNIPER"]);

    //adds the upgrade options to the vector
    for(unsigned int i=0; i<10;i++)
        cardChoice.push_back("DMG");
    for(unsigned int i=0; i<10;i++)
        cardChoice.push_back("FIRERATE");
    for(unsigned int i=0; i<10;i++)
        cardChoice.push_back("BULLSPEED");
    cardChoice.push_back("LAZERGUN");
    cardChoice.push_back("SHOTGUN");
    cardChoice.push_back("SNIPER");

    // Booleans
    upgrading = false;
    finalUp = false;
    normUp = true;
    pen = false;
    playerUnderTree = false;
    playerUnderAppleTree = false;

    minutes = -1;
    seconds = -1;
}

/**
 * @brief Destroy the Main Map:: Main Map object
 * 
 */
MainMap::~MainMap() {
    std::ofstream file("scores.txt", std::ios::out | std::ios::app);
    if(file){
        if(player->isAlive()) {
            minutes = timeElapsed.getElapsedTime().asSeconds() / 60;
            seconds = static_cast<int>(timeElapsed.getElapsedTime().asSeconds()) % 60;
        }

        file << "Level: " << levelBar->getLvl() << " | Extra XP: " << levelBar->getXp() << " | Elapsed Time: " << minutes << ":" << seconds << "\n";
        file.close();
    }
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
    delete menuButton;
}

/**
 * @brief Checks if user wants to quit state
 * 
 */
void MainMap::checkForQuit() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))))
        quit = true;

    if(menuButton->getState() == 2)
        quit = true;
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
        trees.emplace_back(new Tree(textures, scale, (i % 10 + 1)));

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

        if(!map->viewContainsCoords(getRandCoords) || map->getSizeAcross() < 20)
            break;
    }

    enemies.emplace_back(new Enemy(textures, getRandCoords.x, getRandCoords.y));
}

/**
 * @brief Resizes GUI to fit new camera size
 * 
 */
void MainMap::resize(float value) {
    if(map->getCameraScale() != value)
        map->setCameraZoom(value);
    else
        return;

    levelBar->setSize(sf::Vector2f(map->getCameraSize().x / 3, map->getCameraSize().y / 12));

    appleBagDisplay.setSize(sf::Vector2f(map->getCameraSize().x / 13, map->getCameraSize().y / 13));
    appleBagDisplay.setOrigin(sf::Vector2f(appleBagDisplay.getSize().x / 2, appleBagDisplay.getSize().y / 2));
    appleBagText.setCharacterSize(appleBagDisplay.getGlobalBounds().width / 6);
    appleBagText.setOrigin(appleBagText.getGlobalBounds().width / 2, appleBagText.getGlobalBounds().height / 2);
    player->scaleAppleBag(map->getCameraScale());

    tint.setSize(sf::Vector2f(map->getCameraSize().x, map->getCameraSize().y));
    tint.setOrigin(tint.getSize().x / 2, tint.getSize().y / 2);
    menuButton->setSize(sf::Vector2f(map->getCameraSize().x / 6, map->getCameraSize().y / 8));
    scoreDisplay.setCharacterSize(map->getCameraSize().x / 65);
}

/**
 * @brief Updates GameState based on deltaTime and any entities
 * 
 * @param dt deltaTime
 */
void MainMap::update(const float& dt) {
    checkForQuit();
    updateMousePositions();

    tint.setPosition(map->getCameraCenter());
    menuButton->setPosition(sf::Vector2f(map->getCameraCenter().x, map->getCameraCenter().y + menuButton->getSize().y));
    
    if(upgrading&&levelBar->getLvl()!=levelBar->getLevelCap()) {
        updateUpgrade();
    } else if(player->isAlive() && !upgrading) {
        updateMobs(dt);
        updateTrees(dt);

        updateInput(dt);
        player->update();

        if(checkSpawnTimer() && player->isAlive() && enemies.size() < enemyCap)
            spawnEnemy();

        updateLevelBar();
    } else if(!player->isAlive()) {
        menuButton->update(mousePosView);
    }

    appleBagDisplay.setPosition(map->getCameraCenter().x + (levelBar->getSize().x / 2) + appleBagDisplay.getSize().x * 0.75f, map->getCameraCenter().y + (appleBagDisplay.getSize().y * 5.5f));
    appleBagText.setPosition(appleBagDisplay.getPosition().x, appleBagDisplay.getPosition().y - (appleBagDisplay.getSize().y / 3));
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
                enemies[i]->updateWolfSpawnRate(levelBar->getLvl());

                if(!finalUp){
                    if(levelBar->getLvl()==levelBar->getLevelCap())
                        upgrading = true;
                    if(normUp){
                        upgrading=true;
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
                        }else if(Menu1<30){
                            int coin=rand()%20;
                            if(coin==1){
                                Menu2=(rand()%2)+30;
                            }else{
                                Menu2=rand()%19;
                            }
                        }else if(Menu1>29){
                            Menu2=rand()%29;
                        }
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

                /*IMPORTANT: when hitting with multiple bullets with shotgun the game crashes*/
                if(!pen){
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
    playerUnderAppleTree = false;
    for(size_t i = 0; i < trees.size(); i++) {
        if(trees[i]->getHitboxBounds().intersects(player->getHitboxBounds())) {
            trees[i]->setOpacity(150);
            playerUnderTree = true;

            if(trees[i]->getType() == 1)
                playerUnderAppleTree = true;

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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SWAP_TO_HANDS"))))
        player->setHandheldType(0);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SWAP_TO_GUN"))))
        player->setHandheldType(1);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("EAT_APPLE"))))
        player->eatApple();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("PICK_APPLE"))) && playerUnderAppleTree)
        player->addApple(textures);

    // Evens out diagonal movement to be the same velocity as unidirectional velocity
    if(abs(velocity.x) == abs(velocity.y) && velocity.x != 0) {
        velocity.x /= sqrt(2);
        velocity.y /= sqrt(2);
    }

    map->updateCollision(player);
    map->setCameraCenter(player->getPosition().x, player->getPosition().y);

    player->move(dt, velocity.x, velocity.y);
    player->updateRotation(mousePosView);
}

/**
 * @brief Updates the upgrade menu
 * 
 */
void MainMap::updateUpgrade()
{
    //based off random menu1 and menu2 choose the upgrade from cardChoice which containns the upgrade options
    if(cardChoice[Menu1]=="DMG" || cardChoice[Menu2]=="DMG"){
        dmgUp->update(mousePosView);
        if(cardChoice[Menu1]=="DMG")
            dmgUp->setPosition(sf::Vector2f(player->getPosition().x - (dmgUp->getSize().x * 3 / 2), player->getPosition().y));
        if(cardChoice[Menu2]=="DMG")
            dmgUp->setPosition(sf::Vector2f(player->getPosition().x + (dmgUp->getSize().x * 3 / 2), player->getPosition().y));
        if(dmgUp->getState()==2){
            player->increaseDmg();
            upgrading=false;
        }
    }if(cardChoice[Menu1]=="FIRERATE" || cardChoice[Menu2]=="FIRERATE"){
        fireRateUp->update(mousePosView);
        if(cardChoice[Menu1]=="FIRERATE")
            fireRateUp->setPosition(sf::Vector2f(player->getPosition().x - (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(cardChoice[Menu2]=="FIRERATE")
            fireRateUp->setPosition(sf::Vector2f(player->getPosition().x + (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(fireRateUp->getState()==2){
            player->increasefireRate();
            upgrading=false;
        } 
    }if(cardChoice[Menu1]=="BULLSPEED" || cardChoice[Menu2]=="BULLSPEED"){
        bullSpeedUp->update(mousePosView);
        if(cardChoice[Menu1]=="BULLSPEED")
            bullSpeedUp->setPosition(sf::Vector2f(player->getPosition().x - (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(cardChoice[Menu2]=="BULLSPEED")
            bullSpeedUp->setPosition(sf::Vector2f(player->getPosition().x + (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(bullSpeedUp->getState()==2){
            player->increaseBullSpeed();
            upgrading=false;
        }
    }if(cardChoice[Menu1]=="LAZERGUN" || cardChoice[Menu2]=="LAZERGUN"){
        lazerGunSwitch->update(mousePosView);
        if(cardChoice[Menu1]=="LAZERGUN")
            lazerGunSwitch->setPosition(sf::Vector2f(player->getPosition().x - (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(cardChoice[Menu2]=="LAZERGUN")
            lazerGunSwitch->setPosition(sf::Vector2f(player->getPosition().x + (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(lazerGunSwitch->getState()==2){
            player->equipLazergun(textures);
            resize(1);
            upgrading=false;
            normUp=false;
        }
    }if(cardChoice[Menu1]=="SHOTGUN" || cardChoice[Menu2]=="SHOTGUN"){
        shotGunSwitch->update(mousePosView);
        if(cardChoice[Menu1]=="SHOTGUN")
            shotGunSwitch->setPosition(sf::Vector2f(player->getPosition().x - (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(cardChoice[Menu2]=="SHOTGUN")
            shotGunSwitch->setPosition(sf::Vector2f(player->getPosition().x + (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(shotGunSwitch->getState()==2){
            player->equipShotgun(textures);
            resize(1);
            upgrading=false;
            normUp=false;
            pen=true;
        }
    }if(cardChoice[Menu1]=="SNIPER" || cardChoice[Menu2]=="SNIPER"){
        sniperSwitch->update(mousePosView);
        if(cardChoice[Menu1]=="SNIPER")
            sniperSwitch->setPosition(sf::Vector2f(player->getPosition().x - (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(cardChoice[Menu2]=="SNIPER")
            sniperSwitch->setPosition(sf::Vector2f(player->getPosition().x + (fireRateUp->getSize().x * 3 / 2), player->getPosition().y));
        if(sniperSwitch->getState()==2){
            player->equipSniper(textures);
            resize(1.5f);
            upgrading=false;
            normUp=false;
        }
    }
}

/**
 * @brief Updates player level bar
 * 
 */
void MainMap::updateLevelBar() {
    levelBar->setPosition(map->getCameraCenter().x, map->getCameraCenter().y + (map->getCameraSize().y * 0.85f / 2));
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

    renderEnemies(*target);
    player->render(*target);

    renderTrees(*target);

    levelBar->render(*target);

    // Apple bag display
    target->draw(appleBagDisplay);
    target->draw(appleBagText);
    player->renderAppleBag(*target, sf::Vector2f(appleBagDisplay.getPosition().x - (appleBagDisplay.getSize().x / 3), appleBagDisplay.getPosition().y + (appleBagDisplay.getSize().y / 6)));
    
    renderCards(*target);

    if(!player->isAlive()) {
        target->draw(tint);
        scoreText();
        target->draw(scoreDisplay);
        menuButton->render(*target);
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
 * @brief Renders cards
 * 
 * @param target 
 */
void MainMap::renderCards(sf::RenderTarget& target) {
    // Normal upgrading
    if(upgrading && levelBar->getLvl() != levelBar->getLevelCap()){
        if(cardChoice[Menu1]=="DMG"||cardChoice[Menu2]=="DMG")
            dmgUp->render(target);
        if(cardChoice[Menu1]=="FIRERATE"||cardChoice[Menu2]=="FIRERATE")  
            fireRateUp->render(target);
        if(cardChoice[Menu1]=="BULLSPEED"||cardChoice[Menu2]=="BULLSPEED")
            bullSpeedUp->render(target);
        if(cardChoice[Menu1]=="LAZERGUN"||cardChoice[Menu2]=="LAZERGUN")
            lazerGunSwitch->render(target);
        if(cardChoice[Menu1]=="SHOTGUN"||cardChoice[Menu2]=="SHOTGUN")
            shotGunSwitch->render(target);
        if(cardChoice[Menu1]=="SNIPER"||cardChoice[Menu2]=="SNIPER")
            sniperSwitch->render(target);
    }

    // If player reaches max level
    if(upgrading&&levelBar->getLvl() == levelBar->getLevelCap()){
        lazerGunSwitch->setPosition(sf::Vector2f(player->getPosition().x - (dmgUp->getSize().x * 3 / 2), player->getPosition().y));
        lazerGunSwitch->render(target);
        lazerGunSwitch->update(mousePosView);
        if(lazerGunSwitch->getState()==2){
            player->equipLazergun(textures);
            resize(1);
            upgrading=false;
            finalUp=true;
        }
        shotGunSwitch->setPosition(player->getPosition());
        shotGunSwitch->render(target);
        shotGunSwitch->update(mousePosView);
        if(shotGunSwitch->getState()==2){
            player->equipShotgun(textures);
            resize(1);
            upgrading=false;
            finalUp=true;
            pen=true;
        }
        sniperSwitch->setPosition(sf::Vector2f(player->getPosition().x + (dmgUp->getSize().x * 3 / 2), player->getPosition().y));
        sniperSwitch->render(target);
        sniperSwitch->update(mousePosView);
        if(sniperSwitch->getState()==2){
            player->equipSniper(textures);
            resize(1.5f);
            upgrading=false;
            finalUp=true;
        }
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
        textures["OAK_TREE"] = temp;

    if(temp.loadFromFile("Textures/apple_tree.png"))
        textures["APPLE_TREE"] = temp;

    if(temp.loadFromFile("Textures/apple.png"))
        textures["APPLE"] = temp;

    if(temp.loadFromFile("Textures/lazergun.png"))
        textures["LAZERGUN"] = temp;

    if(temp.loadFromFile("Textures/sniper.png"))
        textures["SNIPER"] = temp;
}

/**
 * @brief Loads all texts fonts into map
 * 
 */
void MainMap::initializeFonts() {
    sf::Font temp;

    if(temp.loadFromFile("Fonts/Sono-Regular.ttf"))
        fonts["SONO_R"] = temp;

    if(temp.loadFromFile("Fonts/Sono-Bold.ttf"))
        fonts["SONO_B"] = temp;
}

/**
 * @brief sets the text for the score display at the end of the game
 * 
 */
void MainMap::scoreText()
{
    if(minutes == -1 && seconds == -1) {
        minutes = timeElapsed.getElapsedTime().asSeconds() / 60;
        seconds = static_cast<int>(timeElapsed.getElapsedTime().asSeconds()) % 60;
    }

    std::ostringstream scoreOut;
    scoreOut << "Level: " << levelBar->getLvl() << " | Extra XP: " << levelBar->getXp() << " | Elapsed Time: " << minutes << ":" << seconds << "\n";

    scoreDisplay.setString(scoreOut.str());
    scoreDisplay.setPosition(map->getCameraCenter().x - (scoreDisplay.getGlobalBounds().width / 2),map->getCameraCenter().y);
}