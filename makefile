# Makefile

all: blackjack

blackjack: blackjack.c card_handler.c game_result.c 
	gcc -o blackjack blackjack.c card_handler.c game_result.c

#testing_game_result: testing_game_result.c 
#	gcc -o testing_game_result testing_game_result.c

clean:
	rm -f *.o *.gcda *.gcno *.gcov
