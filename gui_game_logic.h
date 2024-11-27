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

// Function declarations
void initialize_cards(Card *deck, Hand *playerHand , Hand *dealerHand);
bool checkBust(Hand someHand);
void deal_player_hand(Card *deck, Hand *player_hand);
void initialize_deck(Card* deck);
void initialize_hand(Hand* hand);
void draw_card(Card* deck, Hand* hand);
char *game_result(Hand *playerHand, Hand *dealerHand, int *payout);
void play_dealer(Card *deck, Hand *dealerHand);
void reveal_hand(Hand *hand, const char *card_holder);
void display_help();

#endif
