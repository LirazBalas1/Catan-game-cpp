#include "Board.hpp"

Board::Board() {
    // Initialize the board with different tiles (example initialization)
    tiles.push_back(std::make_shared<Tile>(Tile::WOOD, 6));
    tiles.push_back(std::make_shared<Tile>(Tile::BRICK, 8));
    tiles.push_back(std::make_shared<Tile>(Tile::SHEEP, 5));
    tiles.push_back(std::make_shared<Tile>(Tile::GRAIN, 9));
    tiles.push_back(std::make_shared<Tile>(Tile::ORE, 4));
    // Add more tiles as needed
}

std::shared_ptr<Tile> Board::getTile(int index) const {
    return tiles.at(static_cast<std::vector<std::shared_ptr<Tile>>::size_type>(index));
}

const std::vector<std::shared_ptr<Tile>>& Board::getTiles() const {
    return tiles;
}
