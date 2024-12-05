#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

// The program takes user-input and makes a minefield grid (for further processing) that has double laid bombs equal to 10% of normal bombs
char B = 'x', BB = '*', S = '#'; // ASCII chars for bombs, double bombs, and safe spaces

void userInput(int *length, int *width) {
    int previousBombs = 0; // Variables to store previous settings

    while (1) {
        int reply = 0;
        printf("Enter 1 to generate a new grid with new settings\n");
        printf("Enter 2 to generate a new grid with previous settings\n");
        printf("Enter 3 to exit\n>");
        scanf("%d", &reply);

        if (reply == 1) {
            // Generate a new grid with new settings and store them
            generateGridNewSettings(length, width, &previousBombs);
        } else if (reply == 2) {
            // Generate a grid with the last used settings
            if (*length > 0 && *width > 0 && previousBombs > 0) {
                generateGridSameSettings(*length, *width, previousBombs);
            } else {
                printf("No previous settings found. Please generate a grid with new settings first.\n");
            }
        } else if (reply == 3) {
            printf("Exiting program...\n");
            break;
        } else {
            printf("Invalid input. Please try again.\n");
        }
    }
}

void generateGridNewSettings(int *length, int *width, int *bombs) {
    printf("%c are landmines\n%c are double laid landmines\n%c are safespaces \n", B, BB, S);
    printf("Enter the percentage of bomb coverage (max 80%%, 10%% of bombs will be double laid):\n>");
    scanf("%d", bombs);

    if (*bombs >= 81) {
        printf("Bomb percentage must be max 80.\n");
        return; // Exit function to reattempt
    }

    printf("Enter the length and width of the landmine field (MAX size of 50x50):\n>");
    scanf("%d%d", length, width);

    if (*length >= 50 || *width >= 50) {
        printf("Grid size too large, must be below 50x50.\n");
        return; // Exit function to reattempt
    }

    generateGridSameSettings(*length, *width, *bombs); // Use common function for grid generation
}

void generateGridSameSettings(int length, int width, int bombs) {
    int totalSize = length * width;
    int amountOfBombs = (totalSize * bombs) / 100;
    int amountOfDoubleBombs = (totalSize * bombs * 0.1) / 100;

    char grid[length][width];

    FILE *file = fopen("landmineGrid.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Fill grid with safe spaces initially
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = S;
        }
    }

    // Place bombs in the grid
    placeBomb(0, amountOfBombs, length, width, grid);
    // Place double bombs in the grid
    placeBomb(1, amountOfDoubleBombs, length, width, grid);

    // Print the final grid and save it to a file
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c ", grid[i][j]);
            fprintf(file, "%c ", grid[i][j]);
        }
        printf("\n");
        fprintf(file, "\n");
    }

    fflush(file);
    fclose(file);
}

void placeBomb(int isDoubleBomb, int bombAmount, int l, int w, char grid[l][w])
{
    for (int i = 0; i < bombAmount; i++) {
        int row, col;
        do {
            row = rand() % l;
            col = rand() % w;
        } while (grid[row][col] != S); // Ensure only safe spaces are overwritten
        if (isDoubleBomb)
            grid[row][col] = BB; // Place double bomb
        else
            grid[row][col] = B; // Place normal bomb
    }
}