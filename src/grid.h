#ifndef GRID_H
#define GRID_H

#include "main.h"
#include <time.h>

// Symbols for the grid
#define B '#'  // Bomb
#define BB '*' // Double bomb
#define S '.'  // Safe space

// Declare global variable (defined in a .c file)
extern int gridExists;

// Functions related to grid creation and manipulation
void userInput();
void gridSettings(int *bombs);
void generateGrid(int bombs);
void placeBomb(int isDoubleBomb, int bombAmount, char grid[l][w]);
void printCharGrid(char grid[l][w], FILE *file);

void riskFactor(Node grid[l][w]);
void applyRisk(char grid[l][w], int adjustedGrid[l][w], Node numericGrid[l][w], int risk, char applyTo, char nextTo);
void printRiskGrid(Node grid[l][w]);

#endif // GRID_H
