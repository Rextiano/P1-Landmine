#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "main.h"
#include <string.h>

// Coordinate structure for storing paths
typedef struct {
    int x, y;
    int target;
} Coord;

extern Coord path_coordinates[2500];
extern int final_count;

// Functions related to finding paths and processing nodes
void findMandatoryNodes(Node grid[l][w], Node nodes[l * w], Node startNode, int threshold, int *count);

void nearestNeighbor(int count, Node nodes[count]);
int distance(Node a, Node b);

int isValid(int x, int y);
int minRisk(Node tempGrid[l][w], int *min_x, int *min_y);
void dijkstra(Node grid[l][w], int srcX, int srcY, int tarX, int tarY);

void savePath(Node tempGrid[l][w], int x, int y, int isTarget);
void printGrid();
void algorithmAccuracy(Coord coords[final_count]);

#endif // DIJKSTRA_H
