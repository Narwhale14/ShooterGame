/**
 * @file Enemy.h
 * @author Niall Murray
 * @brief Enemy class declarations
 * @date 2024-10-29
 */

#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class Enemy : public Entity {
    public:
        Enemy(std::map<std::string, sf::Texture>& textures, int x, int y);
        virtual ~Enemy();

        int getXPValue() const;
        int getSightDistance() const;
        int getKillHealthValue() const;
        short unsigned getType() const;
        short unsigned getState() const;
        bool relaxationTimerPassed() const;
        bool biteTimerPassed();

        void setState(short unsigned state);
        void restartRelaxationTimer();

        void relax();
        void track(sf::Vector2f playerPosition);
        void follow(const float& dt, sf::Vector2f playerPosition);

        virtual void render(sf::RenderTarget& target);
        virtual void update();
    private:
        enum type {wolf = 0, bull};
        short unsigned type;

        enum state {relaxed = 0, enraged, scared, determined};
        short unsigned state;

        sf::Clock relaxationTimer;
        int relaxationTimeMS;

        sf::Clock biteTimer;
        int biteTimeMS;

        int xpValue;
        int killHealthValue;
        int sightDistance;

        float fearSpeedMultiplier;
        int thresholdHeath;

        short unsigned generateEnemyType();
};

#endif