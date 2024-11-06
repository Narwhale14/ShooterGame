/**
 * @file main.cpp
 * @author Niall Murray
 * @brief Main file
 * @date 2024-10-23
 * 
 * @complile: g++ -g -Wall Source/Entity/ *.cpp Source/GameManager/ *.cpp Source/Weapons/ *.cpp Source/main.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
 * (For debugging purpose. Remove spaces before asterisks)
 */
#include "../Resource/GameManager/Game.h"

int main() {
    Game game;
    
    game.run();

    return 0;
}