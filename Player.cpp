// Liraz Balas
// 211801220
// lbalad13@gmail.com
#include "Player.hpp"
#include <algorithm>
#include <iostream>

Player::Player(const std::string& name, AILevel level)
    : name(name), points(0), roadsBuilt(0), armySize(0), aiLevel(level) {
    resources[Tile::WOOD] = 0;
    resources[Tile::BRICK] = 0;
    resources[Tile::SHEEP] = 0;
    resources[Tile::GRAIN] = 0;
    resources[Tile::ORE] = 0;
}

const std::string& Player::getName() const {
    return name;
}

int Player::getPoints() const {
    return points;
}

int Player::getArmySize() const {
    return armySize;
}

Player::AILevel Player::getAILevel() const {
    return aiLevel;
}

void Player::addResource(Tile::ResourceType type, int amount) {
    resources[type] += amount;
}

int Player::getResource(Tile::ResourceType type) const {
    auto it = resources.find(type);
    if (it != resources.end()) {
        return it->second;
    }
    return 0;
}

bool Player::tradeResourceWithBank(Tile::ResourceType give, Tile::ResourceType receive, int amount) {
    if (resources[give] >= 4 * amount) {
        resources[give] -= 4 * amount;
        resources[receive] += amount;
        return true;
    }
    return false;
}

bool Player::tradeResourceWithPlayer(Tile::ResourceType give, Tile::ResourceType receive, int amount, std::shared_ptr<Player> otherPlayer) {
    if (resources[give] >= amount && otherPlayer->resources[receive] >= amount) {
        resources[give] -= amount;
        resources[receive] += amount;
        otherPlayer->resources[receive] -= amount;
        otherPlayer->resources[give] += amount;
        return true;
    }
    return false;
}

bool Player::buildStructure(Structure structure) {
    switch (structure) {
        case SETTLEMENT:
            if (resources[Tile::WOOD] >= 1 && resources[Tile::BRICK] >= 1 &&
                resources[Tile::SHEEP] >= 1 && resources[Tile::GRAIN] >= 1) {
                resources[Tile::WOOD]--;
                resources[Tile::BRICK]--;
                resources[Tile::SHEEP]--;
                resources[Tile::GRAIN]--;
                points += 1;
                return true;
            }
            break;
        case ROAD:
            if (resources[Tile::WOOD] >= 1 && resources[Tile::BRICK] >= 1) {
                resources[Tile::WOOD]--;
                resources[Tile::BRICK]--;
                roadsBuilt++;
                return true;
            }
            break;
        case CITY:
            if (resources[Tile::ORE] >= 3 && resources[Tile::GRAIN] >= 2) {
                resources[Tile::ORE] -= 3;
                resources[Tile::GRAIN] -= 2;
                points += 2;
                return true;
            }
            break;
    }
    return false;
}

bool Player::buyDevelopmentCard() {
    if (resources[Tile::ORE] >= 1 && resources[Tile::SHEEP] >= 1 && resources[Tile::GRAIN] >= 1) {
        resources[Tile::ORE]--;
        resources[Tile::SHEEP]--;
        resources[Tile::GRAIN]--;
        developmentCards.push_back(std::make_shared<DevelopmentCard>(DevelopmentCard::KNIGHT));
        return true;
    }
    return false;
}

bool Player::useDevelopmentCard() {
    for (auto it = developmentCards.begin(); it != developmentCards.end(); ++it) {
        if ((*it)->getType() == DevelopmentCard::KNIGHT) {
            developmentCards.erase(it);
            armySize++;
            return true;
        }
    }
    return false;
}

int Player::getTotalResources() const {
    int total = 0;
    for (const auto& resource : resources) {
        total += resource.second;
    }
    return total;
}

void Player::discardResources(int amount) {
    while (amount > 0) {
        for (auto& resource : resources) {
            if (resource.second > 0) {
                resource.second--;
                amount--;
                if (amount == 0) break;
            }
        }
    }
}

int Player::calculateLongestRoad() const {
    return roadsBuilt; // Simplified for illustration; actual implementation may vary
}

void Player::displayAvailableActions() const {
    std::cout << "Available actions for " << name << ":\n";
    std::cout << "1. Build Settlement\n";
    std::cout << "2. Build Road\n";
    std::cout << "3. Build City\n";
    std::cout << "4. Trade with Bank\n";
    std::cout << "5. Buy Development Card\n";
    std::cout << "6. Use Development Card\n";
    std::cout << "7. Trade with Player\n";
    std::cout << "8. End Turn\n";

    std::cout << "Your available actions based on current resources:\n";
    if (resources.at(Tile::WOOD) >= 1 && resources.at(Tile::BRICK) >= 1) {
        std::cout << "2. Build Road\n";
    }
    if (resources.at(Tile::WOOD) >= 1 && resources.at(Tile::BRICK) >= 1 &&
        resources.at(Tile::SHEEP) >= 1 && resources.at(Tile::GRAIN) >= 1) {
        std::cout << "1. Build Settlement\n";
    }
    if (resources.at(Tile::ORE) >= 3 && resources.at(Tile::GRAIN) >= 2) {
        std::cout << "3. Build City\n";
    }
    if (resources.at(Tile::ORE) >= 1 && resources.at(Tile::SHEEP) >= 1 && resources.at(Tile::GRAIN) >= 1) {
        std::cout << "5. Buy Development Card\n";
    }
    std::cout << "4. Trade with Bank\n";
    std::cout << "7. Trade with Player\n";
    std::cout << "6. Use Development Card\n";
    std::cout << "8. End Turn\n";
}

bool Player::canBuildStructure(Structure structure) const {
    switch (structure) {
        case SETTLEMENT:
            return resources.at(Tile::WOOD) >= 1 && resources.at(Tile::BRICK) >= 1 &&
                   resources.at(Tile::SHEEP) >= 1 && resources.at(Tile::GRAIN) >= 1;
        case ROAD:
            return resources.at(Tile::WOOD) >= 1 && resources.at(Tile::BRICK) >= 1;
        case CITY:
            return resources.at(Tile::ORE) >= 3 && resources.at(Tile::GRAIN) >= 2;
    }
    return false;
}

bool Player::canBuyDevelopmentCard() const {
    return resources.at(Tile::ORE) >= 1 && resources.at(Tile::SHEEP) >= 1 && resources.at(Tile::GRAIN) >= 1;
}

bool Player::hasDevelopmentCard() const {
    for (const auto& card : developmentCards) {
        if (card->getType() == DevelopmentCard::KNIGHT) {
            return true;
        }
    }
    return false;
}
