//
//  Card.hpp
//  BlackJack
//
//  Created by Devon Flowers on 3/3/21.
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>
#include <string>
#include "Suit.h"
#include "Rank.h"

class Card {
    
public:
    Card(const Suit &suit_in, const Rank &rank_in);
    Rank get_rank();
    Suit get_suit();
    bool is_facedown();
    int get_numerical_value();
    void set_facedown();
    void set_rank(Rank rank);
    std::string get_card_description();
    
private:
    Rank rank;
    Suit suit;
    bool facedown;
    
};

#endif /* Card_hpp */
