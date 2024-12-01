#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blackjack.h"
#include <stdbool.h>

/* 
 * Function: display_help
 * -----------------------
 * Prints a detailed help guide for the program.
 * Provides information on usage, options, and game rules.
 * 
 * Parameters: None
 * Returns: None
 */
void display_help(){
    char help_txt[] =
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

/* 
 * Function: get_input
 * --------------------
 * Prompts the user for input and checks if it is a valid yes ('y'/'Y') or no ('n'/'N') response.
 * Loops until valid input is provided.
 * 
 * Parameters: None
 * Returns: 
 *   bool - true if the user inputs 'y' or 'Y', false if 'n' or 'N'.
 */
bool get_input() {
    char input; // Variable to store the user's input
    while (true) { // Loop until valid input is provided
        printf("Enter your choice (y/n): "); // Prompt the user
        scanf(" %c", &input); // Read a character input from the user
        
        // Check if the input is a valid 'yes' or 'no'
        if (input == 'y' || input == 'Y') {
            return true; // Return true for 'yes'
        } else if (input == 'n' || input == 'N') {
            return false; // Return false for 'no'
        } else {
            // Handle invalid input
            printf("Invalid input! Please type 'y' for yes or 'n' for no.\n");
            // Clear the input buffer to avoid errors
            while (getchar() != '\n');
        }
    }
} 
