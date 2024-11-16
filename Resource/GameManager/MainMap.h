/**
 * @file GameState.h
 * @author Niall Murray
 * @brief GameState class declaration file. This class takes the State template and finishes construction of it's pure virtual functions. Any object of this class will contain
 *        it's scene worth of entities, textures, whatever is visible
 * @date 2024-10-23
 */
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "MainMenu.h"

class MainMap : public State {
    public:
        MainMap(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
        virtual ~MainMap();

        void move(const float& dt, const float dir_x, const float dir_y, const float movementSpeed);
        void updateInput(const float& dt);

        virtual void checkForQuit();

        void update(const float& dt);
        void render(sf::RenderTarget* target = nullptr);
    private:
        Player* player;
        Enemy* enemy;

        Map* map;
        sf::View view;
        
        std::vector<Enemy*> enemies;
        sf::Clock spawnTimer;
        int spawnIntervalMS;

        void initializeKeybinds();
        void initializeTextures();

        void updateDamageCollisions();
        void updateMobs(const float& dt, bool spawn);
        void renderEnemies(sf::RenderTarget* target);

        bool checkSpawnTimer();
};

#endif