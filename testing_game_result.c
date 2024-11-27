#include <stdio.h>
#include <stdlib.h>
#include "blackjack.h"

// Function declarations
char *game_result(Hand *playerHand, Hand *dealerHand, int *payout);

int main(int argc, char *argv[]) {
    Hand playerHand, dealerHand;
    int payout;
    char *result;

    // Read player's hand details
    if (scanf("%d %d", &playerHand.value, &playerHand.cardCount) != 2) {
        fprintf(stderr, "Error reading player's hand.\n");
        return 1;
    }

    // Read dealer's hand details
    if (scanf("%d %d", &dealerHand.value, &dealerHand.cardCount) != 2) {
        fprintf(stderr, "Error reading dealer's hand.\n");
        return 1;
    }    

    // Read initial bet amount
    if (scanf("%d", &payout) != 1 || payout <= 0) {
        fprintf(stderr, "Oops! Bet amount can never be zero or less.\n");
        return 1;
    }

    // Call the game_result function
    result = game_result(&playerHand, &dealerHand, &payout);

    // Output the game result and payout
    printf("%s", result);
    printf("Payout: %d\n", payout);

    return 0;
}
