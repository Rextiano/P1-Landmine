#include <time.h>
#include "grid.h"

void riskFactor(Node grid[l][w]) {

    FILE *fp;
    char fileGrid[l][w];        // To hold symbols from the file
    int adjustedGrid[l][w];  // Tracks whether a cell has been adjusted

    // Open the grid file
    fp = fopen("landmineGrid.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        // return 1;
    }

    printf("Reading generated grid and choosing probability...\n");

    // Read the grid data
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < w; j++) {
            fscanf(fp, " %c", &fileGrid[i][j]);
        }
    }

    // Seed the random number generator
    srand(time(NULL));

    // Initialize the numeric grid based on symbols
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < w; j++) {
            switch (fileGrid[i][j]) {
                case S:
                    grid[i][j] = (Node){i, j, rand()% 10 + 0, INF, 0, -1, -1};  // Random between 0-10
                    break;
                case B:
                    grid[i][j] = (Node){i, j, rand()% 20 + 70, INF, 0, -1, -1};  // Random between 70-90
                    break;
                case BB:
                    grid[i][j] = (Node){i, j, rand()% 10 + 100, INF, 0, -1, -1};  // Random between 90-100
                    break;
                default:
                    grid[i][j] = (Node){i, j, 0, INF, 0, -1, -1};  // Default for invalid entries
                    break;
            }
        }
    }

    // First, apply +50 to '.' next to '*'
    applyRisk(fileGrid, adjustedGrid, grid, 50, S, BB);
    // Then, apply +30 to '.' next to '#' if not already adjusted
    applyRisk(fileGrid, adjustedGrid, grid, 30, S, B);

    printRiskGrid(grid);

    // Close the file
    fclose(fp);
}

void applyRisk(char fileGrid[l][w], int adjustedGrid[l][w], Node grid[l][w], int risk, char applyTo, char nextTo)
{
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < w; j++) {
            if (fileGrid[i][j] == nextTo) {
                // Apply +50 to '#' neighbors of '*'
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int x = i + dx, y = j + dy;
                        if (x >= 0 && x < l && y >= 0 && y < w && fileGrid[x][y] == applyTo && !adjustedGrid[x][y]) {
                            grid[x][y].risk += risk;
                            adjustedGrid[x][y] = 1;  // Mark as adjusted by +50
                        }
                    }
                }
            }
        }
    }
}

void printRiskGrid(Node grid[l][w])
{
    // Print the modified numeric grid in the desired format
    for (int i = 0; i < l; i++) {
        printf("{");
        for (int j = 0; j < w; j++) {
            printf("%3d", grid[i][j].risk);
            if (j < w - 1) {
                printf(", ");  // Add a comma after each value except the last
            }
        }
        printf("}");
        if (i < l - 1) {
            printf(",\n");  // Add a comma and newline after each row except the last
        }
    }
    printf("\n\n");
}

