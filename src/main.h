#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

#define INF 9999

// Node structure representing a grid cell
typedef struct {
    int x, y;
    int risk;
    int tempRisk;  // Tentative risk value
    int visited;   // Flag to indicate if the cell has been visited
    int parentX, parentY;
} Node;

extern int l, w;

// Utility function to clear input buffer
void clearInputBuffer();
void updateVariables(int length, int width);

#endif // MAIN_H
