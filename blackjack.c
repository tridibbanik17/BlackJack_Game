#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "blackjack.h"

/* Main logic for Blackjack utility, including 
   command-line invocation, game loop, and initialization.
*/

/* 
 * Function: get_initial_bet
 * --------------------------
 * Prompts the player to enter the initial bet amount.
 * 
 * Parameters: None
 * Returns: 
 *   int - The valid bet amount (positive integer) entered by the user.
 *         Defaults to $100 if the user enters 0.
 */
int get_initial_bet() {
    int initialBet;

    while (true) {
        printf("Enter the bet amount (must be a positive integer): $");
        if (scanf("%d", &initialBet) == 1) {
            if (initialBet > 0) return initialBet;
            else if (initialBet == 0) {
                printf("Defaulting bet to $100 since you entered 0.\n");
                return 100;
            } else printf("Invalid input! The bet must be a positive integer.\n");
        } else {
            printf("Invalid input! Please enter a valid positive integer.\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    }
}

/* 
 * Function: deal_player_hand
 * --------------------------
 * Deals the initial two cards to the player's hand.
 * 
 * Parameters:
 *   Card *deck       - Pointer to the deck of cards.
 *   Hand *playerHand - Pointer to the player's hand structure.
 * Returns: None
 */
void deal_player_hand(Card *deck, Hand *playerHand) {
    for (int i = 0; i < 2; i++) {
        draw_card(deck, playerHand);
        printf("You drew: %s\n", playerHand->cards[i].name);
    }
    printf("The value of your hand is: %d\n", playerHand->value);
}

/* 
 * Function: hit
 * -------------
 * Adds a single card to the player's hand and displays its updated value.
 * 
 * Parameters:
 *   Card *deck       - Pointer to the deck of cards.
 *   Hand *playerHand - Pointer to the player's hand structure.
 * Returns: None
 */
void hit(Card *deck, Hand *playerHand) {
    draw_card(deck, playerHand);
    printf("You drew: %s\n", playerHand->cards[playerHand->cardCount - 1].name);
    printf("Your hand value is: %d\n", playerHand->value);
}

/* 
 * Function: player_hit_loop
 * --------------------------
 * Allows the player to repeatedly draw cards until they decide to stop or bust.
 * 
 * Parameters:
 *   Card *deck       - Pointer to the deck of cards.
 *   Hand *playerHand - Pointer to the player's hand structure.
 *   int *balance     - Pointer to the player's current balance.
 * Returns: None
 */
void player_hit_loop(Card *deck, Hand *playerHand, int *balance) {
    char continuePlaying;
    do {
        while (true) {
            printf("Would you like to draw another card? (y/n): ");
            scanf(" %c", &continuePlaying);
            if (continuePlaying == 'y' || continuePlaying == 'Y' || 
                continuePlaying == 'n' || continuePlaying == 'N') break;
            else {
                printf("Invalid input! Please enter 'y' or 'n'.\n");
                while (getchar() != '\n');
            }
        }
        if (continuePlaying == 'y' || continuePlaying == 'Y') {
            draw_card(deck, playerHand);
            printf("You drew: %s\n", playerHand->cards[playerHand->cardCount - 1].name);
            printf("Your hand value is: %d\n", playerHand->value);
            if (playerHand->value > 21 || playerHand->cardCount >= NUM_CHARLIE) break;
        }
    } while (continuePlaying == 'y' || continuePlaying == 'Y');
}

/* 
 * Function: get_result
 * ---------------------
 * Determines the result of the game and updates the player's balance.
 * 
 * Parameters:
 *   Hand *dealerHand - Pointer to the dealer's hand structure.
 *   Hand *playerHand - Pointer to the player's hand structure.
 *   int *balance     - Pointer to the player's current balance.
 * Returns: None
 */
void get_result(Hand *dealerHand, Hand *playerHand, int *balance) {
    int payout = playerHand->bet;
    char *result_msg = game_result(playerHand, dealerHand, &payout);
    printf("\n%s\n", result_msg);
    int balanceDiff = (payout - playerHand->bet);
    *balance += balanceDiff;
    printf("You bet $%d and earned: $%d\n", playerHand->bet, balanceDiff);
}

/* 
 * Function: reveal_hand
 * ----------------------
 * Displays the cards and total value of a hand.
 * 
 * Parameters:
 *   Hand *hand         - Pointer to the hand structure to display.
 *   const char *holder - String indicating the owner of the hand (e.g., "Player" or "Dealer").
 * Returns: None
 */
void reveal_hand(Hand *hand, const char *card_holder) {
    printf("%s's hand: ", card_holder);
    for (int i = 0; i < hand->cardCount; i++) {
        printf("%s, ", hand->cards[i].name);
    }
    printf("\nValue: %d\n", hand->value);
}

/* 
 * Function: play_dealer
 * ----------------------
 * Executes the dealer's turn logic.
 * 
 * Parameters:
 *   Card *deck       - Pointer to the deck of cards.
 *   Hand *dealerHand - Pointer to the dealer's hand structure.
 * Returns: None
 */
void play_dealer(Card *deck, Hand *dealerHand) {
    while (dealerHand->value < 17) draw_card(deck, dealerHand);
    reveal_hand(dealerHand, "Dealer");
}

/* 
 * Function: play_blackjack
 * -------------------------
 * Manages a single round of Blackjack.
 * 
 * Parameters:
 *   int *balance - Pointer to the player's current balance.
 * Returns: None
 */
void play_blackjack(int *balance) {
    Card deck[NUM_CARDS];
    Hand playerHand, splitHand;
    Hand dealerHand;
    srand((unsigned int)time(NULL));
    initialize_deck(deck);
    initialize_hand(&playerHand);
    initialize_hand(&dealerHand);
    int initialBet = get_initial_bet();
    playerHand.bet = initialBet;
    deal_player_hand(deck, &playerHand);
    int split_result = check_split(deck, &playerHand, balance);
    if (split_result) {
        handle_split(deck, &playerHand, &splitHand, balance);
        printf("Playing first hand:\n");
        player_hit_loop(deck, &playerHand, balance);
        printf("\nPlaying split hand:\n");
        player_hit_loop(deck, &splitHand, balance);
    } else {
        if (double_down(&playerHand, balance)) hit(deck, &playerHand);
        else player_hit_loop(deck, &playerHand, balance);
    }
    printf("\nDealer's Turn:\n");
    play_dealer(deck, &dealerHand);
    if (split_result) printf("\nFirst hand:");
    get_result(&dealerHand, &playerHand, balance);
    if (split_result) {
        printf("\nSplit hand:");
        get_result(&dealerHand, &splitHand, balance);
    }
    printf("Current balance: $%d\n\n", *balance);
}

/* 
 * Function: blackjack_manager
 * ----------------------------
 * Main manager function for Blackjack game.
 * 
 * Parameters: None
 * Returns: None
 */
void blackjack_manager() {
    int balance = 500;
    printf("\nWelcome to Blackjack!\n");
    printf("Balance: $%d\n", balance);
    play_blackjack(&balance);
    while (balance > 0) {
        printf("Start another round? \n");
        if (get_input() == false) break;
        play_blackjack(&balance);
    }
    if (balance <= 0) printf("\nYou're broke. Bye.\n");
    else printf("You started with $500 and left with $%d\n", balance);
}

/* 
 * Function: main
 * --------------
 * Entry point of the Blackjack program.
 * 
 * Parameters:
 *   int argc      - Number of command-line arguments.
 *   char *argv[]  - Array of command-line argument strings.
 * Returns: 
 *   int - Exit status of the program.
 */
int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        display_help();
        exit(0);
    }
    blackjack_manager();
    return 0;
}
