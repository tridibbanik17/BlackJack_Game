#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"
#include <stdbool.h>

/*  Main logic for Blackjack utility, including 
    call from command line and game loop and
    initialization.
*/

// get_input returns whether user input is yes or not
bool get_input(){
	char input;
	scanf("%c", &input);
        if (input == 'y' || input == 'Y') {
		return true;
	}
	return false;
}

// main game logic
void play_blackjack(int *balance) {
    // initialization
    Card deck[NUM_CARDS];
    Hand playerHand;
    srand((unsigned int)time(NULL)); // Setup random seed
    char continuePlaying;
    initialize_deck(deck);
    initialize_hand(&playerHand);
    int initialBet = 0;

    // handle initial bet
    printf("Enter the bet amount: $");
    scanf("%d", &initialBet);

    // draw initial two cards
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

    /*
    // Get the game result
    game_result(&playerHand, &dealerHand, bet);
*/
}


// command line call
int main(int argc, char* argv[]) {
    int balance = 500;
    printf("Welcome to Blackjack!\n");

    while (balance > 0) {
        play_blackjack(&balance);
        printf("Continue? ");
        if (!get_input()) {
            break;
        }
    }
    printf("bye");

    return 0;
}
