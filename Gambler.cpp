//
//  Gambler.cpp
//  BlackJack
//
//  Created by Devon Flowers on 3/3/21.
//

#include "Gambler.hpp"

Gambler::Gambler(int score_in, std::string name_in):
Player(score_in), name{name_in}, state(State::Playing) {}

std::string Gambler::get_name() {
    return this->name;
}

State Gambler::get_state() {
    return this->state;
}

void Gambler::set_state(State state) {
    this->state = state;
}

