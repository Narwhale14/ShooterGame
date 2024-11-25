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
        Tree(sf::Texture& texture, float scale);
        virtual ~Tree();

        void setOpacity(int opacity);
        void setRotation(int angle);
        void setPosition(const sf::Vector2f& pos);

        sf::Vector2f getPosition() const;

        virtual void update();
        virtual void render(sf::RenderTarget& target);
    private:

};

#endif