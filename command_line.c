#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blackjack.h"
#include <stdbool.h>

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

/* get_true_input
 *
 * returns whether user input is yes or not
 */
bool get_true_input(){
	char input;
	scanf("%c", &input);
        if (input == 'y' || input == 'Y') {
		return true;
	}
	return false;
}



bool get_input() {
    char input;
    while (true) { // Loop until valid input is provided
        printf("Enter your choice (y/n): ");
	scanf(" %c", &input);
	// Check if the input is valid
        if (input == 'y' || input == 'Y') {
            return true;
        } else if (input == 'n' || input == 'N') {
            return false;
        } else {
            // Invalid input: Print an error message and prompt again
            printf("Invalid input! Please type 'y' for yes or 'n' for no.\n");
            // Clear the input buffer
            while (getchar() != '\n'); 
        }
    }
}	
