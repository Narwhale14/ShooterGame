/**
 * @file Player.h
 * @author Niall Murray
 * @brief Player class declaration (controllable player)
 * @date 2024-10-23
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
    public:
        Player(std::map<std::string, sf::Texture>& textures, int x, int y, float s);
        virtual ~Player();

        virtual bool useHandheld(const sf::Vector2f mousePos);
        virtual bool stopHandheld(const sf::Vector2f mousePos);

        virtual void render(sf::RenderTarget& target);
        virtual void updateRotation(const sf::Vector2f mousePos);
        virtual void update();
    private:
        Weapon* handheld;

        sf::Texture* idle;
        sf::Texture* aimed;

        sf::Vector2f weaponPos;

        short unsigned handheldType;
        enum weaponTypes {empty = 0, pistol};
};

#endif