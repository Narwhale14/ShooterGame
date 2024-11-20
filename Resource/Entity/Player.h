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

        void increaseDmg();
        void increasefireRate();
        void increaseBullSpeed();

        virtual void useHandheld(const sf::Vector2f& mousePos);
        virtual void stopHandheld(const sf::Vector2f& mousePos);

        virtual void updateRotation(const sf::Vector2f& mousePos);
        virtual void update();

        virtual void render(sf::RenderTarget& target);
    private:
        Weapon* handheld;

        sf::Texture* idle;
        sf::Texture* aimed;
        sf::Vector2f weaponPos;

        short unsigned handheldType;
        enum weaponTypes {empty = 0, gun};
};

#endif