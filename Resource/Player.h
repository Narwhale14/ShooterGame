/**
 * @file Player.h
 * @author Niall Murray
 * @brief Player class declaration (controllable player)
 * @date 2024-10-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
    public:
        Player(float x = 0, float y = 0, sf::Texture* texture = nullptr);
        ~Player();
        
        virtual void pointToCursor(const sf::Vector2f mousePos);
    private:
        
};

#endif