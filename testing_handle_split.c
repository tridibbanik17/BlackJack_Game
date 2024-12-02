#include <stdio.h>
#include <stdlib.h>

// Define the Card structure
typedef struct {
    char name[20];
    int value;
    int rankIndex;  // Example: 1 for Ace, 10 for Jack, etc.
} Card;

// Define the Hand structure
typedef struct {
    Card cards[2];
    int bet;
    int value;
    int cardCount;
} Hand;

// Function to initialize a hand
void initialize_hand(Hand* hand) {
    hand->value = 0;
    hand->cardCount = 0;
    hand->bet = 0;
}

// Function to adjust the value of aces (in case of split)
void split_ace_adjuster(Hand* hand) {
    hand->value = 11;
    hand->cards[0].value = 11;  // Adjust Ace value to 11 after split
}

// handle_split function: splits the hand and modifies the balance
void handle_split(Card *deck, Hand *playerHand, Hand *splitHand, int *balance) {
    printf("You split your hand. Each hand starts with a bet of $%d.\n\n", playerHand->bet);
    *balance -= playerHand->bet;

    // Initialize the split hand
    initialize_hand(splitHand);
    splitHand->bet = playerHand->bet;

    // Move second card to split hand
    playerHand->value -= playerHand->cards[1].value;
    splitHand->cards[0] = playerHand->cards[1];
    splitHand->cardCount++;
    playerHand->cardCount--;
    splitHand->value += splitHand->cards[0].value;

    // Adjust aces if necessary
    if (playerHand->value == 1) {
        split_ace_adjuster(playerHand);
        split_ace_adjuster(splitHand);
    }
}

int main() {
    int balance;

    // Prompt the user to enter the initial balance
    printf("Enter initial balance: ");
    if (scanf("%d", &balance) != 1 || balance <= 0) {
        fprintf(stderr, "Invalid balance input. Exiting.\n");
        return 1;
    }

    // Simulate a simple deck of cards and the player's hand
    Card deck[52];  // Deck is not used here but could be extended
    Hand playerHand, splitHand;

    // Initialize player hand
    initialize_hand(&playerHand);
    playerHand.cards[0] = (Card) {.value = 10}; // Example card 1
    playerHand.cards[1] = (Card) {.value = 10}; // Example card 2
    playerHand.cardCount = 2;
    playerHand.value = 20;
    playerHand.bet = 50;

    // Call handle_split
    handle_split(deck, &playerHand, &splitHand, &balance);

    // Output results
    printf("Player hand: Value=%d, CardCount=%d\n", playerHand.value, playerHand.cardCount);
    printf("Split hand: Value=%d, CardCount=%d\n", splitHand.value, splitHand.cardCount);
    if (balance < 0) {
        int updated_balance = balance + 50;
        printf("Remaining balance: %d\n", updated_balance);
        return 0;
    }
    printf("Remaining balance: %d\n", balance);

    return 0;
}
