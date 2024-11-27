# Makefile

all: blackjack

<<<<<<< HEAD
blackjack: blackjack.c card_handler.c game_result.c 
	gcc -o blackjack blackjack.c card_handler.c game_result.c

#testing_game_result: testing_game_result.c 
#	gcc -o testing_game_result testing_game_result.c

clean:
	rm -f *.o *.gcda *.gcno *.gcov
=======
blackjack: blackjack.c card_handler.c command_line.c game_result.c blackjack.h
	gcc -o blackjack blackjack.c card_handler.c game_result.c command_line.c
	
>>>>>>> 3b33a54b8bd68433796d14e5236a77d6d3df1917
