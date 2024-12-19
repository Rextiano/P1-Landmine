// Header guard. Checks if main has been defined and defines if not https://stackoverflow.com/questions/27810115/what-exactly-do-c-include-guards-do
// Makes it possible to include the header in multiple files, but only process the data once
// Also used in the other headers
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

#define INF 9999
#define RESET "\033[0m" // Used in the end to colour grid

// Node structure representing a grid cell
typedef struct {
    int x, y;
    int risk;
    int tempRisk;  // Tentative risk value
    int visited;   // Flag to indicate if the cell has been visited
    int parentX, parentY;
} Node;

// 'Extern' to be able to use global variables when called multiple times.
// It tells the program that there will only be one instance
extern int l, w;

// Function to clear input buffer because C is just like that
void clearInputBuffer();

#endif // MAIN_H
