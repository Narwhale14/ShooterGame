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
        Tree(sf::Texture& texture, float size);
        virtual ~Tree();

        void setPosition(sf::Vector2f pos);

        virtual void update();
        virtual void render(sf::RenderTarget& target);
    private:

};

#endif