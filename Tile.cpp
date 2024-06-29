// Liraz Balas
// 211801220
// lbalad13@gmail.com
#include "Tile.hpp"

Tile::Tile(ResourceType resourceType, int resourceNumber) : type(resourceType), number(resourceNumber) {}

Tile::ResourceType Tile::getType() const {
    return type;
}

int Tile::getNumber() const {
    return number;
}
const char* Tile::getResourceName(ResourceType type) {
    switch (type) {
        case WOOD:
            return "Wood";
        case BRICK:
            return "Brick";
        case SHEEP:
            return "Sheep";
        case GRAIN:
            return "Grain";
        case ORE:
            return "Ore";
        default:
            return "Unknown";
    }
}
