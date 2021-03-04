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
    std::cout << "You currently have " << gambler->get_score() << " dollars!\n";
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
        std::cout << "Hit (1) or Stay (0)? ";
        std::cin >> hit;
        if (hit) {
            gambler->add_to_hand(deck->deal_card(false));
            gambler->print_hand();
            std::cout << "\n" << gambler->calculate_hand_value() << "\n";
            if (gambler->calculate_hand_value() > 21) {
                gambler->set_state(State::Bust);
                std::cout << "BUST (over 21) \n";
                player_still_playing = false;
            } else if (gambler->calculate_hand_value() == 21) {
                gambler->set_state(State::BlackJack);
                std::cout << "BlackJack 21! \n";
                player_still_playing = false;
            }
        } else {
            player_still_playing = false;
        }
    }
}

void dealer_loop(Dealer *dealer, Deck *deck, const int &gambler_hand_value) {
    bool dealer_still_playing = true;
    std::cout << "Flipping dealer hidden card... ";
    dealer->flip_hidden_card();
    dealer->print_hand();
    std::cout << "\n" << dealer->calculate_hand_value() << "\n";
    while (dealer_still_playing) {
        if (dealer->calculate_hand_value() < 17 &&
            dealer->calculate_hand_value() < gambler_hand_value) {
            std::cout << "Dealer hits: \n";
            dealer->add_to_hand(deck->deal_card(false));
            dealer->print_hand();
            std::cout << "\n" << dealer->calculate_hand_value() << "\n";
            if (dealer->calculate_hand_value() > 21) {
                dealer->set_state(DealerState::Bust);
                std::cout << "Dealer Busts! \n";
                dealer_still_playing = false;
            }
        } else if (dealer->calculate_hand_value() > 17 &&
                   dealer->calculate_hand_value() < gambler_hand_value) {
            std::cout << "Dealer stands (over 17) \n";
            dealer->set_state(DealerState::Bust);
            dealer_still_playing = false;
        } else if (dealer->calculate_hand_value() == gambler_hand_value) {
            std::cout << "Dealer stands (push)\n";
            dealer->set_state(DealerState::Push);
            dealer_still_playing = false;
        } else if (dealer->calculate_hand_value() > gambler_hand_value
                   && dealer->calculate_hand_value() <= 21) {
            std::cout << "Dealer stands (winning)\n";
            dealer->set_state(DealerState::BlackJack);
            dealer_still_playing = false;
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

void end_round(Gambler *gambler, Dealer *dealer, const int &wager) {
    // First check if player busted or black jacked...
    if (gambler->get_state() == State::Bust) {
        std::cout << "Player busted... Dealer taking " << wager << " dollar pot!\n";
        dealer->add_to_score(wager);
        return;
    } else if (gambler->get_state() == State::BlackJack) {
        std::cout << "Player BlackJacked... Player getting " << wager*2 << " dollar payout\n";
        gambler->add_to_score(wager * 2);
        return;
    }
    // Player didnt win on first pass...
    if (dealer->get_state() == DealerState::Push) {
        std::cout << "Round ends in a push... " << wager << " dollar wager returned to Player\n";
        gambler->add_to_score(wager);
        return;
    } else if (dealer->get_state() == DealerState::Bust) {
        std::cout << "Player wins! paying out " << wager*2 << " dollars to " << gambler->get_name() << "\n";
        gambler->add_to_score(wager*2);
        return;
    } else {
        std::cout << "Dealer wins! Dealer taking " << wager << " dollar pot!\n";
        dealer->add_to_score(wager);
        return;
    }
}

bool ask_to_continue(Gambler *gambler, Dealer *dealer) {
    if (gambler->get_score() == 0) {
        std::cout << "You are broke! Call 1-800-GAMBLER to get help and get out of this casino!\n";
        return false;
    }
    std::cout << "You currently have " << gambler->get_score() << " dollars. Do you wish to stay at the table?\n";
    std::cout << "1(yes), 0(no) ";
    int stay;
    std::cin >> stay;
    if (stay) {
        gambler->erase_hand();
        dealer->erase_hand();
        gambler->set_state(State::Playing);
        dealer->set_state(DealerState::Playing);
        return true;
    }
    return false;
}

void end_program(Gambler *gambler, Dealer * dealer) {
    std::cout << "During this session, you lost " << dealer->get_score() << " dollars to the house, and are "
    << "walking away with " << gambler->get_score() << " dollars. See you next time!";
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
        if (gambler->get_state() != State::Bust && gambler->get_state() != State::BlackJack) {
            dealer_loop(dealer, deck, gambler->calculate_hand_value());
        }
        end_round(gambler, dealer, pot);
        game_in_progress = ask_to_continue(gambler, dealer);
    }
    end_program(gambler, dealer);
    delete gambler;
    delete dealer;
    delete deck;
    return 0;
}
