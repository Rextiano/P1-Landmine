#include <stdio.h>
#include <stdlib.h>

// The program takes user-input and makes a minefield grid (for further processing) that has double laid bombs equal to 10% of normal bombs

// Function prototypes
void generateGridNewSettings(int *length, int *width, int *bombs);
void generateGridSameSettings(int length, int width, int bombs);

int main(void) {
    int previousLength = 0, previousWidth = 0, previousBombs = 0; // Variables to store previous settings

    while (1) {
        int reply = 0;
        printf("Enter 1 to generate a new grid with new settings\n");
        printf("Enter 2 to generate a new grid with previous settings\n");
        printf("Enter 3 to exit\n>");
        scanf("%d", &reply);

        if (reply == 1) {
            // Generate a new grid with new settings and store them
            generateGridNewSettings(&previousLength, &previousWidth, &previousBombs);
        } else if (reply == 2) {
            // Generate a grid with the last used settings
            if (previousLength > 0 && previousWidth > 0 && previousBombs > 0) {
                generateGridSameSettings(previousLength, previousWidth, previousBombs);
            } else {
                printf("No previous settings found. Please generate a grid with new settings first.\n");
            }
        } else if (reply == 3) {
            printf("Exiting program...\n");
            return 0;
        } else {
            printf("Invalid input. Please try again.\n");
        }
    }
}

void generateGridNewSettings(int *length, int *width, int *bombs) {
    char B = 'x', BB = '*', S = '#'; // ASCII chars for bombs, double bombs, and safe spaces

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
    char B = 'x', BB = '*', S = '#'; // ASCII chars for bombs, double bombs, and safe spaces
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
    for (int i = 0; i < amountOfBombs; i++) {
        int row, col;
        do {
            row = rand() % length;
            col = rand() % width;
        } while (grid[row][col] != S); // Ensure only safe spaces are overwritten
        grid[row][col] = B; // Place bomb
    }

    // Place double bombs in the grid
    for (int i = 0; i < amountOfDoubleBombs; i++) {
        int row, col;
        do {
            row = rand() % length;
            col = rand() % width;
        } while (grid[row][col] != S); // Ensure only safe spaces are overwritten
        grid[row][col] = BB; // Place double bomb
    }

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
