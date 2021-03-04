//
//  Dealer.cpp
//  BlackJack
//
//  Created by Devon Flowers on 3/3/21.
//

#include "Dealer.hpp"


Dealer::Dealer():
Player(), state(DealerState::Playing) {}

void Dealer::flip_hidden_card() {
    for (auto it : this->hand) {
        if (it->is_facedown()) {
            it->flip_faceup();
            std::cout << it->get_card_description() << " was flipped up.\n";
        }
    }
}

DealerState Dealer::get_state() {
    return this->state;
}

void Dealer::set_state(DealerState state) {
    this->state = state;
}
