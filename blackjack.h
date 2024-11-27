#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "cardStructs.h"

/*  Define constraints, structs, and
    functions for the blackjack utility
*/

// Function declarations
void initialize_deck(Card* deck);
void initialize_hand(Hand* hand);
void draw_card(Card* deck, Hand* hand);
char *game_result(Hand *playerHand, Hand *dealerHand, int *payout);
void play_dealer(Card *deck, Hand *dealerHand);
void reveal_hand(Hand *hand, const char *card_holder);
void display_help();

#endif
