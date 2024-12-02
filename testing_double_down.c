#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    int value;
    int rankIndex;
} Card;

typedef struct {
    Card cards[2];
    int bet;
    int value;
    int cardCount;
} Hand;

// Function to get user input for decision (yes or no)
int get_input() {
    char response[10];
    fgets(response, sizeof(response), stdin);
    return response[0] == 'y' || response[0] == 'Y';
}

// Double down function
int double_down(Hand* hand, int* balance) {
    if (hand->cardCount != 2) {
        return 0; // Cannot double down unless there are exactly 2 cards
    }

    printf("Would you like to double down? ");
    if (!get_input()) {
        return 0; // Player chose not to double down
    }

    // Check if the player has enough balance to double the bet
    if (*balance < hand->bet) {
        printf("Not enough balance to double down.\n");
        return 0; // Not enough balance
    }

    // Double the bet
    hand->bet *= 2;
    printf("Your bet has been doubled to: $%d\n", hand->bet);
    *balance -= hand->bet;  // Deduct the doubled bet from the balance

    return 1; // Successful double down
}

int main() {
    int balance = 100;  // Initial balance

    // Initialize player hand
    Hand playerHand;
    playerHand.cards[0] = (Card) {.value = 10}; // Card 1 value = 10
    playerHand.cards[1] = (Card) {.value = 10}; // Card 2 value = 10
    playerHand.cardCount = 2;
    playerHand.bet = 50;
    playerHand.value = 20; // Total value of player hand

    // Call double_down function
    int result = double_down(&playerHand, &balance);

    // Output results
    printf("Player's final bet: $%d\n", playerHand.bet);
    printf("Remaining balance: $%d\n", balance);

    return 0;
}

