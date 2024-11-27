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

void render_game(SDL_Renderer *renderer, TTF_Font *font, GameState state, char* bet_input);

void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y);

int initgui(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font);