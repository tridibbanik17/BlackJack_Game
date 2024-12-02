#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int rankIndex;
} Card;

typedef struct {
    Card cards[2];
    int bet;
} Hand;

int get_input() {
    char response[10];
    fgets(response, sizeof(response), stdin);
    return response[0] == 'y' || response[0] == 'Y';
}

int check_split(Card *deck, Hand *playerHand, int *balance) {
    if (playerHand->cards[0].rankIndex != playerHand->cards[1].rankIndex) {
        return 0;
    }

    printf("You have two %s. Would you like to split? ", playerHand->cards[0].name);
    if (!get_input()) {
        return 0;
    }

    if (*balance < playerHand->bet) {
        printf("Not enough balance to split. ");
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[]) {
    Card deck[2];
    Hand playerHand;
    int balance;

    // Input for card 1
    printf("Enter card 1 name and rankIndex: ");
    scanf("%s %d", deck[0].name, &deck[0].rankIndex);

    // Input for card 2
    printf("Enter card 2 name and rankIndex: ");
    scanf("%s %d", deck[1].name, &deck[1].rankIndex);

    // Input for bet amount
    printf("Enter bet amount: ");
    scanf("%d", &playerHand.bet);

    getchar(); // Consume the newline character

    // Set up the player hand
    playerHand.cards[0] = deck[0];
    playerHand.cards[1] = deck[1];

    // Assume an initial balance
    balance = 100;

    // Call check_split and print result
    int result = check_split(deck, &playerHand, &balance);
    printf("Result: %d\n", result);

    return 0;
}
