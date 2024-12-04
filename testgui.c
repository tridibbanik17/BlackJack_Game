#include <stdio.h>
#include <stdlib.h>
#include "guimain.h"

int main(){
    Card deck [NUM_CARDS];
    Hand testHand1;
    Hand testHand2;
    Hand testHand3;

    Hand playerHand;
    Hand dealerHand;

    display_help();

    /*arbritrary numbers, except for value, over or under 21*/
    testHand1.value = 22;
    testHand1.cardCount = 1;
    testHand1.bet = 200;

    testHand2.value = 22;
    testHand2.cardCount = 1;
    testHand2.bet = 200;

    testHand3.value = 21;
    testHand3.cardCount = 1;
    testHand3.bet = 200;

    if (checkBust(testHand1) == true){
        printf("Test 1 Passed");
    } else {
        printf("Test 1 Failed");
    }

    if (checkBust(testHand2) == false){
        printf("Test 2 Passed");
    } else {
        printf("Test 2 Failed");
    }

    if (checkBust(testHand3) == false){
        printf("Test 3 Passed");
    } else 
        printf("Test 3 Failed");
    }

    GameState state = MENU;
    int balance1 = 500;
    int balance2 = -100;


    if (checkBalance(balance1) == CONTINUE){
        printf("Test 4 Passed");
    } else {
        printf("Test 4 Failed");
    }

    if (checkBalance(balance2) == GAME_OVER){
        printf("Test 5 Passed");
    } else {
        printf("Test 5 Failed");
    }

    state = WIN;
    update_balance(&balance1, 100, state);

    if (balance1 == 600){ 
        printf("Test 6 Passed");
    } else {
        printf("Test 6 Failed");
    }

    balance1 = 500;
    state = LOSE_BUST;
    update_balance(&balance1, 100, state);

    if (balance1 == 400){
        printf("Test 7 Passed");
    } else {
        printf("Test 7 Failed");
    }


    initialize_cards(deck, &playerHand, &dealerHand);
    deal_player_hand(deck, &playerHand);
    deal_player_hand(deck, &dealerHand);

    if (playerHand.cardCount == 2 && dealerHand.cardCount == 2){
        printf("Test 8 Passed");
    } else {
        printf("Test 8 Failed");
    }

    draw_card(deck, &playerHand);

    if (playerHand.cardCount == 3){
        printf("Test 9 Passed");
    } else {
        printf("Test 9 Failed");
    }

    play_dealer(deck, &dealerHand);

    if (dealerHand.value > 17){
        printf("Test 10 Passed");
    } else {
        printf("Test 10 Failed");
    }
}