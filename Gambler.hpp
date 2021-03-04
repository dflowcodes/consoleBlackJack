//
//  Gambler.hpp
//  BlackJack
//
//  Created by Devon Flowers on 3/3/21.
//

#ifndef Gambler_hpp
#define Gambler_hpp

#include <stdio.h>
#include <string>
#include "Player.hpp"
#include "State.h"


class Gambler: public Player {
    
public:
    Gambler(int score_in, std::string name_in);
    std::string get_name();
    State get_state();
    void set_state(State state);
    
private:
    std::string name;
    State state;
};

#endif /* Gambler_hpp */
