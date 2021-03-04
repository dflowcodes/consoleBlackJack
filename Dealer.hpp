//
//  Dealer.hpp
//  BlackJack
//
//  Created by Devon Flowers on 3/3/21.
//

#ifndef Dealer_hpp
#define Dealer_hpp

#include <stdio.h>
#include "Player.hpp"
#include "DealerState.h"

class Dealer: public Player {
public:
    void flip_hidden_card();
    Dealer();
    DealerState get_state();
    void set_state(DealerState state);
    
private:
    DealerState state;
};

#endif /* Dealer_hpp */
