#include "DevelopmentCard.hpp"

DevelopmentCard::DevelopmentCard(CardType cardType) : type(cardType) {}

DevelopmentCard::CardType DevelopmentCard::getType() const {
    return type;
}
