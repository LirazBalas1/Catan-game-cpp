#ifndef TILE_HPP
#define TILE_HPP

#include <string>

class Tile {
public:
    enum ResourceType { WOOD, BRICK, SHEEP, GRAIN, ORE, DESERT };

    Tile(ResourceType resourceType, int resourceNumber);

    ResourceType getType() const;
    int getNumber() const;
    static const char* getResourceName(ResourceType type);

private:
    ResourceType type;
    int number;
};

#endif // TILE_HPP
