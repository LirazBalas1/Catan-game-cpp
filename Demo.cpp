#include <iostream>
#include "Game.hpp"

void demo() {
    std::cout << "Demo: Initial Placement" << std::endl;
    Game game;
    auto player1 = game.getPlayer(0);
    auto player2 = game.getPlayer(1);
    auto player3 = game.getPlayer(2);

    // Initial points after the initial placements
    std::cout << "Player 1 initial points: " << player1->getPoints() << std::endl;
    std::cout << "Player 2 initial points: " << player2->getPoints() << std::endl;
    std::cout << "Player 3 initial points: " << player3->getPoints() << std::endl;

    std::cout << "\nDemo: Dice Roll" << std::endl;
    int roll = game.rollDice();
    std::cout << "Rolled: " << roll << std::endl;

    std::cout << "\nDemo: Build Structures" << std::endl;
    player1->addResource(Tile::WOOD, 10);
    player1->addResource(Tile::BRICK, 10);
    player1->addResource(Tile::SHEEP, 10);
    player1->addResource(Tile::GRAIN, 10);
    player1->addResource(Tile::ORE, 10);

    if (player1->buildStructure(Player::SETTLEMENT)) {
        std::cout << "Player 1 built a settlement." << std::endl;
    }
    if (player1->buildStructure(Player::ROAD)) {
        std::cout << "Player 1 built a road." << std::endl;
    }
    if (player1->buildStructure(Player::CITY)) {
        std::cout << "Player 1 built a city." << std::endl;
    }

    std::cout << "\nDemo: Trade Resources" << std::endl;
    player2->addResource(Tile::WOOD, 10);
    player2->addResource(Tile::BRICK, 10);

    if (player1->tradeResourceWithPlayer(Tile::WOOD, Tile::BRICK, 1, player2)) {
        std::cout << "Player 1 traded wood for brick with Player 2." << std::endl;
    }

    std::cout << "\nDemo: Development Cards" << std::endl;
    if (player1->buyDevelopmentCard()) {
        std::cout << "Player 1 bought a development card." << std::endl;
    }
    if (player1->useDevelopmentCard()) {
        std::cout << "Player 1 used a development card." << std::endl;
    }

    std::cout << "\nDemo: Edge Cases" << std::endl;
    // Building without resources
    if (!player1->buildStructure(Player::SETTLEMENT)) {
        std::cout << "Player 1 couldn't build a settlement (not enough resources)." << std::endl;
    }

    // Trading without enough resources
    if (!player1->tradeResourceWithPlayer(Tile::SHEEP, Tile::ORE, 1, player2)) {
        std::cout << "Player 1 couldn't trade sheep for ore (not enough resources)." << std::endl;
    }

    // Discarding resources when over limit
    player1->addResource(Tile::WOOD, 10);
    player1->addResource(Tile::BRICK, 10);
    player1->addResource(Tile::SHEEP, 10);
    player1->addResource(Tile::GRAIN, 10);
    player1->addResource(Tile::ORE, 10);
    player1->discardResources(25);
    std::cout << "Player 1 discarded resources when over limit." << std::endl;

    // Maximum resource limit
    player1->addResource(Tile::WOOD, 100);
    player1->addResource(Tile::BRICK, 100);
    std::cout << "Player 1's resources after adding a lot: Wood: " << player1->getResource(Tile::WOOD) << ", Brick: " << player1->getResource(Tile::BRICK) << std::endl;

    // Resource scarcity
    player1->addResource(Tile::WOOD, 1);
    player1->addResource(Tile::BRICK, 1);
    if (player1->buildStructure(Player::ROAD)) {
        std::cout << "Player 1 built a road with minimal resources." << std::endl;
    }
    if (!player1->buildStructure(Player::ROAD)) {
        std::cout << "Player 1 couldn't build another road due to resource scarcity." << std::endl;
    }
}

int main() {
    demo();
    return 0;
}