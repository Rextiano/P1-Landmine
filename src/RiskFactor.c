#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"

void riskFactor(int rows, int cols, Node grid[rows][cols]) {
    FILE *fp;
    char fileGrid[rows][cols];        // To hold symbols from the file
    int adjustedGrid[rows][cols];  // Tracks whether a cell has been adjusted

    // Open the grid file
    fp = fopen("landmineGrid.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        // return 1;
    }

    // Read the grid data
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(fp, " %c", &fileGrid[i][j]);
        }
    }

    // Seed the random number generator
    srand(time(NULL));

    // Initialize the numeric grid based on symbols
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            switch (fileGrid[i][j]) {
                case '#':
                    grid[i][j] = (Node){i, j, rand()% 10 + 0, INF, 0, -1, -1};  // Random between 0-10
                    break;
                case 'x':
                    grid[i][j] = (Node){i, j, rand()% 20 + 70, INF, 0, -1, -1};  // Random between 70-90
                    break;
                case '*':
                    grid[i][j] = (Node){i, j, rand()% 10 + 90, INF, 0, -1, -1};  // Random between 90-100
                    break;
                default:
                    grid[i][j] = (Node){i, j, 0, INF, 0, -1, -1};  // Default for invalid entries
                    break;
            }
        }
    }

    // First, apply +50 to '#' next to '*'
    applyRisk(rows, cols, fileGrid, adjustedGrid, grid, 50, '#', '*');
    // Then, apply +30 to '#' next to 'x' if not already adjusted
    applyRisk(rows, cols, fileGrid, adjustedGrid, grid, 30, '#', 'x');

    // Print the modified numeric grid in the desired format
    for (int i = 0; i < rows; i++) {
        printf("{");
        for (int j = 0; j < cols; j++) {
            printf("%d", grid[i][j].risk);
            if (j < cols - 1) {
                printf(", ");  // Add a comma after each value except the last
            }
        }
        printf("}");
        if (i < rows - 1) {
            printf(",\n");  // Add a comma and newline after each row except the last
        }
    }
    printf("\n");

    // Close the file
    fclose(fp);
}

void applyRisk(int l, int w, char fileGrid[l][w], int adjustedGrid[l][w], Node grid[l][w], int risk, char applyTo, char nextTo)
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