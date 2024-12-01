#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blackjack.h"

/* Includes functions handling card and
   deck logic and initialization.
*/

// Array of suit names
const char* SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};

// Array of rank names
const char* RANKS[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

/* 
 * Function: initialize_deck
 * --------------------------
 * Initializes the deck with all 52 cards, assigning 
 * each card its name, value, rank index, and suit index.
 * 
 * Parameters:
 *   Card* deck - Pointer to an array of Card structures representing the deck.
 * Returns: None
 */
void initialize_deck(Card* deck) {
    int idx = 0; // Index to track the current card in the deck
    for (int suit = 0; suit < NUM_SUITS; suit++) { // Loop through each suit
        for (int rank = 0; rank < NUM_RANKS; rank++) { // Loop through each rank
            deck[idx].isDrawn = 0; // Mark card as not drawn

            // Build the card name, e.g., "Ace of Spades"
            strcpy(deck[idx].name, RANKS[rank]); 
            strcat(deck[idx].name, " of ");
            strcat(deck[idx].name, SUITS[suit]);
            
            // Assign value: Face cards are 10, Ace is 11, others are rank + 2
            deck[idx].value = (rank == 12) ? 11 : ((rank >= 9) ? 10 : (rank + 2)); 

            // Store rank and suit indices for potential future use
            deck[idx].rankIndex = rank;
            deck[idx].suitIndex = suit;
            idx++;
        }
    }
}

/* 
 * Function: initialize_hand
 * --------------------------
 * Initializes a hand by setting its value, card count, and bet to zero.
 * 
 * Parameters:
 *   Hand* hand - Pointer to a Hand structure to initialize.
 * Returns: None
 */
void initialize_hand(Hand* hand) {
    hand->value = 0;        // Set initial hand value to 0
    hand->cardCount = 0;    // Set initial card count to 0
    hand->bet = 0;          // Set initial bet to 0
}

/* 
 * Function: draw_card
 * --------------------
 * Draws a random card from the deck and adds it to the player's hand.
 * Ensures the card has not already been drawn. Updates hand value and card count.
 * 
 * Parameters:
 *   Card* deck - Pointer to an array of Card structures representing the deck.
 *   Hand* hand - Pointer to a Hand structure representing the player's hand.
 * Returns: None
 */
void draw_card(Card* deck, Hand* hand) {
    int cardIndex; // Index of the randomly selected card
    do {
        cardIndex = rand() % NUM_CARDS; // Generate a random index in the range of the deck
    } while (deck[cardIndex].isDrawn); // Repeat if the card has already been drawn
    
    deck[cardIndex].isDrawn = 1; // Mark the card as drawn

    // Add the card to the player's hand
    hand->cards[hand->cardCount] = deck[cardIndex];
    hand->cardCount++; // Increment the card count

    // Update the total value of the hand
    hand->value += deck[cardIndex].value;

    // Adjust the hand value if there are aces
    ace_adjuster(hand);
}
