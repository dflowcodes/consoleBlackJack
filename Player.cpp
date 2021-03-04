//
//  Player.cpp
//  BlackJack
//
//  Created by Devon Flowers on 3/3/21.
//

#include "Player.hpp"

Player::Player():
hand{}, score{0} {}

Player::Player(int score_in):
hand{}, score{score_in} {}

void Player::add_to_hand(Card *card) {
    this->hand.push_back(card);
}

int Player::get_score() {
    return this->score;
}

int Player::calculate_hand_value() {
    int count = 0;
    bool ace_in_hand = false;
    for (auto it : this->hand) {
        if (it->get_rank() == Rank::Ace) {
            ace_in_hand = true;
        }
        // Only add the face up cards to the count
        if (!it->is_facedown()) {
            count += it->get_numerical_value();
        }
    }
    // If they bust but have an ace, turn it to a 1.
    if (count > 21 && ace_in_hand) {
        std::cout << "Over 21 - turning an Ace to a 1!\n";
        for (auto it : this->hand) {
            if (it->get_rank() == Rank::Ace) {
                it->set_rank(Rank::One);
                count -= 10;
            }
        }
    }
    return count;
}

void Player::add_to_score(int change) {
    this->score += change;
}

void Player::print_hand() {
    for (auto it : this->hand) {
        if (!it->is_facedown()) {
            std::cout << it->get_card_description() << ", ";
        } else {
            std::cout << "Facedown Card, ";
        }
    }
}

void Player::erase_hand() {
    this->hand.clear();
}

