#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"  // Assuming blackjack.h contains all necessary declarations

// Declare global variables for the deck, player's hand, and balance
Card deck[52];
Hand playerHand, splitHand;
int balance = 100;  // Starting balance for the player

// Function to simulate getting input (for simplicity, we assume it returns 1 for yes and 0 for no)
bool get_input() {
    char input;
    scanf(" %c", &input);
    if (input == 'y' || input == 'Y') {
        return true;  // Yes
    } 
    return false;  // No
    
}

// Main function to simulate the blackjack game
int main() {
    srand(time(NULL));  // Seed the random number generator

    // Initialize the player's hand and deck
    initialize_hand(&playerHand);
    initialize_deck(deck);  // This should initialize the deck with 52 cards
    // shuffle_deck(deck);  // Shuffle the deck

    // Deal two cards to the player (and show them)
    deal_player_hand(deck, &playerHand);  // Deal first card to the player
    deal_player_hand(deck, &playerHand);  // Deal second card to the player

    printf("Your hand: %d\n", playerHand.value);
    reveal_hand(&playerHand);  // Function that prints the player's hand

    // Check if the player wants to split
    if (check_split(deck, &playerHand, &balance)) {
        // Initialize the split hand and handle the split
        handle_split(deck, &playerHand, &splitHand, &balance);
        printf("Your split hand: %d\n", splitHand.value);
        reveal_hand(&splitHand);  // Print the split hand

        // After splitting, continue to play both hands
    } else {
        printf("You chose not to split.\n");
    }

    // Check if the player wants to double down
    if (double_down(&playerHand, &balance)) {
        // After doubling down, only one more card is dealt to the player
        deal_player_hand(deck, &playerHand);
        printf("Your hand after doubling down: %d\n", playerHand.value);
        reveal_hand(&playerHand);
    } else {
        printf("You chose not to double down.\n");
    }

    // Ace adjustment (handle any aces if value > 21)
    ace_adjuster(&playerHand);
    printf("Your final hand: %d\n", playerHand.value);
    reveal_hand(&playerHand);  // Print the final hand after ace adjustments

    // If split hand exists, apply ace adjustments to it as well
    if (splitHand.cardCount > 0) {
        ace_adjuster(&splitHand);
        printf("Your split hand after ace adjustment: %d\n", splitHand.value);
        reveal_hand(&splitHand);  // Print the final split hand after ace adjustments
    }

    // Final output: print the player's balance after the round
    printf("Your final balance is: $%d\n", balance);

    return 0;
}
