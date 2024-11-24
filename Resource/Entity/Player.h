/**
 * @file Player.h
 * @author Niall Murray
 * @brief Player class declaration (controllable player)
 * @date 2024-10-23
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "../GameManager/Button.h"

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
    private:
        Weapon* handheld;

        sf::Texture* idle;
        sf::Texture* aimed;
        sf::Vector2f weaponPos;

        sf::Clock timeUnderTree;
        int timeUntilImmunityMS;

        short unsigned handheldType;
        enum weaponTypes {empty = 0, gun};
};

#endif