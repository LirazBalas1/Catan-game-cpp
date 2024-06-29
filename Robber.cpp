// Liraz Balas
// 211801220
// lbalad13@gmail.com
#include "Robber.hpp"

Robber::Robber() : currentTile(nullptr) {}

void Robber::moveRobber(std::shared_ptr<Tile> tile) {
    currentTile = tile;
}

std::shared_ptr<Tile> Robber::getCurrentTile() const {
    return currentTile;
}
