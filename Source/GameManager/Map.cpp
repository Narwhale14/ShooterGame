/**
 * @file Map.cpp
 * @author Niall Murray
 * @brief Map class implementation
 * @date 2024-11-12
 */

#include "../../Resource/GameManager/Map.h"

Map::Map() {
    gridSizeF = 100.f;

    gridUnit.setSize(sf::Vector2f(gridSizeF, gridSizeF));
}

Map::~Map() {

}

void Map::update(const float& dt) {
    
}

void Map::render(sf::RenderTarget& target) {

}