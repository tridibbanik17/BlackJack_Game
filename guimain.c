#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "blackjack.h"
#include "screens.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char *argv[]) {

    GameState state = MENU;
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
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym){
                        case SDLK_RETURN:
                            printf("enter key pressed!");
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
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym){
                        case SDLK_w:
                            printf("w key pressed!");
                            state = WIN;
                            break;
                        case SDLK_b:
                            printf("b key was pressed");
                            state = LOSE_BUST;
                            break;
                        case SDLK_d:
                            printf("the d key was pressed");
                            state = LOSE_DEALWIN;
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
                        case SDLK_c:
                            printf("c key pressed!");
                            state = CONTINUE;
                            break;
                        case SDLK_g:
                            printf("the g key was pressed!");
                            state = GAME_OVER;
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
                        case SDLK_c:
                            printf("the c key pressed!");
                            state = CONTINUE;
                            break;
                        case SDLK_g:
                            printf("the g key was pressed");
                            state = GAME_OVER;
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
        render_game(renderer, font, state);
        SDL_RenderPresent(renderer);

    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}