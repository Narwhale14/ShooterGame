/**
 * @file LevelBar.h
 * @author Niall Murray
 * @brief LevelBar class declaration
 * @date 2024-11-18
 */

#ifndef LEVELBAR_H
#define LEVELBAR_H

#include <iostream>
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
        LevelBar(float size_x, float size_y, float pos_x, float pos_y);
        ~LevelBar();

        int getXp() const;

        void setPosition(float pos_x, float pos_y);
        bool addXp(int incoming);

        void render(sf::RenderTarget& target);
    private:
        int level;
        int xp;

        int requiredXpToLevelUp;
        float maxMainBarSize;
        float levelRatio;

        sf::RectangleShape* barBack;
        sf::RectangleShape* barMain;

        sf::Color color;
};

#endif