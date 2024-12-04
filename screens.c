#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "cardStructs.h"

//menu, set bet, on player turn have game functionality, on continue decide whether to go back to bet or menu
typedef enum {
    MENU,
    BET,
    PLAYER_TURN,
    WIN,
    LOSE_BUST,
    LOSE_DEALWIN,
    CONTINUE,
    GAME_OVER,
    PUSH
} GameState;

/*renders text onto the gui, takes in the renderer object, the font, a string to print, and the coordinates where it'll be placed*/
void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y) {
    SDL_Color color = {255, 255, 255, 255}; // White color
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dst = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

/*renders player hand onto the gui, takes in the renderer object, the font, the hand to print, and the coordinates where it'll be placed*/
void render_player_hand(SDL_Renderer *renderer, TTF_Font *font, Hand *someHand, int x, int y) {
    SDL_Rect cardRectangle;
    cardRectangle.w = 50;
    cardRectangle.h = 80;
    for (int i = 0; i < someHand->cardCount; i++){
        cardRectangle.x = x + i*(cardRectangle.w + 5);
        cardRectangle. y = y;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &cardRectangle);

        //border
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &cardRectangle);

        //name
        char first_letter[2];
        first_letter[0] = someHand->cards[i].name[0];
        first_letter[1] = '\0';
        SDL_Color textColor = {0, 0, 0}; //black text, change later for appropriate suit
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, first_letter, textColor); //also change this when we get symbol
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        //pos in card
        SDL_Rect textRect;
        textRect.x = cardRectangle.x + 15; 
        textRect.y = cardRectangle.y + 25;
        textRect.w = textSurface->w;
        textRect.h = textSurface->h;
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        //Clean up
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

    }
}

/*renders deal onto the gui, takes in the renderer object, the font, a hand to print, and the coordinates where it'll be placed*/
void render_dealer_hand(SDL_Renderer *renderer, TTF_Font *font, Hand *someHand, int x, int y) {
    SDL_Rect cardRectangle;
    cardRectangle.w = 50;
    cardRectangle.h = 80;
    
    cardRectangle.x = x;
    cardRectangle. y = y;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &cardRectangle);

    //border
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &cardRectangle);

    //name
    char first_letter[2];
    first_letter[0] = someHand->cards[0].name[0];
    first_letter[1] = '\0';
    SDL_Color textColor = {0, 0, 0}; //black text, change later for appropriate suit
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, first_letter, textColor); //also change this when we get symbol
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    //pos in card
    SDL_Rect textRect;
    textRect.x = cardRectangle.x + 15; 
    textRect.y = cardRectangle.y + 25;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    //Clean up
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

/*renders the actual frames onto the gui, takes in the renderer object, the font, the state, bet, balance and hands*/
void render_game(SDL_Renderer *renderer, TTF_Font *font, GameState state, char* bet_input, int *balance, Hand *playerHand, Hand *dealerHand){
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); //Green background
    SDL_RenderClear(renderer);
    char strBalance [256];
    int temp = *balance;
    sprintf(strBalance, "Balance: %d", temp);
    int dealerVal;
    int playerVal;
    
    if (state == MENU){
        render_text(renderer, font, "Welcome to Blackjack! (enter to continue)", 100, 50);
    } else if (state == BET){
        render_text(renderer, font, "How much would you like to bet?", 100, 50);
        render_text(renderer, font, "(type in bet amount, and press enter to continue)", 100, 75);
        render_text(renderer, font, bet_input, 100, 550);
        render_text(renderer, font, strBalance, 100, 525);
    } else if (state == PLAYER_TURN) {
        dealerVal = dealerHand->cards[0].value;
        playerVal = playerHand->value;
        char strDealVal [14];
        char strPlayerVal [14];
        sprintf(strDealVal, "(value: %d)", dealerVal);
        sprintf(strPlayerVal, "(value: %d)", playerVal);

        render_text(renderer, font, "Player turn (h to hit, s to stand)", 100, 50);
        render_text(renderer, font, "Dealer Hand:", 100, 175);
        render_text(renderer, font, strDealVal, 280, 175);
        render_dealer_hand(renderer, font, dealerHand, 100, 225);
        render_text(renderer, font, "Player Hand:", 100, 400);
        render_text(renderer, font, strPlayerVal, 280, 400);
        render_player_hand(renderer, font, playerHand, 100, 450);
    } else if (state == WIN) {
        render_text(renderer, font, "You win!! (enter to continue)", 100, 50);
        render_text(renderer, font, "Dealer Hand:", 100, 175);
        render_player_hand(renderer, font, dealerHand, 100, 225);
        render_text(renderer, font, "Player Hand:", 100, 400);
        render_player_hand(renderer, font, playerHand, 100, 450);
    } else if (state == LOSE_BUST) {
        render_text(renderer, font, "BUST! You've lost! (enter to continue)", 100, 50);
        render_text(renderer, font, "Dealer Hand:", 100, 175);
        render_player_hand(renderer, font, dealerHand, 100, 225);
        render_text(renderer, font, "Player Hand:", 100, 400);
        render_player_hand(renderer, font, playerHand, 100, 450);
    } else if (state == LOSE_DEALWIN) {
        render_text(renderer, font, "Dealer wins! You've lost (enter to continue)", 100, 50);
        render_text(renderer, font, "Dealer Hand:", 100, 175);
        render_player_hand(renderer, font, dealerHand, 100, 225);
        render_text(renderer, font, "Player Hand:", 100, 400);
        render_player_hand(renderer, font, playerHand, 100, 450);
    } else if (state == PUSH) {
        render_text(renderer, font, "Push! All bets returned (enter to continue)", 100, 50);
        render_text(renderer, font, "Dealer Hand:", 100, 175);
        render_player_hand(renderer, font, dealerHand, 100, 225);
        render_text(renderer, font, "Player Hand:", 100, 400);
        render_player_hand(renderer, font, playerHand, 100, 450);
    } else if (state == CONTINUE) {
        render_text(renderer, font, "Keep playing ?? (y to keep playing, n to stop)", 100, 50);
    } else if (state == GAME_OVER) {
        render_text(renderer, font, "Game over! (enter to go back to the lobby))", 100, 50);
    }
}