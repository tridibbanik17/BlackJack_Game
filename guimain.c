#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "screens.h"
#include "gui_game_logic.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char *argv[]) {

    if(argc > 1 && strcmp(argv[1], "--help") == 0){
		display_help();
		return 0;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0) {
        printf("Failed to initialize SDL or TTF: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Blackjack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Failed to create window: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return -1;
    }

    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 24);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return -1;
    }

    GameState state = MENU;
    int balance;
    int bet;
    char bet_input[256] = "$";
    Card deck [NUM_CARDS];
    Hand playerHand;
    Hand dealerHand;
    bool activeRound = false;

    
    bool running = true;
    SDL_Event event;
    while (running){
        if (state == MENU){
            while(SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym){
                        case SDLK_RETURN:
                            printf("enter key pressed!");
                            balance = 500;
                            state = BET;
                            break;
                        default:
                            printf("The %d key was pressed", event.key.keysym.sym);
                            break;
                    }
                }
            }
        } else if (state == BET){
            while(SDL_PollEvent(&event)) {
                initialize_cards(deck, &playerHand, &dealerHand);
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_TEXTINPUT) {
                    if (isdigit(event.text.text[0]) && strlen(bet_input) < sizeof(bet_input) - 1){
                        strcat(bet_input, event.text.text);
                    }
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym){
                        case SDLK_BACKSPACE:
                            if (strlen(bet_input) > 0){
                                bet_input[strlen(bet_input) - 1] = '\0';
                            }
                            break;
                        case SDLK_RETURN:
                            printf("enter key pressed!");
                            //smt here
                            int bet = atoi(bet_input);
                            state = PLAYER_TURN;
                            break;
                        default:
                            printf("The %d key was pressed", event.key.keysym.sym);
                            break;
                    }
                }
            }
        } else if (state == PLAYER_TURN) {
            while(SDL_PollEvent(&event)) {
                if (activeRound == false){
                    deal_player_hand(deck, &playerHand);
                    deal_player_hand(deck, &dealerHand);
                    activeRound = true;
                }
                if (checkBust(playerHand)){
                    printf("PLAYER BUST!");
                    state = LOSE_BUST;
                }
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym){
                        case SDLK_h:
                            draw_card(deck, &playerHand);
                            printf("h key pressed!");
                            printf("The current value of player hand is, %d", playerHand.value);
                            break;
                        case SDLK_s:
                            printf("the s key was pressed!");
                            play_dealer(deck, &dealerHand);
                            //this below should be a function tbh
                            if (checkBust(dealerHand)){
                                printf("dealer bust!");
                                state = WIN;
                            } else if (dealerHand.value == playerHand.value){
                                printf("Push!");
                                state = PUSH;
                            } else if (dealerHand.value > playerHand.value){
                                printf("dealer wins!");
                                state = LOSE_DEALWIN;
                            } else if (dealerHand.value < playerHand.value){
                                printf("Player wins!!");
                                state = WIN;
                            }
                            activeRound = false;
                            break;
                        default:
                            printf("The %d key was pressed", event.key.keysym.sym);
                            break;
                    }
                }
            }
        } else if (state == WIN) {
            while(SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym){
                        case SDLK_RETURN:
                            balance += bet;
                            printf("enter key pressed!");
                            state = CONTINUE;
                            break;
                        default:
                            printf("The %d key was pressed", event.key.keysym.sym);
                            break;
                    }
                }
            }
        } else if (state == LOSE_BUST) {
            while(SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym){
                        case SDLK_RETURN:
                            printf("The balance before subtraction is: %d", balance);
                            printf("The current bet is: %d", bet);
                            balance = balance - bet;
                            printf("The current balance is: %d", balance);
                            printf("enter key pressed!");
                            if (balance > 0){
                                state = CONTINUE;
                            } else {
                                state = GAME_OVER;
                            }
                            break;
                        default:
                            printf("The %d key was pressed", event.key.keysym.sym);
                            break;
                    }
                }
            }
        } else if (state == LOSE_DEALWIN) {
            while(SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym){
                        case SDLK_RETURN:
                            balance -= bet;
                            printf("enter key pressed!");
                            //should also be a function below
                            if (balance > 0){
                                state = CONTINUE;
                            } else {
                                state = GAME_OVER;
                            }
                            break;
                        default:
                            printf("The %d key was pressed", event.key.keysym.sym);
                            break;
                    }
                }
            }
        } else if (state == PUSH) {
            while(SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym){
                        case SDLK_RETURN:
                            printf("enter key pressed!");
                            state = BET;
                            break;
                        default:
                            printf("The %d key was pressed", event.key.keysym.sym);
                            break;
                    }
                }
            }
        } else if (state == CONTINUE) {
            while(SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym){
                        case SDLK_y:
                            printf("y key pressed!");
                            state = BET;
                            break;
                        case SDLK_n:
                            printf("n key pressed!");
                            state = MENU;
                            break;
                        default:
                            printf("The %d key was pressed", event.key.keysym.sym);
                            break;
                    }
                }
            }
        } else if (state == GAME_OVER) {
            while(SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym){
                        case SDLK_RETURN:
                            printf("enter key pressed!");
                            state = MENU;
                            break;
                        default:
                            printf("The %d key was pressed", event.key.keysym.sym);
                            break;
                    }
                }
            }
        }
        render_game(renderer, font, state, bet_input, balance, &playerHand, &dealerHand);
        SDL_RenderPresent(renderer);

    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}