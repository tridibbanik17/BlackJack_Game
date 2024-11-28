#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "blackjack.h"

/*  Main logic for Blackjack utility, including 
    call from command line and game loop and
    initialization.
*/

int get_initial_bet() {
    int initialBet;

    while (true) { // Loop until valid input is provided
        printf("Enter the bet amount (must be a positive integer): $");

        // Validate input using scanf
        if (scanf("%d", &initialBet) == 1) {
            // Check if the value is positive
            if (initialBet > 0) {
                return initialBet; // Valid positive integer
            } else if (initialBet == 0) {
                printf("Defaulting bet to $100 since you entered 0.\n");
                return 100; // Default value for 0
            } else {
                // Negative number entered
                printf("Invalid input! The bet must be a positive integer.\n");
            }
        } else {
            // Non-integer input entered
            printf("Invalid input! Please enter a valid positive integer.\n");

            // Clear the input buffer
            while (getchar() != '\n');
        }
    }
}

void deal_player_hand(Card *deck, Hand *playerHand) {
    // draw initial two cards
    for (int i = 0; i < 2; i++) {
        draw_card(deck, playerHand);
        printf("You drew: %s\n", playerHand->cards[i].name);
    }
    printf("The value of your hand is: %d\n", playerHand->value);
}


void hit(Card *deck, Hand *playerHand){
	draw_card(deck, playerHand);
        printf("You drew: %s\n", playerHand->cards[playerHand->cardCount - 1].name);
        printf("Your hand value is: %d\n", playerHand->value);
}

void player_hit_loop(Card *deck, Hand *playerHand, int *balance) {
    char continuePlaying;
    int double_result; // if player wants to double down
    do {
	double_result = double_down(playerHand, balance);
	if(double_result){
		hit(deck, playerHand);
		break;
	}

        // Loop to ensure valid input
        while (true) {
            printf("Would you like to draw another card? (y/n): ");
            scanf(" %c", &continuePlaying);

            // Check if input is valid
            if (continuePlaying == 'y' || continuePlaying == 'Y' || 
                continuePlaying == 'n' || continuePlaying == 'N') {
                break; // Exit the validation loop if valid
            } else {
                printf("Invalid input! Please enter 'y' or 'n'.\n");
                // Clear input buffer in case of invalid input
                while (getchar() != '\n');
            }
        }
        if (continuePlaying == 'y' || continuePlaying == 'Y') {
            draw_card(deck, playerHand);
            printf("You drew: %s\n", playerHand->cards[playerHand->cardCount - 1].name);
            printf("Your hand value is: %d\n", playerHand->value);

            if (playerHand->value > 21 || playerHand->cardCount >= NUM_CHARLIE) {
                //printf("Bust! Your hand value exceeded 21. Game over.\n");
                break;
            }
        }
    } while ((continuePlaying == 'y' || continuePlaying == 'Y'));
}		       


void get_result(Hand *dealerHand, Hand *playerHand, int *balance){
	int payout = playerHand->bet;
    	char *result_msg = game_result(playerHand, dealerHand, &payout);
    	printf("\n%s\n", result_msg);

    	int balanceDiff =  (payout - playerHand->bet);
    	*balance += balanceDiff;
    	printf("You bet $%d and earned: $%d\n", playerHand->bet, balanceDiff);
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
    Hand playerHand, splitHand;
    Hand dealerHand;
    srand((unsigned int)time(NULL)); // Setup random seed

    initialize_deck(deck);
    initialize_hand(&playerHand);
    initialize_hand(&dealerHand);
    int initialBet = get_initial_bet();
    playerHand.bet = initialBet;

    deal_player_hand(deck, &playerHand);
    // checking if player wants to double down
    int double_result = double_down(&playerHand, balance);

    // checking and handling for split hand
    int split_result = check_split(deck, &playerHand, balance);
    
    if(split_result){
	    handle_split(deck, &playerHand, &splitHand, balance);
	    
	    printf("Playing first hand:\n");
	    printf("The value of your hand is: %d\n", playerHand.value);
	    player_hit_loop(deck, &playerHand, balance);
	    
	    
            printf("\nPlaying split hand:\n");
	    printf("The value of your hand is: %d\n", splitHand.value);
            player_hit_loop(deck, &splitHand, balance);
    }else{
    	// player hit/stand loop
	player_hit_loop(deck, &playerHand, balance);
    	
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
    printf("\nWelcome to Blackjack!\n");
    printf("Balance: $%d\n", balance);
    
    play_blackjack(&balance);

    while (balance > 0) {
        printf("Continue? \n");
        if (get_input() == false) {
            break;
        }
        play_blackjack(&balance);
    }
    if (balance <= 0) {
        printf("\nYou're broke. Bye.\n");
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
