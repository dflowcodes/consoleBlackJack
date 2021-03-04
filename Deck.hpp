//
//  Deck.hpp
//  BlackJack
//
//  Created by Devon Flowers on 3/3/21.
//

#ifndef Deck_hpp
#define Deck_hpp

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include "Card.hpp"

class Deck {
    
public:
    Deck();
    ~Deck();
    void shuffle();
    Card * deal_card(bool hidden);
    
private:
    std::vector<Card *> deck;
    uint32_t top_card;
};

#endif /* Deck_hpp */
