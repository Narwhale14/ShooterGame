/**
 * @file Map.h
 * @author Niall Murray
 * @brief Map class declaration
 * @date 2024-11-12
 */

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

#ifndef MAP_H
#define MAP_H

class Map {
    public:

    private:
        std::vector<std::vector<sf::RectangleShape>> tileMap;
        
        float gridSizeF;
        unsigned gridSizeU;
};

#endif