#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "cardStructs.h"

/*  Main logic for Blackjack utility, including 
    call from command line and game loop and
    initialization.
*/
const char* suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const char* ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

void ace_adjuster(Hand* hand){
        for(int i=0; i<hand->cardCount; i++){
                if(hand->cards[i].value == 11){
			if(hand->value > 21){
				hand->value -= 10; // adjusting hand value
                		hand->cards[i].value -= 10; // adjusting ace value from 11 to 1
        		}		
		}
	}
	
}

void draw_card(Card* deck, Hand* hand) {
    // Randomly select a card
    int cardIndex;
    do {
        cardIndex = rand() % NUM_CARDS;
    } while (deck[cardIndex].isDrawn);
    
    deck[cardIndex].isDrawn = 1;

    // Add card to hand
    hand->cards[hand->cardCount] = deck[cardIndex];
    hand->cardCount++;

    hand->value += deck[cardIndex].value;

    // accounting for possible aces
    ace_adjuster(hand);
}

void initialize_hand(Hand* hand) {
    hand->value = 0;
    hand->cardCount = 0;
    hand->bet = 0;
}

void initialize_deck(Card* deck) {
    int idx = 0;
    for (int suit = 0; suit < NUM_SUITS; suit++) {
        for (int rank = 0; rank < NUM_RANKS; rank++) {
            deck[idx].isDrawn = 0;

            // build card name
            strcpy(deck[idx].name, ranks[rank]); 
            strcat(deck[idx].name, " of ");
            strcat(deck[idx].name, suits[suit]);
            
            deck[idx].value = (rank == 12) ? 11 : ((rank >= 9) ? 10 : (rank + 2)); // Face cards have a value of 10, others take their rank
            idx++;
        }
    }
}

void deal_player_hand(Card *deck, Hand *playerHand) {
    // draw initial two cards
    for (int i = 0; i < 2; i++) {
        draw_card(deck, playerHand);
    }
}

/*void player_hit_loop(Card *deck, Hand *playerHand) {
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
}*/

void initialize_cards(Card *deck, Hand *playerHand, Hand*dealerHand){
    initialize_deck(deck);
    initialize_hand(playerHand);
    initialize_hand(dealerHand);
}

bool checkBust(Hand someHand){
    if (someHand.value > 21){
        return true;
    } else{
        return false;
    }
}

void play_dealer(Card *deck, Hand *dealerHand) {
    // Dealer must draw cards until their hand value is at least 17
    while (dealerHand->value < 17) {
        draw_card(deck, dealerHand);
    }
}
// main game logic
/*void play_blackjack(int *balance, Card deck[NUM_CARDS], Hand *playerHand, Hand *dealerHand) {

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
}*/

/*void blackjack_manager() {
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
}*/