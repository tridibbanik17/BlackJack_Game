#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* display_help
 *
 * Prints a detailed help guide of how to interact with program
 */
void display_help(){
	char help_txt[]=
	"Usage: blackjack [--help]\n"
	"\t\t\t\tplay a game of BlackJack\n"
	"  --help\t\t\tdisplay this help and exit\n\n"
	"Game Rules:\n"
	"  - Start with a balance of $500.\n"
	"  - Enter your bet for each round (Default is $100).\n"
	"  - Try to get a hand value as close to 21 as possible.\n"
	"  - Win or lose money based on the outcome of the round.\n";
	printf("%s", help_txt);
}
