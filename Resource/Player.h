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
        Player(float x = 0, float y = 0, std::map<std::string, sf::Texture>* textures = nullptr);
        ~Player();
        
        virtual void pointToCursor(const sf::Vector2f mousePos);
        virtual void useHandheld(const sf::Vector2f mousePos);

        virtual void render(sf::RenderTarget* target);
    private:
        std::string handheldType;
        Weapon* handheld;   
};

#endif