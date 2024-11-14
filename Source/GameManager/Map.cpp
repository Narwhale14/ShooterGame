/**
 * @file Map.cpp
 * @author Niall Murray
 * @brief Map class implementation
 * @date 2024-11-12
 */

#include "../../Resource/GameManager/Map.h"

/**
 * @brief Construct a new Map:: Map object
 * 
 * @param mapS size
 * @param gridS size of each tile
 * @param color color of map
 * @param outlineColor color of outline
 */
Map::Map(sf::RenderTarget* window, int mapS, float gridS, sf::Color color, sf::Color outlineColor) {
    if(gridS >= 0.f)
        gridSize = gridS;
    else
        gridSize = 0.f;

    if(mapS >= 0)
        mapSize = mapS;
    else
        mapSize = 0;

    mapColor = color;
    mapOutlineColor = outlineColor;
    totalMapSize = gridSize * mapSize;

    view.setSize(window->getSize().x, window->getSize().y);
    view.setCenter(totalMapSize / 2, totalMapSize / 2);

    initializeTileMap();
}

/**
 * @brief Destroy the Map:: Map object
 * 
 */
Map::~Map() {
    
}

/**
 * @brief returns map size
 * 
 * @return float 
 */
float Map::getTotalSize() const {
    return totalMapSize;
}

/**
 * @brief Returns the view size
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Map::getCameraSize() const {
    return view.getSize();
}

/**
 * @brief Moves view
 * 
 * @param dir_x 
 * @param dir_y 
 */
void Map::moveCamera(float dir_x, float dir_y) {
    view.move(dir_x, dir_y);
}

/**
 * @brief draws map to window
 * 
 * @param target 
 */
void Map::render(sf::RenderTarget& target) {
    target.setView(view);
    for(int x = 0; x < mapSize; x++) {
        for(int y = 0; y < mapSize; y++) {
            target.draw(tileMap[x][y]);
        }
    }
}

/**
 * @brief creates map
 * 
 */
void Map::initializeTileMap() {
    tileMap.resize(mapSize, std::vector<sf::RectangleShape>());

    for(int x = 0; x < mapSize; x++) {
        tileMap[x].resize(mapSize, sf::RectangleShape());

        for(int y = 0; y < mapSize; y++) {
            tileMap[x][y].setSize(sf::Vector2f(gridSize, gridSize));
            tileMap[x][y].setFillColor(mapColor);
            tileMap[x][y].setOutlineThickness(5.f);
            tileMap[x][y].setOutlineColor(mapOutlineColor);
            tileMap[x][y].setPosition(x * gridSize, y * gridSize);
        }
    }
}