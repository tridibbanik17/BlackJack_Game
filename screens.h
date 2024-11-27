typedef enum {
    MENU,
    BET,
    PLAYER_TURN,
    WIN,
    LOSE_BUST,
    LOSE_DEALWIN,
    CONTINUE,
    GAME_OVER
} GameState;

void render_game(SDL_Renderer *renderer, TTF_Font *font, GameState state);