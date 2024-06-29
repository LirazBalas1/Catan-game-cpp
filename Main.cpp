#include <iostream>
#include <ctime>
#include "Game.hpp"

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Initialize and start the game
    Game game;
    game.start();

    return 0;
}
