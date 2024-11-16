#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"

void play_blackjack() {
    Card deck[NUM_CARDS];
    Hand playerHand;

    srand((unsigned int)time(NULL)); // Setup random seed

    char continuePlaying;

    printf("Welcome to Blackjack!\n");

    initialize_deck(deck);
    initialize_hand(&playerHand);

    // Initial two cards
    for (int i = 0; i < 2; i++) {
        draw_card(deck, &playerHand);
        printf("You drew: %s\n", playerHand.cards[i].name);
    }
    printf("Your hand value is: %d\n", playerHand.value);

    // Game loop
    do {
        printf("Would you like to draw another card? (y/n): ");
        scanf(" %c", &continuePlaying);
        if (continuePlaying == 'y' || continuePlaying == 'Y') {
            draw_card(deck, &playerHand);
            printf("You drew: %s\n", playerHand.cards[playerHand.cardCount - 1].name);
            printf("Your hand value is: %d\n", playerHand.value);

            if (playerHand.value > 21) {
                printf("Bust! Your hand value exceeded 21. Game over.\n");
                break;
            }
        }
    } while (continuePlaying == 'y' || continuePlaying == 'Y');

    if (playerHand.value <= 21) {
        printf("Your final hand value is: %d. Thank you for playing!\n", playerHand.value);
    }
}

int main(int argc, char* argv[]) {
    play_blackjack();
    return 0;
}
