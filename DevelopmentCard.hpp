// Liraz Balas
// 211801220
// lbalad13@gmail.com
#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

class DevelopmentCard {
public:
    enum CardType { KNIGHT, VICTORY_POINT, ROAD_BUILDING, YEAR_OF_PLENTY, MONOPOLY };

    DevelopmentCard(CardType cardType);

    CardType getType() const;

private:
    CardType type;
};

#endif // DEVELOPMENTCARD_HPP
