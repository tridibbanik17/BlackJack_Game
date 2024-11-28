#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blackjack.h"

/*  Includes functions handling card and
    deck logic and initialization.
*/

const char* suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const char* ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

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

void initialize_hand(Hand* hand) {
    hand->value = 0;
    hand->cardCount = 0;
    hand->bet = 0;
}

// readjusting ace values for a hand of aces being split
void split_ace_adjuster(Hand* hand){
	hand->value = 11;
	hand->cards[0].value = 11;
}

// adjusting hand value based on special value aces
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
