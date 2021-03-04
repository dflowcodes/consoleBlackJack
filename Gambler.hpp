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


class Gambler: public Player {
    
public:
    Gambler(int score_in, std::string name_in);
    std::string get_name();
    
private:
    std::string name;
};

#endif /* Gambler_hpp */
