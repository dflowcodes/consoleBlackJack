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
#include "State.h"

class Player{
    
public:
    Player();
    int get_score();
    int calculate_hand_value();
    void add_to_score(int change);
    void add_to_hand(Card *card);
    void print_hand();
    State get_state();
    void set_state(State state);
protected:
    Player(int score_in);
private:
    std::vector<Card *> hand;
    int score;
    State state;
};

#endif /* Player_hpp */
