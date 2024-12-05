#include "dijkstra.h"

void userInput(int *length, int *width);
void generateGridNewSettings(int *length, int *width, int *bombs);
void generateGridSameSettings(int length, int width, int bombs);
void placeBomb(int isDoubleBomb, int bombAmount, int l, int w, char grid[l][w]);
void riskFactor(int rows, int cols, Node grid[rows][cols]);
void applyRisk(int l, int w, char grid[l][w], int adjustedGrid[l][w], Node numericGrid[l][w], int risk, char applyTo, char nextTo);