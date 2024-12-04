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

/*checks if balance is above 0, to see if game is over or if player can keep playing, takes in balance
 * returns the appropriate game state depending on the balance
 */
GameState checkBalance(int balance) {
    if (balance > 0){
        return CONTINUE;
    } else {
        return GAME_OVER;
    }

}

/*updates the balance depending on if the player won or lost
 * takes in a pointer to the balance (so that it can be updated), the bet amount, and the game state
 */
void update_balance(int *balance, int bet, GameState state) {
    if (state == WIN) {
        *balance += bet;
    } else {
        *balance -= bet;
    }
}

int main(int argc, char *argv[]) {

    /*if only the --help string is called, print it*/
    if(argc > 1 && strcmp(argv[1], "--help") == 0){
		display_help();
		return 0;
    }

    /*initialize all the gui stuff*/
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

    /*intialize all game values*/
    GameState state = MENU;
    int balance = 500;
    int bet;
    char bet_input[256] = "$";
    Card deck [NUM_CARDS];
    Hand playerHand;
    Hand dealerHand;

    
    bool running = true;
    SDL_Event event;
    while (running){
        /*handle inputs, depending on the game state*/
        if (state == MENU){
            while(SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym){
                        case SDLK_RETURN:
                            printf("enter key pressed!\n");
                            balance = 500;
                            state = BET;
                            break;
                        default:
                            printf("The %d key was pressed \n", event.key.keysym.sym);
                            break;
                    }
                }
            }
        } else if (state == BET){
            while(SDL_PollEvent(&event)) {
                initialize_cards(deck, &playerHand, &dealerHand);
                deal_player_hand(deck, &playerHand);
                deal_player_hand(deck, &dealerHand);
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_TEXTINPUT) {
                    if (isdigit(event.text.text[0]) && strlen(bet_input) < sizeof(bet_input) - 1){
                        strcat(bet_input, event.text.text);
                    }
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym){
                        case SDLK_BACKSPACE:
                            if (strlen(bet_input) > 1){
                                bet_input[strlen(bet_input) - 1] = '\0';
                            }
                            break;
                        case SDLK_RETURN:
                            printf("enter key pressed! \n");
                            bet = atoi(&bet_input[1]);
                            if ((bet <= balance) && (0 < bet)){
                                state = PLAYER_TURN;
                            }
                            break;
                        default:
                            printf("The %d key was pressed \n", event.key.keysym.sym);
                            break;
                    }
                }
            }
        } else if (state == PLAYER_TURN) {
            while(SDL_PollEvent(&event)) {
                if (checkBust(playerHand)){
                    printf("PLAYER BUST! \n");
                    state = LOSE_BUST;
                }
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym){
                        case SDLK_h:
                            draw_card(deck, &playerHand);
                            printf("h key pressed! \n");
                            break;
                        case SDLK_s:
                            printf("the s key was pressed! \n");
                            play_dealer(deck, &dealerHand);
                            if (checkBust(dealerHand)){
                                printf("dealer bust! \n");
                                state = WIN;
                            } else if (dealerHand.value == playerHand.value){
                                printf("Push! \n");
                                state = PUSH;
                            } else if (dealerHand.value > playerHand.value){
                                printf("dealer wins! \n");
                                state = LOSE_DEALWIN;
                            } else {
                                printf("Player wins!! \n");
                                state = WIN;
                            }
                            break;
                        default:
                            printf("The %d key was pressed \n", event.key.keysym.sym);
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
                            update_balance(&balance, bet, state);
                            state = checkBalance(balance);
                            printf("enter key pressed! \n");
                            state = CONTINUE;
                            break;
                        default:
                            printf("The %d key was pressed \n", event.key.keysym.sym);
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
                            update_balance(&balance, bet, state);
                            state = checkBalance(balance);
                            break;
                        default:
                            printf("The %d key was pressed \n", event.key.keysym.sym);
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
                            update_balance(&balance, bet, state);
                            printf("enter key pressed! \n");
                            state = checkBalance(balance);
                            break;
                        default:
                            printf("The %d key was pressed \n", event.key.keysym.sym);
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
                            printf("enter key pressed! \n");
                            state = BET;
                            break;
                        default:
                            printf("The %d key was pressed \n", event.key.keysym.sym);
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
                            printf("y key pressed! \n");
                            state = BET;
                            break;
                        case SDLK_n:
                            printf("n key pressed! \n");
                            state = MENU;
                            break;
                        default:
                            printf("The %d key was pressed \n", event.key.keysym.sym);
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
                            printf("enter key pressed! \n");
                            state = MENU;
                            break;
                        default:
                            printf("The %d key was pressed \n", event.key.keysym.sym);
                            break;
                    }
                }
            }
        }
        //update renderer, and the present the new gui to the screen
        render_game(renderer, font, state, bet_input, &balance, &playerHand, &dealerHand);
        SDL_RenderPresent(renderer);

    }

    //close the gui when finished
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}