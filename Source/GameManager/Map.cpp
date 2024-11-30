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
    cameraScale = 1.f;

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
 * @brief returns map size
 * 
 * @return int 
 */
int Map::getSizeAcross() const {
    return mapSize;
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
sf::Vector2f Map::getCameraCenter() const {
    return view.getCenter();
}

/**
 * @brief Returns camera scale
 * 
 * @return float 
 */
float Map::getCameraScale() const {
    return cameraScale;
}

/**
 * @brief Sets camera position
 * 
 * @param pos 
 */
void Map::setCameraCenter(float xpos, float ypos) {
    view.setCenter(xpos, ypos);
}

/**
 * @brief Zooms the camera
 * 
 * @param zoom 
 */
void Map::setCameraZoom(float zoom) {
    view.zoom(zoom);
    cameraScale = zoom;
}

/**
 * @brief Determines if an set of coords is on the map
 * 
 * @param obj 
 * @return true 
 * @return false 
 */
bool Map::viewContainsCoords(const sf::Vector2f& objPos) const {
    return (objPos.x > view.getCenter().x - (view.getSize().x / 2) - gridSize) && (objPos.y > view.getCenter().y - (view.getSize().y / 2) - gridSize)
        && (objPos.x < view.getCenter().x + (view.getSize().x / 2) + gridSize) && (objPos.y < view.getCenter().y + (view.getSize().y / 2) + gridSize);
}

/**
 * @brief Determines if an object is on the map
 * 
 * @param objPos 
 * @param objBounds 
 * @return true 
 * @return false 
 */
bool Map::viewContainsObject(const sf::Vector2f& objPos, const sf::FloatRect& objBounds) const {
    return (objPos.x > view.getCenter().x - (view.getSize().x / 2) - (objBounds.width * 1.5f)) && (objPos.y > view.getCenter().y - (view.getSize().y / 2) - (objBounds.height * 1.5f))
        && (objPos.x < view.getCenter().x + (view.getSize().x / 2) + (objBounds.width * 1.5f)) && (objPos.y < view.getCenter().y + (view.getSize().y / 2) + (objBounds.height * 1.5f));
}

/**
 * @brief Returns whether a pos is inside the map
 * 
 * @param objPos 
 * @return true 
 * @return false 
 */
bool Map::mapContains(const sf::Vector2f& objPos, const sf::FloatRect& objBounds) const {
    if(objPos.x > objBounds.width / 2 && objPos.x < totalMapSize - objBounds.width && objPos.y > objBounds.width / 2 && objPos.y < totalMapSize - objBounds.width )
        return true;

    return false;
}

/**
 * @brief Checks if passed entity is in map and limits it to it's bounds
 * 
 * @param entity 
 */
void Map::updateCollision(Entity* entity) {
    if(entity->getPosition().x < 0 + entity->getHitboxBounds().width / 2) // Left wall
        entity->setPosition(sf::Vector2f(entity->getHitboxBounds().width / 2, entity->getPosition().y));
    else if(entity->getPosition().x > this->getTotalSize() - entity->getHitboxBounds().width / 2) // Right wall
        entity->setPosition(sf::Vector2f(this->getTotalSize() - entity->getHitboxBounds().width / 2, entity->getPosition().y));
    if(entity->getPosition().y < 0 + entity->getHitboxBounds().height / 2) // Top wall
        entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getHitboxBounds().height / 2));
    else if(entity->getPosition().y > this->getTotalSize() - entity->getHitboxBounds().height / 2) // Bottom wall
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
            if(this->viewContainsObject(tileMap[x][y].getPosition(), tileMap[x][y].getGlobalBounds()))
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