all: blackjack

blackjack: blackjack.c card_handler.c command_line.c game_result.c blackjack.h
	gcc -o blackjack blackjack.c card_handler.c game_result.c command_line.c
	
