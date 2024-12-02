#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "blackjack.h"

// Function to run a specific test scenario
void run_scenario(int scenario) {
    // Mock variables
    Card deck[NUM_CARDS];
    Hand playerHand, splitHand;
    int balance = 100;

    // Initialize variables
    initialize_hand(&playerHand);
    initialize_hand(&splitHand);
    initialize_deck(deck);

    switch (scenario) {
        case 1: // Test ace_adjuster
            printf("Running ace_adjuster test...\n");

            // Bust scenario with Ace as 11
            playerHand.cardCount = 3;
            playerHand.cards[0].value = 11; // Ace
            playerHand.cards[1].value = 10;
            playerHand.cards[2].value = 1;
            playerHand.value = 22; // Bust if Ace is 11
            ace_adjuster(&playerHand);
            printf("Adjusted hand value: %d\n", playerHand.value);
            break;

        case 2: // Test double_down
            printf("Running double_down test...\n");

            // Valid double down
            playerHand.cardCount = 2;
            playerHand.bet = 50;
            printf("Would you like to double down? (1 for Yes, 0 for No): ");
            int doubled = double_down(&playerHand, &balance);
            printf("Double down result: %d, Remaining balance: %d\n", doubled, balance);

            // Insufficient balance for double down
            balance = 30; // Less than the bet
            doubled = double_down(&playerHand, &balance);
            printf("Double down result with insufficient balance: %d\n", doubled);
            break;

        case 3: // Test double_down when card count is not equals 2
            printf("Running double_down test...\n");

            // Valid double down
            playerHand.cardCount = 3;
            playerHand.bet = 50;
            printf("Would you like to double down? (1 for Yes, 0 for No): ");
            int new_doubled = double_down(&playerHand, &balance);
            printf("Double down result: %d, Remaining balance: %d\n", new_doubled, balance);

            // Insufficient balance for double down
            balance = 30; // Less than the bet
            doubled = double_down(&playerHand, &balance);
            printf("Double down result with insufficient balance: %d\n", doubled);
            break;

        case 4: // Test check_split
            printf("Running check_split test...\n");

            // Scenario 1: Different ranks
            playerHand.cards[0].rankIndex = 2;
            playerHand.cards[1].rankIndex = 3;
            playerHand.cardCount = 2;
            playerHand.bet = 50;
            int split = check_split(deck, &playerHand, &balance);
            printf("Split decision with different ranks: %d\n", split);

            // Scenario 2: Same ranks, insufficient balance
            playerHand.cards[1].rankIndex = 2;
            balance = 40; // Less than the bet
            split = check_split(deck, &playerHand, &balance);
            printf("Split decision with insufficient balance: %d\n", split);

            // Scenario 3: Valid split
            balance = 150; // Sufficient balance
            split = check_split(deck, &playerHand, &balance);
            printf("Split decision with valid conditions: %d\n", split);
            break;

        case 5: // Test handle_split
            printf("Running handle_split test...\n");

            // Valid split setup
            playerHand.cards[0].rankIndex = 2;
            playerHand.cards[1].rankIndex = 2;
            playerHand.cardCount = 2;
            playerHand.value = 20;
            playerHand.bet = 50;
            balance = 150;

            // Execute split
            handle_split(deck, &playerHand, &splitHand, &balance);
            printf("Remaining balance: %d\n", balance);
            printf("Player hand value: %d, Split hand value: %d\n", playerHand.value, splitHand.value);
            break;

        case 6: // Test handle_split when playerHand.value = 1
            printf("Running handle_split test...\n");

            // Valid split setup
            playerHand.cards[0].rankIndex = 2;
            playerHand.cards[1].rankIndex = 2;
            playerHand.cardCount = 2;
            playerHand.value = 1;
            playerHand.bet = 50;
            balance = 150;

            // Execute split
            handle_split(deck, &playerHand, &splitHand, &balance);
            printf("Remaining balance: %d\n", balance);
            printf("Player hand value: %d, Split hand value: %d\n", playerHand.value, splitHand.value);
            break;

        case 7: // Test split_ace_adjuster
            printf("Running split_ace_adjuster test...\n");

            // Single Ace setup
            playerHand.cards[0].value = 1; // Ace
            playerHand.value = 1;
            split_ace_adjuster(&playerHand);
            printf("Adjusted hand value after split_ace_adjuster: %d\n", playerHand.value);
            break;

        case 8: // Comprehensive test for combined functionality
            printf("Running combined functionality test...\n");

            // Split scenario
            playerHand.cards[0].rankIndex = 2;
            playerHand.cards[1].rankIndex = 2;
            playerHand.cardCount = 2;
            playerHand.value = 20;
            playerHand.bet = 50;
            balance = 200;

            if (check_split(deck, &playerHand, &balance)) {
                handle_split(deck, &playerHand, &splitHand, &balance);
                split_ace_adjuster(&splitHand); // Adjust for Ace in split hand
            }

            // Double down scenario
            playerHand.cardCount = 2;
            double_down(&playerHand, &balance);

            // Ace adjustment scenario
            splitHand.cards[0].value = 11; // Ace in split hand
            splitHand.value = 22;         // Bust scenario
            ace_adjuster(&splitHand);
            printf("Final split hand value after ace adjustment: %d\n", splitHand.value);
            break;

        default:
            printf("Invalid scenario number. Please choose between 1-6.\n");
    }
}

int main() {
    int scenario;

    // Ask user to input the test scenario
    printf("Enter the test scenario number (1-8): ");
    if (scanf("%d", &scenario) != 1) {
        fprintf(stderr, "Invalid input. Please enter a valid integer.\n");
        return 1;
    }

    // Run the selected test scenario
    run_scenario(scenario);

    return 0;
}
