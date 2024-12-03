# Makefile

all: blackjack testing_game_result testing_special_case
	
gui_blackjack: guimain.c screens.c command_line.c gui_game_logic.c screens.h cardStructs.h
	gcc guimain.c screens.c command_line.c gui_game_logic.c -o test_gui -lSDL2 -lSDL2_ttf

blackjack: blackjack.c card_handler.c command_line.c game_result.c special_case.c
	gcc -o blackjack blackjack.c card_handler.c command_line.c game_result.c special_case.c -lm

testing_game_result: testing_game_result.c game_result.c
	gcc -o testing_game_result testing_game_result.c game_result.c -lm

testing_special_case: testing_special_case.c special_case.c card_handler.c command_line.c
	gcc -o testing_special_case special_case.c card_handler.c command_line.c testing_special_case.c -lm

clean:
	rm -f *.o *.gcda *.gcno *.gcov blackjack testing_game_result testing_special_case test_gui
