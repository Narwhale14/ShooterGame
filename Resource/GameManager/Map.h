/**
 * @file Map.h
 * @author Niall Murray
 * @brief Map class declaration
 * @date 2024-11-12
 */

#ifndef MAP_H
#define MAP_H

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

class Map {
    public:
        Map(int mapS, float gridS, sf::Color color, sf::Color outlineColor);
        ~Map();

        float getTotalSize() const;

        void update(const float& dt);
        void render(sf::RenderTarget& target);
    private:
        std::vector<std::vector<sf::RectangleShape>> tileMap;
        sf::Color mapColor;
        sf::Color mapOutlineColor;
        
        float gridSize;
        int mapSize;
        float totalMapSize;

        void initializeTileMap();
};

#endif