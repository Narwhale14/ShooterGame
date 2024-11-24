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

void Player::increaseDmg()
{
    handheld->increaseDmg();
}

void Player::increasefireRate()
{
    handheld->increaseFireRate();
}

void Player::increaseBullSpeed()
{
    handheld->increaseBullSpeed();
}

int Player::getDmg()
{
    return handheld->getDmg();
}

void Player::equipLazergun(std::map<std::string, sf::Texture>& textures)
{
    delete handheld;
    handheld=new Lazergun(textures);
}

void Player::equipShotgun(std::map<std::string, sf::Texture>& textures)
{
    delete handheld;
    handheld=new Shotgun(textures);
}