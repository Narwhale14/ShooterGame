#include "Game.h"

/**
 * @brief Construct a new Game:: Game object
 * Calls to build the window and pushes a new state to the state stack
 */
Game::Game() {
    this->initializeWindow();
    this->initializeKeys();
    this->initializeStates();
}

/**
 * @brief Destroy the Game:: Game object
 * Deletes window (pointer) and cycles through state stack deleting and popping state
 */
Game::~Game() {
    delete this->window;

    while(!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}

/**
 * @brief Runs when user wants to end application
 * 
 */
void Game::endApplication() {
    std::cout << "Ending application\n";
}

/**
 * @brief Updates the dt variable with the time it takes to update and render one frame
 * 
 */
void Game::updateDt() {
    this->dt = this->dtClock.restart().asSeconds();
}

/**
 * @brief Constantly checks for any updates with SFML events
 * 
 */
void Game::updateSFMLEvents() {
    while(this->window->pollEvent(this->sfEvent)) {
        if(this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

/**
 * @brief Updates SFML events through previous function, constantly updates top priority state, checks for when user quits state
 * if 0 states on stack, end program
 */
void Game::update() {
    this->updateSFMLEvents();

    // Updates the state that's first in queue
    if(!this->states.empty()) {
        this->states.top()->update(this->dt);

        if(this->states.top()->getQuit()) {
            // Code that happens when user quits a state
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    } else {
        // Application's end
        this->endApplication();
        this->window->close();
    }
}

/**
 * @brief Renders game through the top priority stack, then posts the window
 * 
 */
void Game::render() {
    this->window->clear();

    // Renders the state first in queue (top of stack)
    if(!this->states.empty()) {
        this->states.top()->render(this->window);
    }

    this->window->display();
}

/**
 * @brief Runs the game
 * 
 */
void Game::run() {
    while(this->window->isOpen()) {
        this->updateDt();
        this->update();
        this->render();
    }
}

/**
 * @brief Creates window
 * 
 */
void Game::initializeWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Test Game C++");
}

/**
 * @brief Initializes all supported keybinds
 *        For visualization, go to < sf::Keyboard >'s definition by right clicking it
 */
void Game::initializeKeys() {
    this->supportedKeys["Escape"] = sf::Keyboard::Key::Escape; // Adds escape to available, supported keys
    this->supportedKeys["A"] = sf::Keyboard::Key::A;
    this->supportedKeys["D"] = sf::Keyboard::Key::D;
    this->supportedKeys["W"] = sf::Keyboard::Key::W;
    this->supportedKeys["S"] = sf::Keyboard::Key::S;

    // Posts all keys in map to console (debugging)
    for(auto i : this->supportedKeys) {
        std::cout << i.first << " " << i.second << "\n";
    }
}
/**
 * @brief Pushes new state to state stack
 * 
 */
void Game::initializeStates() {
    this->states.push(new GameState(this->window, &this->supportedKeys));
}