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
        int getSizeAcross() const;
        sf::Vector2f getMapCenter() const;
        sf::Vector2f getCameraSize() const;
        sf::Vector2f getCameraCenter() const;
        float getCameraScale() const;
        void setCameraCenter(float xpos, float ypos);
        void setCameraZoom(float zoom);
        
        bool viewContainsCoords(const sf::Vector2f& objPos) const;
        bool viewContainsObject(const sf::Vector2f& objPos, const sf::FloatRect& objBounds) const;
        bool mapContains(const sf::Vector2f& objPos, const sf::FloatRect& objBounds) const;

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
        float cameraScale;

        void initializeTileMap();
};

#endif