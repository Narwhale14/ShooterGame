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
        Map(sf::RenderTarget* window, int mapS, float gridS, sf::Color color, sf::Color outlineColor);
        ~Map();

        float getTotalSize() const;
        sf::Vector2f getMapCenter() const;
        sf::Vector2f getCameraSize() const;
        void setViewCenter(float xpos, float ypos);
        
        bool contains(sf::Vector2f objPos) const;
        
        void render(sf::RenderTarget& target);
    private:
        std::vector<std::vector<sf::RectangleShape>> tileMap;
        sf::Color mapColor;
        sf::Color mapOutlineColor;

        sf::View view;
        
        float gridSize;
        int mapSize;
        float totalMapSize;

        void initializeTileMap();
};

#endif