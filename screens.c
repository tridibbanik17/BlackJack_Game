#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y) {
    SDL_Color color = {255, 255, 255, 255}; // White color
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dst = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void render_game(SDL_Renderer *renderer, TTF_Font *font, GameState state, char* bet_input, int balance){
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); // Green background
    SDL_RenderClear(renderer);
    if (state == MENU){
        render_text(renderer, font, "Welcome to Blackjack! (enter to continue)", 100, 50);
    } else if (state == BET){
        render_text(renderer, font, "How much would you like to bet? (enter to continue)", 100, 50);
        render_text(renderer, font, bet_input, 100, 550);
    } else if (state == PLAYER_TURN) {
        render_text(renderer, font, "Player turn (h to hit, s to stand", 100, 50);
    } else if (state == WIN) {
        render_text(renderer, font, "You win!! (enter to continue)", 100, 50);
        //add line for bet multiplier
    } else if (state == LOSE_BUST) {
        render_text(renderer, font, "BUST! You've lost! (enter to continue)", 100, 50);
    } else if (state == LOSE_DEALWIN) {
        render_text(renderer, font, "Dealer wins! You've lost (enter to continue)", 100, 50);
    } else if (state == PUSH) {
        render_text(renderer, font, "Push! All bets returned (enter to continue)", 100, 50);
    } else if (state == CONTINUE) {
        render_text(renderer, font, "Keep playing ?? (y to keep playing, n to stop)", 100, 50);
    } else if (state == GAME_OVER) {
        render_text(renderer, font, "Game over! (enter to go back to the lobby))", 100, 50);
    }
}