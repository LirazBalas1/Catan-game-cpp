// Liraz Balas
// 211801220
// lbalad13@gmail.com
#include "DevelopmentCard.hpp"

DevelopmentCard::DevelopmentCard(CardType cardType) : type(cardType) {}

DevelopmentCard::CardType DevelopmentCard::getType() const {
    return type;
}
