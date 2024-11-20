/**
 * @file Game.cpp
 * @author Niall Murray
 * @brief Game class initialization
 * @date 2024-10-29
 */

#include "../../Resource/GameManager/Game.h"

/**
 * @brief Construct a new Game:: Game object
 * Calls to build the window and pushes a new state to the state stack
 */
Game::Game() {
    // Both of these are essentially just functions that purposefully clean up the constructor
    initializeWindow();
    initializeKeys();
    sf::Clock c;
    
    states.push(new MainMap(window, &supportedKeys));
    states.push(new MainMenu(window, &supportedKeys));
}

/**
 * @brief Destroy the Game:: Game object
 * Deletes window (pointer) and cycles through state stack deleting and popping state
 */
Game::~Game() {
    delete window;

    while(!states.empty()) {
        delete states.top();
        states.pop();
    }
}

/**
 * @brief Updates SFML events through previous function, constantly updates top priority state, checks for when user quits state
 * if 0 states on stack, end program
 */
void Game::update() {
    dt = dtClock.restart().asSeconds();

    while(window->pollEvent(sfEvent)) {
        if(sfEvent.type == sf::Event::Closed)
            window->close();
    }

    // Updates the state that's first in queue
    if(!states.empty()) {
        states.top()->update(dt);

        if(states.top()->getQuit()) {
            // Code that happens when user quits a state
            states.top()->endState();
            delete states.top();
            states.pop();
        } else if(states.top()->getFlush()) {
            window->close();
        }
    } else {
        // Application's end
        window->close();
    }
}

/**
 * @brief Renders game through the top priority stack, then posts the window
 * 
 */
void Game::render() {
    window->clear(sf::Color(50, 50, 50));

    // Renders the state first in queue (top of stack)
    if(!states.empty()) {
        states.top()->render(window);
    }

    window->display();
}

/**
 * @brief Runs the game
 * 
 */
void Game::run() {
    while(window->isOpen()) {
        update();
        render();
    }
}

/**
 * @brief Creates window from config file
 * 
 */
void Game::initializeWindow() {
    std::ifstream inputFile("Config/window.ini");
    
    // Variables
    windowBounds.width = 1920;
    windowBounds.height = 1080;
    std::string title = "None";
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;

    if(inputFile.is_open()) {
        std::getline(inputFile, title);
        inputFile >> windowBounds.width >> windowBounds.height;
        inputFile >> framerate_limit;
        inputFile >> vertical_sync_enabled;
    } else {
        exit(1);
    }

    inputFile.close();

    window = new sf::RenderWindow(windowBounds, title);
    window->setFramerateLimit(framerate_limit);
    window->setVerticalSyncEnabled(vertical_sync_enabled);
}

/**
 * @brief Initializes all supported keybinds
 *        For visualization, go to <sf::Keyboard>'s definition by right clicking it
 */
void Game::initializeKeys() {
    std::ifstream inputFile("Config/supported_keys.ini");

    if(inputFile.is_open()) {
        std::string key;
        int key_value = 0;

        while(inputFile >> key >> key_value) {
            supportedKeys[key] = key_value;
        }
    }

    inputFile.close();
}