#include "functions.h"
#include <math.h>

void findMandatoryNodes(int grid[GRID_SIZE][GRID_SIZE], Node nodes[GRID_SIZE * GRID_SIZE + 1])
{

}

void nearestNeighbor(Node *nodes, int count, int *order)
{

}

int isValid(int x, int y)
{
    return x >= 0 && x <= GRID_SIZE && y >= 0 && y <= GRID_SIZE;
}

int distance(Node a, Node b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void dijkstra(Node ref, Node tar, int risk[GRID_SIZE][GRID_SIZE], Node parent[GRID_SIZE][GRID_SIZE], int grid[GRID_SIZE][GRID_SIZE])
{

}

void printPath(Node prev[GRID_SIZE][GRID_SIZE], Node target)
{

}