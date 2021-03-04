//
//  main.cpp
//  BlackJack
//
//  Created by Devon Flowers on 3/2/21.
//

#include "Deck.hpp"
#include "Gambler.hpp"
#include "Dealer.hpp"

/*
 This is the driver file. This should create the three main classes and play the game.
 The command line expects ./executable <int>starting_money <string>player_name
*/

void check_command_line_input(int argc, const char * argv[]) {
    if (argc != 3) {
        std::cout << "Invalid usage: Try ./executable starting_money player_name\n";
        exit(1);
    }
}

void intro (Gambler *gambler) {
    std::cout << "Welcome to the blackjack terminal, "
    << gambler->get_name() << ".\n"
    << "You are starting with "
    << gambler->get_score() <<
    " dollars. Lets see what you can do with that. \n";
}

int take_bets(Gambler *gambler) {
    int bet;
    std::cout << "Please enter a valid integer amount for how much you would like to bet: ";
    while(true) {
        std::cin >> bet;
        if (bet > gambler->get_score()) {
            std::cout << "You cannot bet more than you're worth! Try again: ";
        } else {
            gambler->add_to_score(-bet);
            return bet;
            break;
        }
    }
    return -1;
}

void player_loop(Gambler *gambler, Deck *deck) {
    bool player_still_playing = true;
    while (player_still_playing) {
        int hit;
        std::cout << "Hit (1) or Stay (0)?";
        std::cin >> hit;
        if (hit) {
            gambler->add_to_hand(deck->deal_card(false));
            gambler->print_hand();
            std::cout << "\n" << gambler->calculate_hand_value() << "\n";
            if (gambler->calculate_hand_value() > 21) {
                gambler->set_state(State::Bust);
                std::cout << "BUST (over 21) \n";
                player_still_playing = false;
            }
        } else {
            player_still_playing = false;
        }
    }
}

// deal in this order (gambler, dealer(flipped), gambler, dealer (regular)
void deal(Gambler *gambler, Dealer *dealer, Deck *deck) {
    std::cout << "Dealing Cards... \n";
    gambler->add_to_hand(deck->deal_card(false));
    dealer->add_to_hand(deck->deal_card(true));
    gambler->add_to_hand(deck->deal_card(false));
    dealer->add_to_hand(deck->deal_card(false));
}

void print_current_state(Dealer *dealer, Gambler *gambler) {
    std::cout << "-----STATE OF GAME-----\n"
    << "Dealers hand is: ";
    dealer->print_hand();
    std::cout << "\n" << gambler->get_name() << "'s hand: ";
    gambler->print_hand();
    std::cout << "\n";
    std::cout << "DEALER SCORE: " << dealer->calculate_hand_value() << "\n";
    std::cout << gambler->get_name() << "'s SCORE: " << gambler->calculate_hand_value() << "\n";
    
}

int main(int argc, const char * argv[]) {
    check_command_line_input(argc, argv);
    Dealer *dealer = new Dealer();
    Deck *deck = new Deck();
    Gambler *gambler = new Gambler(atoi(argv[1]), argv[2]);
    bool game_in_progress = true;
    intro(gambler);
    while (game_in_progress) {
        int pot = 0;
        deck->shuffle();
        pot = take_bets(gambler);
        deal(gambler, dealer, deck);
        print_current_state(dealer, gambler);
        player_loop(gambler, deck);
        // erase everything below this line when you finish.
        std::cout << gambler->get_score() << "\n";
        game_in_progress = false;
    }
    
    delete gambler;
    delete dealer;
    delete deck;
    return 0;
}
