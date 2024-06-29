#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <memory>
#include <iostream>
#include <cstdlib>
#include <limits>
#include "Board.hpp"
#include "Player.hpp"
#include "Robber.hpp"

class Game {
public:
    Game();

    void start();
    std::shared_ptr<Player> getPlayer(int index) const;
    int rollDice() const;

    // Public wrapper methods for testing
    void testMoveRobber(std::shared_ptr<Player> player) {
        moveRobber(player);
    }

    void testTakeAITurn(std::shared_ptr<Player> player) {
        takeAITurn(player);
    }

private:
    std::shared_ptr<Board> board;
    std::vector<std::shared_ptr<Player>> players;
    Robber robber;
    std::shared_ptr<Player> longestRoadPlayer;
    std::shared_ptr<Player> largestArmyPlayer;

    void initialPlacement();
    void placeHumanInitialSettlement(std::shared_ptr<Player> player);
    void placeHumanInitialRoad(std::shared_ptr<Player> player);
    void placeAIInitialSettlement(std::shared_ptr<Player> player);
    void placeAIInitialRoad(std::shared_ptr<Player> player);
    void displayAvailableActions(std::shared_ptr<Player> player) const;
    void takeHumanTurn(std::shared_ptr<Player> player);
    bool tradeWithBank(std::shared_ptr<Player> player);
    bool tradeWithPlayer(std::shared_ptr<Player> player);
    void updateLongestRoad(std::shared_ptr<Player> player);
    void updateLargestArmy(std::shared_ptr<Player> player);
    void distributeResources(int diceRoll);
    void displayResources(std::shared_ptr<Player> player) const;
    void moveRobber(std::shared_ptr<Player> player);
    void discardResources(std::shared_ptr<Player> player);
    void robPlayer(std::shared_ptr<Player> robber, std::shared_ptr<Player> victim);
    bool isGameOver() const;
    void announceWinner() const;
    void takeAITurn(std::shared_ptr<Player> player);
    void takeEasyAITurn(std::shared_ptr<Player> player);
    void takeMediumAITurn(std::shared_ptr<Player> player);
    void takeHardAITurn(std::shared_ptr<Player> player);
};

#endif // GAME_HPP
