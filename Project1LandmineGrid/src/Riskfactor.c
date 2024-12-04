#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct { //Struct to better find positions of nodes
    int x, y;
    int risk;
    int visited;
    int parent[2];
} Node;

int riskFactor() {
    FILE *fp;
    char grid[100][100];        // To hold symbols from the file
    Node numericGrid[100][100];  // To hold numeric values for processing
    int adjustedGrid[100][100] = {0};  // Tracks whether a cell has been adjusted
    int rows = 25, cols = 25;  // Dimensions based on the uploaded file
    int i, j;

    // Open the grid file
    fp = fopen("landmineGrid.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read the grid data
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fscanf(fp, " %c", &grid[i][j]);
        }
    }

    // Seed the random number generator
    srand(time(NULL));

    // Initialize the numeric grid based on symbols
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            switch (grid[i][j]) {
                case '#':
                    numericGrid[i][j] = (Node){i, j, rand()% 10 + 0, 0, {-1, -1}};  // Random between 0-10
                    break;
                case 'x':
                    numericGrid[i][j] = (Node){i, j, rand()% 20 + 70, 0, {-1, -1}};  // Random between 70-90
                    break;
                case '*':
                    numericGrid[i][j] = (Node){i, j, rand()% 10 + 90, 0, {-1, -1}};  // Random between 90-100
                    break;
                default:
                    numericGrid[i][j] = (Node){i, j, 0, 0, {-1, -1}};  // Default for invalid entries
                    break;
            }
        }
    }

    // First, apply +50 to '#' next to '*'
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (grid[i][j] == '*') {
                // Apply +50 to '#' neighbors of '*'
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int x = i + dx, y = j + dy;
                        if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == '#' && !adjustedGrid[x][y]) {
                            numericGrid[x][y].risk += 50;
                            adjustedGrid[x][y] = 1;  // Mark as adjusted by +50
                        }
                    }
                }
            }
        }
    }

    // Then, apply +30 to '#' next to 'x' if not already adjusted
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (grid[i][j] == '#') {
                // Apply +30 to '#' neighbors of 'x', but only if not adjusted
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int x = i + dx, y = j + dy;
                        if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 'x' && !adjustedGrid[i][j]) {
                            numericGrid[i][j].risk += 30;
                            adjustedGrid[i][j] = 1;  // Mark as adjusted by +30
                            break;
                        }
                    }
                    if (adjustedGrid[i][j]) break;  // Exit early if adjusted
                }
            }
        }
    }

    // Print the modified numeric grid in the desired format
    for (i = 0; i < rows; i++) {
        printf("{");
        for (j = 0; j < cols; j++) {
            printf("%d", numericGrid[i][j].risk);
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

    return 0;
}
