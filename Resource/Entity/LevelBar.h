/**
 * @file LevelBar.h
 * @author Niall Murray
 * @brief LevelBar class declaration
 * @date 2024-11-18
 */

#ifndef LEVELBAR_H
#define LEVELBAR_H

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <cmath>
#include <map>
#include <deque>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class LevelBar {
    public:
        LevelBar(sf::Font& font, float size_x, float size_y, float pos_x, float pos_y);
        ~LevelBar();

        int getXp() const;
        int getLvl() const;
        int getLevelCap() const;
        sf::Vector2f getSize() const;

        void setPosition(float pos_x, float pos_y);
        void setSize(const sf::Vector2f& size);
        bool addXp(int incoming);

        void render(sf::RenderTarget& target);
        
    private:
        int level;
        int xp;

        int requiredXpToLevelUp;
        float maxMainBarSize;
        float levelRatio;
        int levelCap;

        sf::RectangleShape barBack;
        sf::RectangleShape barMain;

        sf::Text text;
        sf::Font font;

        sf::Color color;
};

#endif