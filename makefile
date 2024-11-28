# Makefile

all: blackjack testing_game_result

blackjack: blackjack.c card_handler.c command_line.c game_result.c special_case.c
	gcc -o blackjack blackjack.c card_handler.c command_line.c game_result.c special_case.c

testing_game_result: testing_game_result.c game_result.c
	gcc -o testing_game_result testing_game_result.c game_result.c

clean:
	rm -f *.o *.gcda *.gcno *.gcov
