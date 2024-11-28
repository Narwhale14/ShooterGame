/**
 * @file Tree.h
 * @author Niall Murray
 * @brief Tree class declaration
 * @date 2024-11-21
 */

#include "Object.h"

#ifndef TREE_H
#define TREE_H

class Tree : public Object {
    public:
        Tree(std::map<std::string, sf::Texture>& textures, float scale, int seed);
        virtual ~Tree();

        void setOpacity(int opacity);
        void setRotation(int angle);
        void setPosition(const sf::Vector2f& pos);

        sf::Vector2f getPosition() const;
        short unsigned getType() const;

        virtual void update();
        virtual void render(sf::RenderTarget& target);
    private:
        float appleTreeChance;

        enum type {oak = 0, apple};
        unsigned short type;

        short unsigned getRandomTreeType();
};

#endif