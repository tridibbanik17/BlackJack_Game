#include<stdio.h>
#include<stdlib.h>
#include "blackjack.h"

// Function to print the cards in a hand and its total value
void reveal_hand(Hand *hand, const char *card_holder) {
    printf("%s's hand: ", card_holder); // Print whose hand is holding a particular set of cards (i.e., Player or Dealer)
    for (int i = 0; i < hand->cardCount; i++) {
        printf("%s, ", hand->cards[i].name); // Print each card in the hand
    }
    printf("Total value: %d\n", hand->value); // Print the total value of the hand
}

// Function for the dealer to play its turn
void play_dealer(Card *deck, Hand *dealerHand) {
    // Dealer must draw cards until their hand value is at least 17
    while (dealerHand->value < 17) {
        draw_card(deck, dealerHand);
        reveal_hand(dealerHand, "Dealer"); // Print dealer's hand after each card draw
    }
}

// Function to get the game result
void game_result(Hand *playerHand, Hand *dealerHand, int bet) {
    // Player busts if their hand value exceeds 21
    // In blackjack, a bust occurs when a player or the dealer's hand exceeds 21
    // If the dealer busts, player wins. 
    // If the dealer doesn't bust, player wins if and only if their hand is higher than the dealer's hand.
    if (playerHand->value > 21) {
        printf("Bust! Player lost.\n");
    }
    // Player wins with a Charlie rule if and only if player's hand contains 5 cards and total card value in player's hand does not exceed 21.
    else if (playerHand->cardCount == 5 && playerHand->value <= 21) {
        printf("Charlie! Player won.\n");
        printf("Player earned $%d.\n", bet * 2); // Payout: Double the bet
    }
    // Player wins with 'Blackjack' if and only if the very first 2 cards of the player's hand has the cumulative value of 21.
    else if (playerHand->value == 21 && playerHand->cardCount == 2) {
        printf("Blackjack! Player won.\n");
        printf("Player earned $%d.\n", bet * 2.5); // Payout: 2.5 times the bet
    }
    // Player wins if dealer busts or player has a higher hand value (obviously not exceeding 21) at any point of the game
    else if (dealerHand->value > 21 || playerHand->value > dealerHand->value) {
        printf("Yay! Player won.\n");
        printf("Player earned $%d.\n", bet * 2); // Payout: Double the bet
    }
    // Dealer wins if their hand is higher
    else if (playerHand->value < dealerHand->value) {
        printf("Dealer won. Wishing the best of luck for next round of play!\n");
    }
    // It is considered a push if both have the same hand value
    else {
        printf("Push! Player got their bet back.\n"); // Player neither wins nor loses their bet
    }
}
