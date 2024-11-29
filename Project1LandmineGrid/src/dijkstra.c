#include "functions.h"
#include <math.h>
#include <stdio.h>

void findMandatoryNodes(int l, int w, Node grid[l][w], Node nodes[l * w + 1], int threshold)
{

}

void nearestNeighbor(Node *nodes, int count, int *order)
{

}

int isValid(int x, int y, int l, int w)
{
    return x >= 0 && x <= w && y >= 0 && y <= l;
}

int distance(Node a, Node b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void dijkstra(int l, int w, Node ref, Node tar, Node grid[l][w])
{

}

void printPath(int l, int w, Node grid[l][w], Node current)
{
    if ((grid[current.x][current.y].parent[0] < 0 && grid[current.x][current.y].parent[1] < 0) ||
        (grid[current.x][current.y].parent[0] == current.x && grid[current.x][current.y].parent[1] == current.y)) {
        printf("(%d, %d)", current.x, current.y);
        return;
        }

    printf("(%d, %d) -> ", current.x, current.y);
    printPath(l, w, grid, grid[current.parent[0]][current.parent[1]]);
}