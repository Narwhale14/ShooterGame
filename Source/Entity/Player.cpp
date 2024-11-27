/**
 * @file Player.cpp
 * @author Niall and Will
 * @brief 
 * @version 0.1
 * @date 2024-11-26
 */
#include "../../Resource/Entity/Player.h"

/**
 * @brief Construct a new Player:: Player object
 * 
 * @param x initial xpos
 * @param y initial ypos
 * @param texture texture
 */
Player::Player(std::map<std::string, sf::Texture>& textures, int x, int y, float s) {
    idle = &textures["PLAYER_NORMAL"];
    aimed = &textures["PLAYER_AIMED"];

    createSprite(idle, s);
    setPosition(sf::Vector2f(x, y));

    createHitbox(sprite, sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2, sf::Color::Green);
    createHealthBar(hitbox->getGlobalBounds().width, hitbox->getGlobalBounds().height, sprite->getPosition().x, sprite->getPosition().y);

    handheld = new Pistol(textures);
    handheldType = gun;

    maxVelocity = 240;

    timeUntilImmunityMS = 1000;
}

/**
 * @brief Returns list of bullets
 * 
 * @return std::deque<Bullet*>& 
 */
std::deque<Bullet*>& Player::getActiveBullets() const {
    return handheld->getBulletList();
}

/**
 * @brief Gets the player handheld type
 * 
 * @return unsigned short 
 */
unsigned short Player::getHandheldType() const {
    return handheldType;
}

/**
 * @brief Destroy the Player:: Player object
 * 
 */
Player::~Player() { 
    delete handheld;
    for(unsigned i=appleBag.size();i>0;i--){
        delete appleBag[i];
        appleBag.pop_back();
    }
}

/**
 * @brief Tracks front of player to the cursor
 * 
 * @param mousePos coords of the cursor relative to the window
 */
void Player::updateRotation(const sf::Vector2f& mousePos) {
    float dist_x = mousePos.x - sprite->getPosition().x;
    float dist_y = mousePos.y - sprite->getPosition().y;

    angle = ((atan2(dist_y, dist_x)) * 180 / 3.14);

    weaponPos.x = sprite->getPosition().x + (hitbox->getGlobalBounds().width / 1.1f) * cos(angle * 3.14 / 180);
    weaponPos.y = sprite->getPosition().y + (hitbox->getGlobalBounds().height / 1.1f) * sin(angle * 3.14 / 180);
    
    sprite->setRotation(angle - 90);

    handheld->update(weaponPos);
    handheld->rotateWeapon(mousePos);
}

void Player::useHandheld(const sf::Vector2f& mousePos) {
    handheld->fire(mousePos, weaponPos);
}

void Player::stopHandheld(const sf::Vector2f& mousePos)
{
    handheld->stopFire(mousePos, weaponPos);
}

/**
 * @brief Returns whether player is safe under tree or not
 * 
 * @return true 
 * @return false 
 */
bool Player::immunityTimerPassed() {
    return timeUnderTree.getElapsedTime().asMilliseconds() > timeUntilImmunityMS;
}

/**
 * @brief Resets timer
 * 
 */
void Player::resetImmunityTimer() {
    timeUnderTree.restart();
}

/**
 * @brief Sets the player handheld type
 * 
 * @param type 
 */
void Player::setHandheldType(unsigned short type) {
    handheldType = type;
}

/**
 * @brief Posts sprite to window
 * 
 * @param target 
 */
void Player::render(sf::RenderTarget& target) {

    if(healthBar)
        healthBar->render(target);

    handheld->renderBull(target);

    if(handheld && handheldType == gun)
        handheld->render(target);

    if(sprite)
        target.draw(*sprite);

    if(hitbox)
        hitbox->render(target);
}

/**
 * @brief Updates player and it's sprite
 * 
 */
void Player::update() {
    healthBar->setPosition(hitbox->getPosition().x, hitbox->getPosition().y + (hitbox->getGlobalBounds().height));
    hitbox->update();

    switch(handheldType) {
        case empty:
            changeSprite(idle);
            multiplier = 1.25f;
            break;
        case gun:
            changeSprite(aimed);
            multiplier = 1;
            break;
        default:
            changeSprite(idle);
            break;
    }
}

/**
 * @brief increase the current weapons damage if not an ultimate weapon
 * 
 */
void Player::increaseDmg()
{
    handheld->increaseDmg();
}

/**
 * @brief increase the current weapons rate of fire(the time between each shot) if not an ultimate weapon
 * 
 */
void Player::increasefireRate()
{
    handheld->increaseFireRate();
}

/**
 * @brief increase the current weapons bullet speed(the distance traveled per time) if not an ultimate weapon
 * 
 */
void Player::increaseBullSpeed()
{
    handheld->increaseBullSpeed();
}

/**
 * @brief returns the amount of damage the current weapon does
 * 
 * @return int the damage number
 */
int Player::getDmg()
{
    return handheld->getDmg();
}

/**
 * @brief equips the ultimate weapon lazergun upgrades no longer possible
 * 
 * @param textures textures for the weapon
 */
void Player::equipLazergun(std::map<std::string, sf::Texture>& textures)
{
    delete handheld;
    handheld=new Lazergun(textures);
    handheldType=gun;
}

/**
 * @brief equips the ultimate weapon shotgun upgrades no longer possible
 * 
 * @param textures textures for the weapon
 */
void Player::equipShotgun(std::map<std::string, sf::Texture>& textures)
{
    delete handheld;
    handheld=new Shotgun(textures);
    handheldType=gun;
}

/**
 * @brief equips the ultimate weapon sniper upgrades no longer possible
 * 
 * @param textures textures for the weapon
 */
void Player::equipSniper(std::map<std::string, sf::Texture>& textures)
{
    delete handheld;
    handheld = new Pistol(textures);
    handheld->setDmg(1000);
    handheld->setFireRate(1);
    handheld->setBullSpeed(35);
    handheldType=gun;
}

/**
 * @brief adds an apple to the players inventory the apple can be eaten for health
 * 
 * @param textures texture for the apple
 */
void Player::addApple(std::map<std::string, sf::Texture> &textures)
{
    tm=cl.getElapsedTime();
    if(appleBag.size()<10 && tm.asSeconds()>1){
        int luck=rand()%10;
        if(luck==1){
            appleBag.push_back(new Apple(textures["APPLE"]));
        }
        cl.restart();
    }
}

/**
 * @brief removes an apple from the players inventory and increases the players health
 * 
 */
void Player::eatApple()
{
    tm=cl.getElapsedTime();
    if(appleBag.size()>0 && tm.asSeconds()>1){
        delete appleBag.back();
        appleBag.pop_back();
        changeHealth(10);
        cl.restart();
    }
}

/**
 * @brief displays the apple on the screen if player has any in inventory
 * 
 * @param target
 */
void Player::renderApple(sf::RenderTarget &target, sf::Vector2f view)
{
    if(appleBag.size()>0){
        for(unsigned i=0;i<appleBag.size();i++){
            appleBag[i]->setPosition({view.x+390+(i*8),view.y+456});
            appleBag[i]->render(target);
        }
    }
}