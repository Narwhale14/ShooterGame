/**
 * @file Map.cpp
 * @author Niall Murray
 * @brief Map class implementation
 * @date 2024-11-12
 */

#include "../../Resource/GameManager/Map.h"

Map::Map(int mapS, float gridS, sf::Color color, sf::Color outlineColor) {
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

    std::cout << "Map size x: " << totalMapSize << " y: " << totalMapSize << std::endl;

    initializeTileMap();
}

Map::~Map() {
    
}

float Map::getTotalSize() const {
    return totalMapSize;
}

void Map::update(const float& dt) {

}

void Map::render(sf::RenderTarget& target) {
    for(int x = 0; x < mapSize; x++) {
        for(int y = 0; y < mapSize; y++) {
            target.draw(tileMap[x][y]);
        }
    }
}

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