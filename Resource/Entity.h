/**
 * @file Entity.h
 * @author Niall Murray
 * @brief Entity class declaration (base class for any moving mob)
 * @date 2024-10-23
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <cmath>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Entity {
    public:
        Entity(sf::Texture* texture = nullptr);
        virtual ~Entity();

        void createSprite(sf::Texture* texture);
        virtual void move(const float& dt, const float dir_x, const float dir_y);

        virtual void update(const float& dt);
        virtual void render(sf::RenderTarget* target);
    protected:
        sf::Texture* texture;
        sf::Sprite* sprite;

        float movementSpeed;
        float angle;
};

#endif