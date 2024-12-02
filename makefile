# Makefile

all: blackjack testing_game_result

blackjack: blackjack.c card_handler.c command_line.c game_result.c special_case.c
	gcc -o blackjack blackjack.c card_handler.c command_line.c game_result.c special_case.c

testing_game_result: testing_game_result.c game_result.c
	gcc -o testing_game_result testing_game_result.c game_result.c

testing_double_down: testing_double_down.c 
	gcc -o testing_double_down testing_double_down.c

testing_handle_split: testing_handle_split.c 
	gcc -o testing_handle_split testing_handle_split.c

testing_check_split: testing_check_split.c 
	gcc -o testing_check_split testing_check_split.c

clean:
	rm -f *.o *.gcda *.gcno *.gcov
