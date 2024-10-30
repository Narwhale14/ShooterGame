/**
 * @file HealthBar.cpp
 * @author Niall Murray
 * @brief Health bar class implementation
 * @date 2024-10-30
 */

#include "../../Resource/Entity/HealthBar.h"

HealthBar::HealthBar(float size_x, float size_y) {
    if(size_x > 0 && size_y > 0) {
        barBack.setSize(sf::Vector2f(size_x, size_y));
    } else {
        barBack.setSize(sf::Vector2f(10, 10));
    }

    barBack.setFillColor(sf::Color(128, 128, 128));
}

HealthBar::~HealthBar() {

}

void HealthBar::setPosition(float pos_x, float pos_y) {
    barBack.setPosition(pos_x, pos_y);
}

void HealthBar::update(const float& dt) {

}

void HealthBar::render(sf::RenderTarget& target) {

}