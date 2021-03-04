//
//  Card.cpp
//  BlackJack
//
//  Created by Devon Flowers on 3/3/21.
//

#include "Card.hpp"

Card::Card(const Suit &suit_in, const Rank &rank_in):
rank {rank_in}, suit{suit_in}, facedown{false} {}

Rank Card::get_rank() {
    return this->rank;
}

Suit Card::get_suit() {
    return this->suit;
}

void Card::set_rank(Rank rank) {
    this->rank = rank;
}

bool Card::is_facedown() {
    return this->facedown;
}

void Card::flip_faceup() {
    this->facedown = false;
}

int Card::get_numerical_value() {
    if (this->rank == Rank::Jack || this->rank == Rank::Queen || this->rank == Rank::King) {
        return 10;
    }
    return (int)this->rank;
}

void Card::set_facedown() {
    this->facedown = true;
}

std::string Card::get_card_description() {
    std::string description = "";
    switch(this->rank) {
        case Rank::Ace:
            description += "Ace of";
            break;
        case Rank::Jack:
            description += "Jack of";
            break;
        case Rank::Queen:
            description += "Queen of";
            break;
        case Rank::King:
            description += "King of";
            break;
        default:
            description += std::to_string(this->get_numerical_value()) + " of";
    }
    
    switch (this->suit) {
        case Suit::Hearts:
            description += " Hearts";
            break;
        case Suit::Spades:
            description += " Spades";
            break;
        case Suit::Diamonds:
            description += " Diamonds";
            break;
        case Suit::Clubs:
            description += " Clubs";
            break;
        default:
            break;
    }
    return description;
}

//TODO: Need to implement going alone, and potentially insurance (although that seems unnecesarry).
