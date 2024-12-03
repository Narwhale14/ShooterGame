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
        int getDamage() const;

        bool isCloseTo(const sf::Vector2f& objPos, const sf::Vector2f& viewSize);

        bool relaxationTimerPassed();
        bool biteTimerPassed();
        bool injuryTimerPassed();

        void setState(short unsigned state);
        void resetInjuryTimer();

        void relax();
        void track(const sf::Vector2f& playerPosition);
        void follow(const float& dt, const sf::Vector2f& playerPosition);

        virtual void render(sf::RenderTarget& target);
        virtual void update();
        void updateWolfSpawnRate(int playerLevel);
    private:
        enum type {wolf = 0, bull};
        short unsigned type;

        enum state {relaxed = 0, enraged, scared};
        short unsigned state;

        sf::Clock relaxationTimer;
        int relaxationTimeMS;

        sf::Clock biteTimer;
        int biteTimeMS;

        sf::Clock injuryTimer;
        int injuryTimeMS;
        float injurySpeedMultiplier;
        bool hasBeenRestarted; // Literally only used once but it makes me less annoyed

        int xpValue;
        int killHealthValue;
        int sightDistance;
        int damage;

        int fearSpeedMultiplier;

        int angleDeviation;
        int relaxedAngle;

        float wolfSpawnRate;

        short unsigned generateEnemyType();
};

#endif