/**
 * @file weapon.h
 * @author William Wotherspoon
 * @brief Weapon class declaration for that will be used to create the games weapons
 * @version 0.1
 * @date 2024-10-24
 */

#ifndef WEAPON_H
#define WEAPON_H

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

class Weapon{
    public:
        Weapon();
        virtual ~Weapon();

        bool getFiringStatus();
        void setFiringStatus(bool status);

        void render(sf::RenderTarget* target);
        void createSprite(sf::Texture* texture);
    protected:
        sf::Texture* texture;
        sf::Sprite* sprite;

        bool firing;
};

#endif