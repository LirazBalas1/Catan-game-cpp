#ifndef ROBBER_HPP
#define ROBBER_HPP

#include "Tile.hpp"
#include <memory>

class Robber {
public:
    Robber();

    void moveRobber(std::shared_ptr<Tile> tile);

    std::shared_ptr<Tile> getCurrentTile() const;

private:
    std::shared_ptr<Tile> currentTile;
};

#endif // ROBBER_HPP
