#include "Game.hpp"
#include <limits>
#include <iostream>
#include <cstdlib>

Game::Game() {
    board = std::make_shared<Board>();
    players.push_back(std::make_shared<Player>("Player 1"));
    players.push_back(std::make_shared<Player>("Player 2"));
    players.push_back(std::make_shared<Player>("Player 3"));
    robber = Robber();

    for (auto& player : players) {
        player->addResource(Tile::WOOD, 1);
        player->addResource(Tile::BRICK, 1);
        player->addResource(Tile::SHEEP, 1);
        player->addResource(Tile::GRAIN, 1);
        player->addResource(Tile::ORE, 1);
    }

    longestRoadPlayer = nullptr;
    largestArmyPlayer = nullptr;
}

void Game::start() {
    initialPlacement();
    while (!isGameOver()) {
        for (size_t i = 0; i < players.size(); ++i) {
            auto& player = players[i];
            if (i == 0) { // Human player's turn
                takeHumanTurn(player);
            } else { // AI player's turn
                takeAITurn(player);
            }
            if (isGameOver()) break;
        }
    }
    announceWinner();
}

std::shared_ptr<Player> Game::getPlayer(int index) const {
    return players.at(static_cast<std::vector<std::shared_ptr<Player>>::size_type>(index));
}

int Game::rollDice() const {
    return (rand() % 6 + 1) + (rand() % 6 + 1);
}
void Game::initialPlacement() {
    for (int round = 0; round < 2; ++round) {
        for (size_t i = 0; i < players.size(); ++i) {
            auto& player = players[i];
            if (i == 0) { // Human player's turn
                placeHumanInitialSettlement(player);
                placeHumanInitialRoad(player);
            } else { // AI player's turn
                placeAIInitialSettlement(player);
                placeAIInitialRoad(player);
            }
        }
    }
}

void Game::placeHumanInitialSettlement(std::shared_ptr<Player> player) {
    std::cout << player->getName() << ", place your settlement.\n";
    // Get user input for settlement placement
    // Ensure that the placement follows the game rules
    // For demonstration, we'll assume valid placement
    if (player->buildStructure(Player::SETTLEMENT)) {
        std::cout << player->getName() << " built a settlement.\n";
    }
}

void Game::placeHumanInitialRoad(std::shared_ptr<Player> player) {
    std::cout << player->getName() << ", place your road.\n";
    // Get user input for road placement
    // Ensure that the placement follows the game rules
    // For demonstration, we'll assume valid placement
    if (player->buildStructure(Player::ROAD)) {
        std::cout << player->getName() << " built a road.\n";
    }
}

void Game::placeAIInitialSettlement(std::shared_ptr<Player> player) {
    // AI logic for placing initial settlement
    if (player->buildStructure(Player::SETTLEMENT)) {
        std::cout << player->getName() << " built a settlement.\n";
    }
}

void Game::placeAIInitialRoad(std::shared_ptr<Player> player) {
    // AI logic for placing initial road
    if (player->buildStructure(Player::ROAD)) {
        std::cout << player->getName() << " built a road.\n";
    }
}
void Game::displayAvailableActions(std::shared_ptr<Player> player) const {
    std::cout << "\nAvailable actions:\n";
    if (player->canBuildStructure(Player::SETTLEMENT)) {
        std::cout << "1. Build Settlement\n";
    } else {
        std::cout << "1. Build Settlement (not enough resources)\n";
    }
    if (player->canBuildStructure(Player::ROAD)) {
        std::cout << "2. Build Road\n";
    } else {
        std::cout << "2. Build Road (not enough resources)\n";
    }
    if (player->canBuildStructure(Player::CITY)) {
        std::cout << "3. Build City\n";
    } else {
        std::cout << "3. Build City (not enough resources)\n";
    }
    std::cout << "4. Trade with Bank\n";
    if (player->canBuyDevelopmentCard()) {
        std::cout << "5. Buy Development Card\n";
    } else {
        std::cout << "5. Buy Development Card (not enough resources)\n";
    }
    if (player->hasDevelopmentCard()) {
        std::cout << "6. Use Development Card\n";
    } else {
        std::cout << "6. Use Development Card (no development card available)\n";
    }
    std::cout << "7. Trade with Player\n";
    std::cout << "8. End Turn\n";
}

void Game::takeHumanTurn(std::shared_ptr<Player> player) {
    std::cout << "Your turn, " << player->getName() << ".\n";
    int diceRoll = rollDice();
    std::cout << "You rolled a " << diceRoll << ".\n";

    distributeResources(diceRoll);
    displayResources(player);

    if (diceRoll == 7) {
        moveRobber(player);
        discardResources(player);
    }

    bool endTurn = false;
    while (!endTurn) {
        displayAvailableActions(player);
        std::cout << "Enter the number of your choice: ";
        int choice;
        std::cin >> choice;

        while (std::cin.fail() || choice < 1 || choice > 8) {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid choice. Please enter a number between 1 and 8: ";
            std::cin >> choice;
        }

        switch (choice) {
            case 1:
                if (player->buildStructure(Player::SETTLEMENT)) {
                    std::cout << "You built a settlement.\n";
                } else {
                    std::cout << "You couldn't build a settlement.\n";
                }
                break;
            case 2:
                if (player->buildStructure(Player::ROAD)) {
                    std::cout << "You built a road.\n";
                    updateLongestRoad(player);
                } else {
                    std::cout << "You couldn't build a road.\n";
                }
                break;
            case 3:
                if (player->buildStructure(Player::CITY)) {
                    std::cout << "You built a city.\n";
                } else {
                    std::cout << "You couldn't build a city.\n";
                }
                break;
            case 4:
                tradeWithBank(player);
                break;
            case 5:
                if (player->buyDevelopmentCard()) {
                    std::cout << "You bought a development card.\n";
                } else {
                    std::cout << "You couldn't buy a development card.\n";
                }
                break;
            case 6:
                if (player->useDevelopmentCard()) {
                    std::cout << "You used a development card.\n";
                    moveRobber(player);
                    updateLargestArmy(player);
                }
                break;
            case 7:
                tradeWithPlayer(player);
                break;
            case 8:
                endTurn = true;
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    }
}

void Game::distributeResources(int diceRoll) {
    for (auto& tile : board->getTiles()) {
        if (tile->getNumber() == diceRoll && tile != robber.getCurrentTile()) {
            for (auto& player : players) {
                player->addResource(tile->getType(), 1);
            }
        }
    }
}

void Game::displayResources(std::shared_ptr<Player> player) const {
    std::cout << player->getName() << " resources: "
              << "Wood: " << player->getResource(Tile::WOOD) << ", "
              << "Brick: " << player->getResource(Tile::BRICK) << ", "
              << "Sheep: " << player->getResource(Tile::SHEEP) << ", "
              << "Grain: " << player->getResource(Tile::GRAIN) << ", "
              << "Ore: " << player->getResource(Tile::ORE) << "\n";
}

bool Game::tradeWithBank(std::shared_ptr<Player> player) {
    std::cout << "\nChoose resource to give: \n";
    std::cout << "1. Wood\n";
    std::cout << "2. Brick\n";
    std::cout << "3. Sheep\n";
    std::cout << "4. Grain\n";
    std::cout << "5. Ore\n";
    std::cout << "Enter the number of your choice: ";
    int giveChoice;
    std::cin >> giveChoice;

    while (std::cin.fail() || giveChoice < 1 || giveChoice > 5) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please enter a number between 1 and 5: ";
        std::cin >> giveChoice;
    }

    std::cout << "\nChoose resource to receive: \n";
    std::cout << "1. Wood\n";
    std::cout << "2. Brick\n";
    std::cout << "3. Sheep\n";
    std::cout << "4. Grain\n";
    std::cout << "5. Ore\n";
    std::cout << "Enter the number of your choice: ";
    int receiveChoice;
    std::cin >> receiveChoice;

    while (std::cin.fail() || receiveChoice < 1 || receiveChoice > 5) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please enter a number between 1 and 5: ";
        std::cin >> receiveChoice;
    }

    Tile::ResourceType giveResource = static_cast<Tile::ResourceType>(giveChoice - 1);
    Tile::ResourceType receiveResource = static_cast<Tile::ResourceType>(receiveChoice - 1);

    if (player->tradeResourceWithBank(giveResource, receiveResource, 1)) {
        std::cout << "Trade successful.\n";
        return true;
    } else {
        std::cout << "Trade failed.\n";
        return false;
    }
}

bool Game::tradeWithPlayer(std::shared_ptr<Player> player) {
    std::cout << "\nChoose player to trade with (1 or 2): \n";
    int playerIndex;
    std::cin >> playerIndex;

    while (std::cin.fail() || playerIndex < 1 || playerIndex > static_cast<int>(players.size()) || players[static_cast<std::vector<std::shared_ptr<Player>>::size_type>(playerIndex - 1)] == player) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please enter a valid player number: ";
        std::cin >> playerIndex;
    }

    std::shared_ptr<Player> otherPlayer = players[static_cast<std::vector<std::shared_ptr<Player>>::size_type>(playerIndex - 1)];

    std::cout << "\nChoose resource to give: \n";
    std::cout << "1. Wood\n";
    std::cout << "2. Brick\n";
    std::cout << "3. Sheep\n";
    std::cout << "4. Grain\n";
    std::cout << "5. Ore\n";
    std::cout << "Enter the number of your choice: ";
    int giveChoice;
    std::cin >> giveChoice;

    while (std::cin.fail() || giveChoice < 1 || giveChoice > 5) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please enter a number between 1 and 5: ";
        std::cin >> giveChoice;
    }

    std::cout << "\nChoose resource to receive: \n";
    std::cout << "1. Wood\n";
    std::cout << "2. Brick\n";
    std::cout << "3. Sheep\n";
    std::cout << "4. Grain\n";
    std::cout << "5. Ore\n";
    std::cout << "Enter the number of your choice: ";
    int receiveChoice;
    std::cin >> receiveChoice;

    while (std::cin.fail() || receiveChoice < 1 || receiveChoice > 5) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please enter a number between 1 and 5: ";
        std::cin >> receiveChoice;
    }

    Tile::ResourceType giveResource = static_cast<Tile::ResourceType>(giveChoice - 1);
    Tile::ResourceType receiveResource = static_cast<Tile::ResourceType>(receiveChoice - 1);

    if (player->tradeResourceWithPlayer(giveResource, receiveResource, 1, otherPlayer)) {
        std::cout << "Trade successful.\n";
        return true;
    } else {
        std::cout << "Trade failed.\n";
        return false;
    }
}

void Game::updateLongestRoad(std::shared_ptr<Player> player) {
    int longestRoad = player->calculateLongestRoad();
    if (longestRoad >= 5) {
        if (!longestRoadPlayer || longestRoad > longestRoadPlayer->calculateLongestRoad()) {
            longestRoadPlayer = player;
            std::cout << player->getName() << " now has the longest road.\n";
        }
    }
}

void Game::updateLargestArmy(std::shared_ptr<Player> player) {
    int armySize = player->getArmySize();
    if (armySize >= 3) {
        if (!largestArmyPlayer || armySize > largestArmyPlayer->getArmySize()) {
            largestArmyPlayer = player;
            std::cout << player->getName() << " now has the largest army.\n";
        }
    }
}
void Game::moveRobber(std::shared_ptr<Player> player) {
    int tileIndex = rand() % static_cast<int>(board->getTiles().size());
    robber.moveRobber(board->getTile(static_cast<std::vector<std::shared_ptr<Tile>>::size_type>(tileIndex)));
    std::cout << player->getName() << " moved the robber to tile " << tileIndex << ".\n";

    // Rob a player whose settlement/city borders the new robber location
    for (auto& victim : players) {
        if (victim != player && // Ensure the victim is not the current player
            (victim->getResource(Tile::WOOD) > 0 || 
             victim->getResource(Tile::BRICK) > 0 || 
             victim->getResource(Tile::SHEEP) > 0 || 
             victim->getResource(Tile::GRAIN) > 0 || 
             victim->getResource(Tile::ORE) > 0)) {
            robPlayer(player, victim);
            break; // Rob only one player
        }
    }
}

void Game::robPlayer(std::shared_ptr<Player> robber, std::shared_ptr<Player> victim) {
    std::vector<Tile::ResourceType> resourcesToSteal;
    for (Tile::ResourceType type : {Tile::WOOD, Tile::BRICK, Tile::SHEEP, Tile::GRAIN, Tile::ORE}) {
        if (victim->getResource(type) > 0) {
            resourcesToSteal.push_back(type);
        }
    }
    if (!resourcesToSteal.empty()) {
        Tile::ResourceType stolenResource = resourcesToSteal[static_cast<std::vector<Tile::ResourceType>::size_type>(rand() % static_cast<int>(resourcesToSteal.size()))];
        victim->addResource(stolenResource, -1); // Decrease resource from victim
        robber->addResource(stolenResource, 1);  // Increase resource for robber
        std::cout << robber->getName() << " stole 1 " << Tile::getResourceName(stolenResource) << " from " << victim->getName() << ".\n";
    }
}



void Game::discardResources(std::shared_ptr<Player> player) {
    int totalResources = player->getTotalResources();
    if (totalResources > 7) {
        int discardCount = totalResources / 2;
        player->discardResources(discardCount);
        std::cout << player->getName() << " discarded " << discardCount << " resources.\n";
    }
}

bool Game::isGameOver() const {
    for (const auto& player : players) {
        if (player->getPoints() >= 10) {
            return true;
        }
    }
    return false;
}

void Game::announceWinner() const {
    std::shared_ptr<Player> winner = nullptr;
    int maxPoints = 0;
    for (const auto& player : players) {
        if (player->getPoints() > maxPoints) {
            maxPoints = player->getPoints();
            winner = player;
        }
    }
    if (winner) {
        std::cout << winner->getName() << " wins the game with " << maxPoints << " points!\n";
    }
}

void Game::takeAITurn(std::shared_ptr<Player> player) {
    std::cout << player->getName() << "'s turn (AI).\n";
    int diceRoll = rollDice();
    std::cout << "Rolled a " << diceRoll << ".\n";

    distributeResources(diceRoll);
    displayResources(player);

    if (diceRoll == 7) {
        moveRobber(player);
        discardResources(player);
    }

    // AI logic for deciding actions based on level
    switch (player->getAILevel()) {
        case Player::AILevel::EASY:
            takeEasyAITurn(player);
            break;
        case Player::AILevel::MEDIUM:
            takeMediumAITurn(player);
            break;
        case Player::AILevel::HARD:
            takeHardAITurn(player);
            break;
    }
}
void Game::takeEasyAITurn(std::shared_ptr<Player> player) {
    // Simplistic AI logic
    if (player->getResource(Tile::WOOD) >= 1 && player->getResource(Tile::BRICK) >= 1) {
        if (player->buildStructure(Player::ROAD)) {
            std::cout << player->getName() << " built a road.\n";
            updateLongestRoad(player);
        }
    }

    if (player->getResource(Tile::WOOD) >= 1 && player->getResource(Tile::BRICK) >= 1 && 
        player->getResource(Tile::SHEEP) >= 1 && player->getResource(Tile::GRAIN) >= 1) {
        if (player->buildStructure(Player::SETTLEMENT)) {
            std::cout << player->getName() << " built a settlement.\n";
        }
    }

    if (player->getResource(Tile::ORE) >= 3 && player->getResource(Tile::GRAIN) >= 2) {
        if (player->buildStructure(Player::CITY)) {
            std::cout << player->getName() << " built a city.\n";
        }
    }

    if (player->getResource(Tile::ORE) >= 1 && player->getResource(Tile::SHEEP) >= 1 && 
        player->getResource(Tile::GRAIN) >= 1) {
        if (player->buyDevelopmentCard()) {
            std::cout << player->getName() << " bought a development card.\n";
        }
    }

    if (player->useDevelopmentCard()) {
        std::cout << player->getName() << " used a development card.\n";
        moveRobber(player);
        updateLargestArmy(player);
    }
}

void Game::takeMediumAITurn(std::shared_ptr<Player> player) {
    // More advanced AI logic
    // Prioritize city building if possible
    if (player->getResource(Tile::ORE) >= 3 && player->getResource(Tile::GRAIN) >= 2) {
        if (player->buildStructure(Player::CITY)) {
            std::cout << player->getName() << " built a city.\n";
            return;
        }
    }

    // Otherwise, try to build settlements
    if (player->getResource(Tile::WOOD) >= 1 && player->getResource(Tile::BRICK) >= 1 && 
        player->getResource(Tile::SHEEP) >= 1 && player->getResource(Tile::GRAIN) >= 1) {
        if (player->buildStructure(Player::SETTLEMENT)) {
            std::cout << player->getName() << " built a settlement.\n";
            return;
        }
    }
    // Otherwise, build roads to expand territory
    if (player->getResource(Tile::WOOD) >= 1 && player->getResource(Tile::BRICK) >= 1) {
        if (player->buildStructure(Player::ROAD)) {
            std::cout << player->getName() << " built a road.\n";
            updateLongestRoad(player);
            return;
        }
    }

    // Try to buy development cards if other options are not viable
    if (player->getResource(Tile::ORE) >= 1 && player->getResource(Tile::SHEEP) >= 1 && 
        player->getResource(Tile::GRAIN) >= 1) {
        if (player->buyDevelopmentCard()) {
            std::cout << player->getName() << " bought a development card.\n";
        }
    }

    if (player->useDevelopmentCard()) {
        std::cout << player->getName() << " used a development card.\n";
        moveRobber(player);
        updateLargestArmy(player);
    }
}

void Game::takeHardAITurn(std::shared_ptr<Player> player) {
    // Complex AI logic with strategic planning
    // Prioritize city building if possible
    if (player->getResource(Tile::ORE) >= 3 && player->getResource(Tile::GRAIN) >= 2) {
        if (player->buildStructure(Player::CITY)) {
            std::cout << player->getName() << " built a city.\n";
            return;
        }
    }

    // Build settlements if possible
    if (player->getResource(Tile::WOOD) >= 1 && player->getResource(Tile::BRICK) >= 1 && 
        player->getResource(Tile::SHEEP) >= 1 && player->getResource(Tile::GRAIN) >= 1) {
        if (player->buildStructure(Player::SETTLEMENT)) {
            std::cout << player->getName() << " built a settlement.\n";
            return;
        }
    }

    // Build roads to expand territory strategically
    if (player->getResource(Tile::WOOD) >= 1 && player->getResource(Tile::BRICK) >= 1) {
        if (player->buildStructure(Player::ROAD)) {
            std::cout << player->getName() << " built a road.\n";
            updateLongestRoad(player);
            return;
        }
    }

    // Trade resources with other players to achieve goals
    for (auto& otherPlayer : players) {
        if (otherPlayer != player) {
            if (player->tradeResourceWithPlayer(Tile::WOOD, Tile::BRICK, 1, otherPlayer)) {
                std::cout << player->getName() << " traded with " << otherPlayer->getName() << ".\n";
                break;
            }
        }
    }

    // Buy development cards if no other options are viable
    if (player->getResource(Tile::ORE) >= 1 && player->getResource(Tile::SHEEP) >= 1 && 
        player->getResource(Tile::GRAIN) >= 1) {
        if (player->buyDevelopmentCard()) {
            std::cout << player->getName() << " bought a development card.\n";
        }
    }

    if (player->useDevelopmentCard()) {
        std::cout << player->getName() << " used a development card.\n";
        moveRobber(player);
        updateLargestArmy(player);
    }
}


