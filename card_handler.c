#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blackjack.h"

/*  Includes functions handling card and
    deck logic and initialization.
*/

const char* SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const char* RANKS[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

void initialize_deck(Card* deck) {
    int idx = 0;
    for (int suit = 0; suit < NUM_SUITS; suit++) {
        for (int rank = 0; rank < NUM_RANKS; rank++) {
            deck[idx].isDrawn = 0;

            // build card name
            strcpy(deck[idx].name, RANKS[rank]); 
            strcat(deck[idx].name, " of ");
            strcat(deck[idx].name, SUITS[suit]);
			    
            deck[idx].value = (rank == 12) ? 11 : ((rank >= 9) ? 10 : (rank + 2)); // Face cards have a value of 10, others take their rank
            deck[idx].rankIndex = rank;
	    deck[idx].suitIndex = suit;
	    idx++;
        }
    }
}

void initialize_hand(Hand* hand) {
    hand->value = 0;
    hand->cardCount = 0;
    hand->bet = 0;
}

void draw_card(Card* deck, Hand* hand) {
    // Randomly select a card
    int cardIndex;
    do {
        cardIndex = rand() % NUM_CARDS;
    } while (deck[cardIndex].isDrawn);
    
    deck[cardIndex].isDrawn = 1;

    // Add card to hand
    hand->cards[hand->cardCount] = deck[cardIndex];
    hand->cardCount++;

    hand->value += deck[cardIndex].value;

    // accounting for possible aces
    ace_adjuster(hand);
}
