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
        "\nBlackjack Game Help\n"
        "===================\n"
        "Usage:\n"
        "\t\t\t\tblackjack [--help]\n"
        "  --help\t\t\tDisplay this help guide and exit.\n\n"

        "Game Overview:\n"
        "  - The goal of Blackjack is to have a hand value closer to 21 than the dealer's hand,\n"
        "    without exceeding 21 (busting).\n"
        "  - You start with a balance of $500.\n\n"

        "Gameplay:\n"
        "  1. Place a bet for the current round. If you enter 0, the default bet is $100.\n"
        "  2. You will be dealt two cards, and the dealer will reveal one of their cards.\n"
        "  3. You can:\n"
        "     - 'Hit' to draw another card.\n"
        "     - 'Stand' to end your turn and keep your current hand.\n"
        "     - 'Split' (if the first two cards are of the same rank) to play two separate hands.\n"
        "     - 'Double Down' to double your bet and receive one more card (not available on splits).\n"
        "  4. The dealer will draw cards until their hand value is 17 or higher.\n"
        "  5. Results are determined based on the following rules:\n"
        "     - Bust: If your hand value exceeds 21, you lose your bet.\n"
        "     - Blackjack: If your initial hand is exactly 21, you win 2.5x your bet.\n"
        "     - 5-Card Charlie: If you draw 5 cards without busting, you win 2x your bet.\n"
        "     - Push: If your hand value matches the dealer's, you get your bet back.\n"
        "     - Higher Value: If your hand value is higher than the dealer's, you win 2x your bet.\n\n"

        "Key Points:\n"
        "  - Aces are worth 11 points but can count as 1 if it helps avoid a bust.\n"
        "  - Face cards (Jack, Queen, King) are worth 10 points.\n"
        "  - Number cards are worth their face value.\n"
        "  - Splitting and doubling down require sufficient balance.\n\n"

        "Commands During Gameplay:\n"
        "  - 'y' or 'n' for yes/no questions (e.g., whether to hit or continue).\n"
        "  - Input your bet amount when prompted.\n\n"

        "Ending the Game:\n"
        "  - The game continues until you choose to stop or your balance reaches $0.\n"
        "  - Enjoy playing and try to leave with a higher balance than you started!\n\n";

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
