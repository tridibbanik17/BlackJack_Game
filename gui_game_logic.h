#ifndef BLACKJACK_H
#define BLACKJACK_H

/*  Define constraints, structs, and
    functions for the blackjack utility
*/

#define NUM_CARDS 52
#define NUM_SUITS 4
#define NUM_RANKS 13
#define NUM_CHARLIE 5 // max hand size

#include "cardStructs.h"
#include <stdbool.h>

// Function declarations
void initialize_cards(Card *deck, Hand *playerHand , Hand *dealerHand);
bool checkBust(Hand someHand);
void deal_player_hand(Card *deck, Hand *player_hand);
void initialize_deck(Card* deck);
void initialize_hand(Hand* hand);
void draw_card(Card* deck, Hand* hand);
void play_dealer(Card *deck, Hand *dealerHand);
void display_help();

#endif
