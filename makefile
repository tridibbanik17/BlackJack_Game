all: blackjack

blackjack: blackjack.c card_handler.c
	gcc -o blackjack blackjack.c card_handler.c game_result.c
	