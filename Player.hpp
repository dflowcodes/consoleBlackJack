//
//  Player.hpp
//  BlackJack
//
//  Created by Devon Flowers on 3/3/21.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Card.hpp"

class Player{
    
public:
    Player();
    int get_score();
    int calculate_hand_value();
    void add_to_score(int change);
    void add_to_hand(Card *card);
    void print_hand();
    void erase_hand();
    
protected:
    Player(int score_in);
    std::vector<Card *> hand;
private:
    int score;
    
};

#endif /* Player_hpp */
