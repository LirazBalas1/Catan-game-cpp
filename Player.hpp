#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include "Tile.hpp"
#include "DevelopmentCard.hpp"

class Player {
public:
    enum Structure { ROAD, SETTLEMENT, CITY };
    enum AILevel { EASY, MEDIUM, HARD };

    Player(const std::string& name, AILevel level = EASY);

    const std::string& getName() const;
    int getPoints() const;
    int getArmySize() const;
    AILevel getAILevel() const;

    void addResource(Tile::ResourceType type, int amount);
    int getResource(Tile::ResourceType type) const;
    bool tradeResourceWithBank(Tile::ResourceType give, Tile::ResourceType receive, int amount);
    bool tradeResourceWithPlayer(Tile::ResourceType give, Tile::ResourceType receive, int amount, std::shared_ptr<Player> otherPlayer);
    bool buildStructure(Structure structure);
    bool buyDevelopmentCard();
    bool useDevelopmentCard();
    int getTotalResources() const;
    void discardResources(int amount);
    int calculateLongestRoad() const;
    void displayAvailableActions() const;
    bool canBuildStructure(Structure structure) const;
    bool canBuyDevelopmentCard() const;
    bool hasDevelopmentCard() const;

private:
    std::string name;
    int points;
    int roadsBuilt;
    int armySize;
    AILevel aiLevel;
    std::map<Tile::ResourceType, int> resources;
    std::vector<std::shared_ptr<DevelopmentCard>> developmentCards;
};

#endif // PLAYER_HPP
