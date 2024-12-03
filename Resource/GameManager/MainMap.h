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

        virtual void checkForQuit();

        virtual void update(const float& dt);
        virtual void render(sf::RenderTarget* target = nullptr);

        void scoreText();
    private:
        Player* player;
        bool playerUnderTree;
        bool playerUnderAppleTree;

        sf::RectangleShape appleBagDisplay;
        sf::Text appleBagText;

        Map* map;
        std::vector<Tree*> trees;
        std::vector<Enemy*> enemies;
        sf::Clock spawnTimer;
        int spawnIntervalMS;
        
        size_t enemyCap;

        LevelBar* levelBar;

        Button* menuButton;
        sf::RectangleShape tint;

        virtual void initializeKeybinds();
        virtual void initializeTextures();
        virtual void initializeFonts();

        bool checkSpawnTimer();
        void spawnTrees(int sparsity);
        void spawnEnemy();
        void resize(float value);

        void updateInput(const float& dt);
        void updateMobs(const float& dt);
        void updateTrees(const float& dt);
        void updateLevelBar();
        void updateUpgrade();

        void renderEnemies(sf::RenderTarget& target);
        void renderTrees(sf::RenderTarget& target);
        void renderCards(sf::RenderTarget& target);

        Button *dmgUp;
        Button *fireRateUp;
        Button *bullSpeedUp;
        Button *lazerGunSwitch;
        Button *shotGunSwitch;
        Button *sniperSwitch;
        bool upgrading;
        bool finalUp;
        bool pen;
        bool normUp;
        int Menu1;
        int Menu2;
        std::map<int,std::string> cardChoice;
        std::vector<std::string> cardChoice2;
        sf::Text scoreDisplay;

        sf::Clock timeElapsed;
        int minutes;
        int seconds;
};

#endif