#include "grid.h"

int gridExists = 0;

// The program takes user-input and makes a minefield grid (for further processing) that has double laid bombs equal to 10% of normal bombs
void userInput() {
    int previousBombs = 0; // Variables to store previous settings

    gridSettings(&previousBombs);

    while (1) {
        int reply = 0;
        printf("\n----- Drone Data Menu -----\n");
        printf("Enter 1 to generate a new grid with new settings\n");
        printf("Enter 2 to generate a new grid with previous settings\n");
        printf("Enter 3 to proceed with running the algorithm\n>");

        if (scanf("%d", &reply) != 1) {
            printf("Invalid input. Please enter a number between 1 and 3.\n");
            clearInputBuffer(); // Clear the buffer to avoid infinite loops
            continue;
        }

        switch (reply) {
        case 1:
            gridSettings(&previousBombs);
            break;
        case 2:
            if (l > 0 && w > 0 && previousBombs > 0) {
                generateGrid(previousBombs);
            } else {
                printf("No previous settings found. Please generate a grid with new settings first...\n");
            }
            break;
        case 3:
            if (!gridExists)
            {
                printf("No grid or data. Try generating a grid...\n");
                break;
            }
            printf("Proceeding...\n\n");
            return;
        default:
            printf("Invalid input. Please try again.\n");
        }
    }
}

void gridSettings(int *bombs) {
    printf("\n----- Generate a grid of landmines -----\n");
    printf("%c are landmines\n%c are double laid landmines (to be avoided)\n%c are safespaces\n", B, BB, S);
    printf("Enter the percentage of landmine coverage (Max 80%%. 10%% of landmines will be double laid):\n>");

    if (scanf("%d", bombs) != 1) {
        printf("Invalid input. Please enter a number between 0 and 80.\n");
        clearInputBuffer(); // Clear the buffer to avoid infinite loops
        return;
    }

    if (*bombs > 80 || *bombs < 0) {
        printf("Landmine percentage must be between 0 and 80.\n");
        return; // Exit function to reattempt
    }

    printf("Enter the length and width of the landmine field (MAX size of 50x50):\n>");

    if (scanf("%d%d", &l, &w) != 2) {
        printf("Invalid input. Please enter a viable length and width.\n");
        clearInputBuffer(); // Clear the buffer to avoid infinite loops
        return;
    }

    if (l > 50 || w > 50 || l < 0 || w < 0) {
        printf("Grid size too large, must be below 51x51.\n");
        return;
    }

    generateGrid(*bombs); // Use common function for grid generation
}

void generateGrid(int bombs) {
    int totalSize = l * w;
    int amountOfBombs = (totalSize * bombs) / 100;
    int amountOfDoubleBombs = (totalSize * bombs * 0.1) / 100;

    char grid[l][w];

    FILE *file = fopen("landmineGrid.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Fill grid with safe spaces initially
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < w; j++) {
            grid[i][j] = S;
        }
    }

    // Place bombs in the grid
    placeBomb(0, amountOfBombs, grid);
    // Place double bombs in the grid
    placeBomb(1, amountOfDoubleBombs, grid);

    printCharGrid(grid, file);
    gridExists = 1;

    fflush(file);
    fclose(file);
}

void placeBomb(int isDoubleBomb, int bombAmount, char grid[l][w])
{
    srand(time(NULL));
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

void printCharGrid(char grid[l][w], FILE *file)
{
    printf("\nGrid generated:\n");
    // Print the final grid and save it to a file
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < w; j++) {
            printf("%c ", grid[i][j]);
            fprintf(file, "%c ", grid[i][j]);
        }
        printf("\n");
        fprintf(file, "\n");
    }
}