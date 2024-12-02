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
 * Checks if player is initally dealt two of the same cards and meets requirements for split. Returns 1 if split is wanted.
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
 * Splits a hand into two playing hands.
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

/* Split_ace_adjuster
 *
 * Readjusting ace values for a hand of aces being split
 */
void split_ace_adjuster(Hand* hand){
	hand->value = 11;
	hand->cards[0].value = 11;
}

/* Ace_adjuster
 * 
 * Adjusting hand value based on special value aces
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

/* Double_down
 *
 * Returns 1 if player wants to double down. If so, readjusts bet for double down
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
