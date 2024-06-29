// Liraz Balas
// 211801220
// lbalad13@gmail.com
#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <memory>
#include "Tile.hpp"

class Board {
public:
    Board();

    std::shared_ptr<Tile> getTile(int index) const;
    
    const std::vector<std::shared_ptr<Tile>>& getTiles() const;

private:
    std::vector<std::shared_ptr<Tile>> tiles;
};

#endif // BOARD_HPP
