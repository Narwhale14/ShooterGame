/**
 * @file Map.h
 * @author Niall Murray
 * @brief Map class declaration
 * @date 2024-11-12
 */

#ifndef MAP_H
#define MAP_H

#include "../Entity/Entity.h"

class Map {
    public:
        Map(sf::RenderTarget* window, int mapS, float gridS, sf::Color color, sf::Color outlineColor);
        ~Map();

        float getTotalSize() const;
        float getGridSize() const;
        float getSizeAcross() const;
        sf::Vector2f getMapCenter() const;
        sf::Vector2f getCameraSize() const;
        sf::Vector2f getViewCenter() const;
        void setViewCenter(float xpos, float ypos);
        
        bool viewContains(sf::Vector2f objPos) const;
        bool borderIsTouching(sf::Vector2f objPos) const;

        void updateCollision(Entity* entity);
        
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