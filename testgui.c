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
        
    } else {
        //test case failed
    }

    if (checkBust(testHand2) == false){
        //test case passed
    } else {
        //test case failed
    }

    if (checkBust(testHand3) == false){
        //test case passed
    } else {
        //test case failed
    }

    GameState state = MENU;
    int balance1 = 500;
    int balance2 = -100;


    if (checkBalance(balance1) == CONTINUE){
        //test case passed
    } else {
        //test case failed
    }

    if (checkBalance(balance2) == GAME_OVER){
        //test case passed
    } else {
        //test case failed
    }

    state = WIN;
    update_balance(&balance1, 100, state);

    if (balance1 == 600){ 
        //test case passed
    } else {
        //test case failed
    }

    balance1 = 500;
    state = LOSE_BUST;
    update_balance(&balance1, 100, state);

    if (balance1 == 400){
        //test case passed
    } else {
        //tese case failed
    }


    initialize_cards(deck, &playerHand, &dealerHand);
    deal_player_hand(deck, &playerHand);
    deal_player_hand(deck, &dealerHand);

    if (playerHand.cardCount == 2 && dealerHand.cardCount == 2){
        //test case passed
    } else {
        //test case failed
    }

    draw_card(deck, &playerHand);

    if (playerHand.cardCount == 3){
        //test case passed
    } else {
        //test case failed
    }

    play_dealer(deck, &dealerHand);

    if (dealerHand.value > 17){
        //test case passed
    } else {
        //text case failed
    }
}