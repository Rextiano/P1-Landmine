#include "functions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void findMandatoryNodes(int l, int w, Node grid[l][w], Node nodes[l * w + 1], int threshold, int* count) {

    //for loop that loops through the whole grid to check for each node that is above the threshold
    for (int i = 0; i < w; i++) { //loop through each row
        for (int j = 0; j < l; j++) { //loop though each column
            if (grid[i][j].risk >= threshold){
                nodes[*count].x = i;
                nodes[*count].y = j;
                *count += 1;
            }
        }
    }
}

void nearestNeighbor(Node nodes, int count, int *order)
{

}

int isValid(int x, int y, int l, int w)
{
    return x >= 0 && x <= w && y >= 0 && y <= l; //Check if x and y are within bounds
}

int distance(Node a, Node b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); //Check distance between two coordinates
}

void dijkstra(int l, int w, Node ref, Node tar, Node grid[l][w])
{

}

void printPath(int l, int w, Node grid[l][w], Node current)
{
    //Recursive function
    //Base case, if parent is -1 (no parent)
    if (grid[current.x][current.y].parent[0] == -1 && grid[current.x][current.y].parent[1] == -1) {
        printf("(%d, %d)", current.x, current.y);
        return;
        }

    //Print current node pos
    printf("(%d, %d) -> ", current.x, current.y);
    //Set current node to parent node and loop
    printPath(l, w, grid, grid[current.parent[0]][current.parent[1]]);
}