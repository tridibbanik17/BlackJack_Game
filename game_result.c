#include<stdio.h>
#include<stdlib.h>
#include "blackjack.h"
#include<time.h>

// Function: game_result
// Determines the outcome of the game based on the player's and dealer's hand values and card counts.
// Updates the payout amount based on the result.
//
// Parameters:
// - playerHand: Pointer to the player's hand structure (contains value and card count).
// - dealerHand: Pointer to the dealer's hand structure (contains value and card count).
// - payout: Pointer to an integer representing the current bet amount; updated based on the result.
//
// Returns:
// - A string indicating the result of the game (e.g., "Bust! Player lost.", "Blackjack! Player wins.").
char *game_result(Hand *playerHand, Hand *dealerHand, int *payout) {
    // bust if hand value exceeds 21
    // If the dealer busts, player wins. 
    // If the dealer doesn't bust, player wins if their hand values higher than dealer's
    
    if (playerHand->value > 21) {
        *payout = 0;
        return "Bust! Player lost.\n";
    }
    // 5-Card Charlie
    else if (playerHand->cardCount >= NUM_CHARLIE && playerHand->value <= 21) {
        *payout *= 2;
        return "Player wins by 5-card Charlie.\n";
    }
    // Player wins with 'Blackjack' if and only if the very first 2 cards of the player's hand has the cumulative value of 21.
    else if (playerHand->value == 21 && playerHand->cardCount == 2) {
        *payout *= 2.5;
        return "Blackjack! Player wins.\n";
    }
    // Player wins if dealer busts or player has a higher hand value (obviously not exceeding 21) at any point of the game
    else if (dealerHand->value > 21 || playerHand->value > dealerHand->value) {
        *payout *= 2;
        return "Yay! Player won.\n";
    }
    // Dealer wins if their hand is higher
    else if (playerHand->value < dealerHand->value) {
        *payout = 0;
        return "Dealer wins. Wishing the best of luck for next round of play!\n";
    }
    // It is considered a push if both have the same hand value
    else {
        return "Push! Player got their bet back.\n";
    }
}


