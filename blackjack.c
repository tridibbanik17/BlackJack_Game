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

int get_initial_bet() {
    // handle initial bet
    int initialBet = 0;
    printf("Enter the bet amount: $");
    scanf("%d", &initialBet);
    return initialBet || 100;
}

void deal_player_hand(Card *deck, Hand *playerHand) {
    // draw initial two cards
    for (int i = 0; i < 2; i++) {
        draw_card(deck, playerHand);
        printf("You drew: %s\n", playerHand->cards[i].name);
    }
    printf("Your hand value is: %d\n", playerHand->value);
}

void player_hit_loop(Card *deck, Hand *playerHand) {
    char continuePlaying;

    do {
        printf("Would you like to draw another card? (y/n): ");
        scanf(" %c", &continuePlaying);
        if (continuePlaying == 'y' || continuePlaying == 'Y') {
            draw_card(deck, playerHand);
            printf("You drew: %s\n", playerHand->cards[playerHand->cardCount - 1].name);
            printf("Your hand value is: %d\n", playerHand->value);

            if (playerHand->value > 21 || playerHand->cardCount >= NUM_CHARLIE) {
                //printf("Bust! Your hand value exceeded 21. Game over.\n");
                break;
            }
        }
    } while (continuePlaying == 'y' || continuePlaying == 'Y');
}

// main game logic
void play_blackjack(int *balance) {
    // initialization
    Card deck[NUM_CARDS];
    Hand playerHand;
    Hand dealerHand;
    srand((unsigned int)time(NULL)); // Setup random seed

    initialize_deck(deck);
    initialize_hand(&playerHand);
    initialize_hand(&dealerHand);
    int initialBet = get_initial_bet();
    playerHand.bet = initialBet;

    deal_player_hand(deck, &playerHand);

    // player hit/stand loop
    player_hit_loop(deck, &playerHand);

    // dealer's turn
    play_dealer(deck, &dealerHand);

    // handle the game result
    int payout = playerHand.bet;
    char *result_msg = game_result(&playerHand, &dealerHand, &payout);
    printf("%s\n", result_msg);
    balance += (payout - playerHand.bet);
}

void blackjack_manager() {
    int balance = 500;
    printf("Welcome to Blackjack!\n");

    while (balance > 0) {
        play_blackjack(&balance);
        printf("Continue? (y/n)\n");
        if (!get_input()) {
            break;
        }
    }
    printf("\nYou're broke. Bye\n");
}


// command line call
int main() {
    blackjack_manager();
    return 0;
}
