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
 * @brief Returns the individual grid size
 * 
 * @return float 
 */
float Map::getGridSize() const {
    return gridSize;
}

/**
 * @brief Returns the map center
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Map::getMapCenter() const {
    return sf::Vector2f(totalMapSize / 2, totalMapSize / 2);
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
 * @brief Gets view center
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Map::getViewCenter() const {
    return view.getCenter();
}

/**
 * @brief Sets camera position
 * 
 * @param pos 
 */
void Map::setViewCenter(float xpos, float ypos) {
    view.setCenter(xpos, ypos);
}

/**
 * @brief Determines if an obj is on the map
 * 
 * @param obj 
 * @return true 
 * @return false 
 */
bool Map::viewContains(sf::Vector2f objPos) const {
    return (objPos.x > view.getCenter().x - (view.getSize().x / 2) - gridSize) && (objPos.y > view.getCenter().y - (view.getSize().y / 2) - gridSize)
        && (objPos.x < view.getCenter().x + (view.getSize().x / 2)) && (objPos.y < view.getCenter().y + (view.getSize().y / 2) );
}

/**
 * @brief Determins if an obj is touching map border
 * 
 * @param objPos 
 * @return true 
 * @return false 
 */
bool Map::borderIsTouching(sf::Vector2f objPos) const {
    sf::Vector2f objGridPos(static_cast<int>(objPos.x / gridSize) + 1, static_cast<int>(objPos.y / gridSize) + 1);

    if(objGridPos.x == 1 || objGridPos.x == mapSize || objGridPos.y == 1 || objGridPos.y == mapSize)
        return true;
    
    return false;
}

/**
 * @brief Checks if passed entity is in map and limits it to it's bounds
 * 
 * @param entity 
 */
void Map::containInMap(Entity* entity) {
    // If player is touching wall
    if(entity->getPosition().x < 0 + entity->getHitboxBounds().width / 2) // Left wall
        entity->setPosition(sf::Vector2f(entity->getHitboxBounds().width / 2, entity->getPosition().y));
    if(entity->getPosition().y < 0 + entity->getHitboxBounds().height / 2) // Top wall
        entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getHitboxBounds().height / 2));
    if(entity->getPosition().x > this->getTotalSize() - entity->getHitboxBounds().width / 2) // Right wall
        entity->setPosition(sf::Vector2f(this->getTotalSize() - entity->getHitboxBounds().width / 2, entity->getPosition().y));
    if(entity->getPosition().y > this->getTotalSize() - entity->getHitboxBounds().height / 2) // Bottom wall
        entity->setPosition(sf::Vector2f(entity->getPosition().x, this->getTotalSize() - entity->getHitboxBounds().height / 2));
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
            if(this->viewContains(tileMap[x][y].getPosition()))
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