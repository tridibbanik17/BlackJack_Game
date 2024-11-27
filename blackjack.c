#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	scanf(" %c", &input);
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
    return initialBet != 0 ? initialBet : 100;
}

void deal_player_hand(Card *deck, Hand *playerHand) {
    // draw initial two cards
    for (int i = 0; i < 2; i++) {
        draw_card(deck, playerHand);
        printf("You drew: %s\n", playerHand->cards[i].name);
    }
    printf("The value of your hand is: %d\n", playerHand->value);
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

// Function to print the cards in a hand and its total value
void reveal_hand(Hand *hand, const char *card_holder) {
    printf("%s's hand: ", card_holder); // Print whose hand is holding a particular set of cards (i.e., Player or Dealer)
    for (int i = 0; i < hand->cardCount; i++) {
        printf("%s, ", hand->cards[i].name); // Print each card in the hand
    }
    printf("\nValue: %d\n", hand->value); // Print the total value of the hand
}

// Function for the dealer to play its turn
void play_dealer(Card *deck, Hand *dealerHand) {
    // Dealer must draw cards until their hand value is at least 17
    while (dealerHand->value < 17) {
        draw_card(deck, dealerHand);
    }
    reveal_hand(dealerHand, "Dealer");
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
    printf("\nDealer's Turn:\n");
    play_dealer(deck, &dealerHand);

    // handle the game result
    int payout = playerHand.bet;
    char *result_msg = game_result(&playerHand, &dealerHand, &payout);
    printf("\n%s\n", result_msg);
    int balanceDiff =  (payout - playerHand.bet);
    *balance += balanceDiff;
    printf("You bet $%d and earned: $%d\n", playerHand.bet, balanceDiff);
    printf("Current balance: $%d\n\n", *balance);
}

void blackjack_manager() {
    int balance = 500;
    printf("Welcome to Blackjack!\n");
    printf("\nBalance: $%d\n", balance);
    
    play_blackjack(&balance);

    while (balance > 0) {
        printf("Continue? (y/n)\n");
        if (get_input() == false) {
            break;
        }
        play_blackjack(&balance);
    }
    if (balance <= 0) {
        printf("\nYou're broke. Bye\n");
    } else {
        printf("You started with $500 and left with $%d\n", balance);
    }
}


// command line call
int main(int argc, char *argv[]) {
  
    if(argc > 1 && strcmp(argv[1], "--help") == 0){
		display_help();
		exit(0);
    }
    
    blackjack_manager();
    return 0;
}
