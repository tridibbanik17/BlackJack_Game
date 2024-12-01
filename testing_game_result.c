#include <stdio.h>
#include <stdlib.h>
#include "blackjack.h"

// Function declarations
/**
 * Determines the result of the game and calculates the payout.
 *
 * @param playerHand Pointer to the player's hand structure containing hand value and card count.
 * @param dealerHand Pointer to the dealer's hand structure containing hand value and card count.
 * @param payout Pointer to an integer representing the player's bet/payout amount. This value may be updated based on the game's result.
 * @return A string describing the outcome of the game (e.g., "Player wins", "Dealer wins").
 */
char *game_result(Hand *playerHand, Hand *dealerHand, int *payout);

int main(int argc, char *argv[]) {
    Hand playerHand, dealerHand; // Structures to hold the player's and dealer's hands
    int payout; // Variable to store the player's bet or payout amount
    char *result; // Pointer to store the result message from game_result()

    // Read player's hand details from input (value and card count)
    if (scanf("%d %d", &playerHand.value, &playerHand.cardCount) != 2) {
        fprintf(stderr, "Error reading player's hand.\n"); // Error message if input is invalid
        return 1; // Exit with an error code
    }

    // Read dealer's hand details from input (value and card count)
    if (scanf("%d %d", &dealerHand.value, &dealerHand.cardCount) != 2) {
        fprintf(stderr, "Error reading dealer's hand.\n"); // Error message if input is invalid
        return 1; // Exit with an error code
    }    

    // Read initial bet amount from input
    if (scanf("%d", &payout) != 1 || payout <= 0) {
        fprintf(stderr, "Oops! Bet amount can never be zero or less.\n"); // Error if bet is zero or negative
        return 1; // Exit with an error code
    }

    // Call the game_result function to determine the result of the game
    result = game_result(&playerHand, &dealerHand, &payout);

    // Output the game result message
    printf("%s", result);
    // Output the final payout amount
    printf("Payout: %d\n", payout);

    return 0; // Exit successfully
}
