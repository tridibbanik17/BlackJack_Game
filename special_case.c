#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "blackjack.h"

/* Special_case handles special cases in BlackJack utility.
 * 
 * 
 * Ace handling - an ace can change value down from 11 to 1 if the hand is going to bust if the ace is counted as an 11. 
 *
 * Split functionality - if player's first two cards are of the same rank, they can choose to treat them as two separate hands. The original bet amount goes on one hand and an equal bet must be made on the other.
 * 
 * Doubling down - after player's first two cards are dealt, player may choose to double their bet amount and end the round after getting dealt one more card. Player can not double down on a split hand.
 */


/* check_split
 *
 * Checks if the player is initially dealt two of the same cards and meets the requirements for a split.
 * Prompts the player for input to confirm if they want to split.
 * Verifies if the player's balance is sufficient for splitting.
 *
 * Parameters:
 * - deck: Pointer to the deck of cards.
 * - playerHand: Pointer to the player's current hand.
 * - balance: Pointer to the player's balance.
 *
 * Returns:
 * - 1 if the player chooses to split and has sufficient balance.
 * - 0 otherwise.
 */
int check_split(Card *deck, Hand *playerHand, int *balance){
    if(playerHand->cards[0].rankIndex != playerHand->cards[1].rankIndex){
    	return 0;
    }	
	    
    printf("You have two %s. Would you like to split? ", playerHand->cards[0].name);
    if(!get_input()){
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
 * Handles the splitting of a hand into two separate hands when the player chooses to split.
 * Adjusts the player's balance for the additional bet and initializes the second hand.
 *
 * Parameters:
 * - deck: Pointer to the deck of cards.
 * - playerHand: Pointer to the player's current hand.
 * - splitHand: Pointer to the newly created split hand.
 * - balance: Pointer to the player's balance.
 */
void handle_split(Card *deck, Hand *playerHand, Hand *splitHand, int *balance){
    printf("You split your hand. Each hand starts with a bet of $%d.\n\n", playerHand->bet);
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

    // checking for aces
    if(playerHand->value == 1){
	    split_ace_adjuster(playerHand);
	    split_ace_adjuster(splitHand);
   }
}

/* split_ace_adjuster
 *
 * Adjusts the value of an ace in a hand that has been split.
 * Ensures the ace is valued at 11 initially.
 *
 * Parameters:
 * - hand: Pointer to the hand that contains an ace to be adjusted.
 */
void split_ace_adjuster(Hand* hand){
	hand->value = 11;
	hand->cards[0].value = 11;
}

/* ace_adjuster
 *
 * Adjusts the value of aces in a hand dynamically based on the hand's total value.
 * Converts aces valued at 11 to 1 if the hand's total value exceeds 21.
 *
 * Parameters:
 * - hand: Pointer to the hand that needs adjustment for aces.
 */
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


/* double_down
 *
 * Allows the player to double down their bet if the conditions are met.
 * Adjusts the player's bet and balance accordingly.
 *
 * Parameters:
 * - hand: Pointer to the player's current hand.
 * - balance: Pointer to the player's balance.
 *
 * Returns:
 * - 1 if the player chooses to double down and has sufficient balance.
 * - 0 otherwise.
 */
int double_down(Hand* hand,int *balance){
	if (hand->cardCount != 2) {
		return 0;
	}
	
	printf("Would you like to double down? ");
    	//*asked = true;

    	if(!get_input()) {
        	return 0;
    	}

	// doubling bet
	if(*balance < hand->bet){
      		printf("Not enough balance to double down.\n");
        	return 0;
        }

	//*balance -= hand->bet;
	hand->bet *= 2;
	printf("Your bet has been doubled to: $%d\n", hand->bet);

	return 1;
}
