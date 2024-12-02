#ifndef BLACKJACK_H
#define BLACKJACK_H
#include <stdbool.h>
#include "cardStructs.h"

/*  Define constraints, structs, and
    functions for the blackjack utility
*/

#define NUM_CARDS 52
#define NUM_SUITS 4
#define NUM_RANKS 13
#define NUM_CHARLIE 5 // max hand size

extern const char* SUITS[]; // declare external constants
extern const char* RANKS[];
extern const char* DEALER;

// Card structure
typedef struct {
    int isDrawn;
    int value;
    char name[20];
    int rankIndex;  // index for the rank array
    int suitIndex;  // index for the suit array
} Card;

// Hand structure
typedef struct {
    int cardCount;
    int value;
    int bet;
    Card cards[NUM_CHARLIE];
} Hand;


// Function declarations
void initialize_deck(Card* deck);
void initialize_hand(Hand* hand);
void draw_card(Card* deck, Hand* hand);
char *game_result(Hand *playerHand, Hand *dealerHand, int *payout);
void play_dealer(Card *deck, Hand *dealerHand);
void reveal_hand(Hand *hand);

void display_help();
bool get_input();

void ace_adjuster(Hand* hand);
void split_ace_adjuster(Hand* hand);
int check_split(Card *deck, Hand *playerHand, int *balance);
void handle_split(Card *deck, Hand *playerHand, Hand *splitHand, int *balance);
int double_down(Hand *hand, int *balance);
#endif
