//
//  Deck.cpp
//  BlackJack
//
//  Created by Devon Flowers on 3/3/21.
//

#include "Deck.hpp"

Deck::Deck():
top_card(0)
{
    for (auto i = 0; i < 4; ++i) {
        for (auto j = 2; j <= 10; ++j) {
            this->deck.push_back(new Card(static_cast<Suit>(i), static_cast<Rank>(j)));
        }
        this->deck.push_back(new Card(static_cast<Suit>(i), Rank::Jack));
        this->deck.push_back(new Card(static_cast<Suit>(i), Rank::Queen));
        this->deck.push_back(new Card(static_cast<Suit>(i), Rank::King));

    }
}

Deck::~Deck() {
    for (auto card : this->deck) {
        delete card;
    }
}

void Deck::shuffle() {
    std::cout << "Shuffling deck... \n";
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(this->deck.begin(), this->deck.end(), g);
    this->top_card = 0;
}

Card* Deck::deal_card(bool hidden) {
    Card *card = this->deck.at(this->top_card++);
    if (hidden) {
        card->set_facedown();
    }
    return card;
}


