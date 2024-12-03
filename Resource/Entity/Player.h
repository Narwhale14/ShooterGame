/**
 * @file Player.h
 * @author Niall Murray and Will Wotherspoon
 * @brief Player class declaration (controllable player)
 * @date 2024-10-23
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Apple.h"

class Player : public Entity {
    public:
        Player(std::map<std::string, sf::Texture>& textures, int x, int y, float s);
        virtual ~Player();

        std::deque<Bullet*>& getActiveBullets() const;
        unsigned short getHandheldType() const;
        void equipLazergun(std::map<std::string, sf::Texture>& textures);
        void equipShotgun(std::map<std::string, sf::Texture>& textures);
        void equipSniper(std::map<std::string, sf::Texture>& textures);

        void increaseDmg();
        void increasefireRate();
        void increaseBullSpeed();

        bool immunityTimerPassed();
        void resetImmunityTimer();

        virtual void useHandheld(const sf::Vector2f& mousePos);
        virtual void stopHandheld(const sf::Vector2f& mousePos);
        void setHandheldType(unsigned short type);

        virtual void updateRotation(const sf::Vector2f& mousePos);
        virtual void update();
        int getDmg();

        virtual void render(sf::RenderTarget& target);
        void addApple(std::map<std::string, sf::Texture> &textures);
        void eatApple();
        void renderAppleBag(sf::RenderTarget &target, sf::Vector2f position);
    private:
        Weapon* handheld;

        sf::Texture* idle;
        sf::Texture* aimed;
        sf::Vector2f handheldPos;

        sf::Clock timeUnderTree;
        int timeUntilImmunityMS;

        short unsigned handheldType;
        enum weaponTypes {hands = 0, gun};

        std::vector<Apple*> appleBag;
        Apple* displayApple;

        sf::Clock pickingClock;
        sf::Clock eatingClock;

        int appleGatherIntervalMS;
        int appleEatingIntervalMS;

        int appleHealingValue;
};

#endif