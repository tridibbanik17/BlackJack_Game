# Makefile

all: blackjack testing_game_result

blackjack: blackjack.c card_handler.c command_line.c game_result.c blackjack.h
	gcc -o blackjack blackjack.c card_handler.c game_result.c command_line.c
	
gui_blackjack: guimain.c screens.c command_line.c gui_game_logic.c screens.h cardStructs.h
	gcc guimain.c screens.c command_line.c gui_game_logic.c -o test_gui -lSDL2 -lSDL2_ttf

clean:
	rm -f *.o *.gcda *.gcnp *.gcov