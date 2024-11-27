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

/* get_input
 *
 * returns whether user input is yes or not
 */
 bool get_input(){
    char input;
    scanf(" %c", &input);
    if (input == 'y' || input == 'Y') {
        return true;
    }
    else if(input == 'n' || input == 'N'){
	return false;
    }
    else{
	printf("Invalid input. Please enter 'y' or 'n'.\n");
        return get_input();
    }
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


/* check_split
 *
 * Checks if player is initally dealt two of the same cards and meets requirements for split. Returns 1 if split is wanted.
 */
int check_split(Card *deck, Hand *playerHand, int *balance){
    // NEED TO CHECK FOR SAME RANK -> ONLY CHECKS FOR POINT VALUE RN
    if(playerHand->cards[0].value == playerHand->cards[1].value){
        printf("You have two %s. Would you like to split? (y/n): ", playerHand->cards[0].name);
        if(!get_input()){
                return 0;
        }
    }
    else{
    	return 0;
    }
    
    // splitting hand places an additional bet
    if(*balance < playerHand->bet){
      printf("Not enough balance to split.\n");
        return 0;
    }
    return 1;
}

/* handle_split
 *
 * Splits a hand into two playing hands.
 */
void handle_split(Card *deck, Hand *playerHand, Hand *splitHand, int *balance){
    printf("You split your hand. Each hand starts with a bet of $%d.\n", playerHand->bet);
    *balance -= playerHand->bet;

    // initialize the split hand
    initialize_hand(splitHand);
    splitHand->bet = playerHand->bet;

    // move second card to split hand
    playerHand->value -= playerHand->cards[1].value;
    splitHand->cards[0] = playerHand->cards[1];
    splitHand->cardCount++;
    playerHand->cardCount--;
    splitHand->value += splitHand->cards[0].value;
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

void get_result(Hand *dealerHand, Hand *playerHand, int *balance){
	int payout = playerHand->bet;
    	char *result_msg = game_result(playerHand, dealerHand, &payout);
    	printf("\n%s\n", result_msg);

    	int balanceDiff =  (payout - playerHand->bet);
    	*balance += balanceDiff;
    	printf("You bet $%d and earned: $%d\n", playerHand->bet, balanceDiff);
}

// main game logic
void play_blackjack(int *balance) {
    // initialization
    Card deck[NUM_CARDS];
    Hand playerHand, splitHand;
    Hand dealerHand;
    srand((unsigned int)time(NULL)); // Setup random seed

    initialize_deck(deck);
    initialize_hand(&playerHand);
    initialize_hand(&dealerHand);
    int initialBet = get_initial_bet();
    playerHand.bet = initialBet;

    deal_player_hand(deck, &playerHand);

    // checking and handling for split hand
    int split_result = check_split(deck, &playerHand, balance); 
    if(split_result){
	    handle_split(deck, &playerHand, &splitHand, balance);
	    
	    printf("Playing first hand:\n");
            player_hit_loop(deck, &playerHand);

            printf("\nPlaying split hand:\n");
            player_hit_loop(deck, &splitHand);
    }
    else{
    	// player hit/stand loop
    	player_hit_loop(deck, &playerHand);
    }

    // dealer's turn
    printf("\nDealer's Turn:\n");
    play_dealer(deck, &dealerHand);

    // handle the game result
    if(split_result) printf("\nFirst hand:");

    get_result(&dealerHand, &playerHand, balance);
    
    if(split_result){
	    printf("\nSplit hand:");
            get_result(&dealerHand, &splitHand, balance);
    }

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
