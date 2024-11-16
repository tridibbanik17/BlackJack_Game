#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blackjack.h"

const char* suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const char* ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

void initialize_deck(Card* deck) {
    int idx = 0;
    for (int suit = 0; suit < NUM_SUITS; suit++) {
        for (int rank = 0; rank < NUM_RANKS; rank++) {
            deck[idx].isDrawn = 0;
            snprintf(deck[idx].name, sizeof(deck[idx].name), "%s of %s", ranks[rank], suits[suit]);
            deck[idx].value = (rank >= 9) ? 10 : (rank + 2); // Face cards have a value of 10, others take their rank
            idx++;
        }
    }
}

void initialize_hand(Hand* hand) {
    hand->value = 0;
    hand->cardCount = 0;
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
}