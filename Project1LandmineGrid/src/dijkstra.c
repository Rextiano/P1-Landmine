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

void nearestNeighbor(int count, Node nodes[count])
{
    int visitedNodes[count];// Array to check if each node has been visited
    int route[count];// Array for the final route
    Node routeCoordinate[count];// Array for coordinates of final route
    for (int i = 0; i < count; i++) { //Set all nodes as unvisited
        visitedNodes[i] = 0;
    }

    int currentNode = 0;
    visitedNodes[currentNode] = 1;
    route[0] = currentNode;
    routeCoordinate[0] = nodes[currentNode];

    for (int i = 1; i < count; i++) {
        double tempDist = INT_MAX; //Set the initial distance to infinite so the first found distance is always shorter
        int nextNode = -1;

        for (int j = 0; j < count; j++) {
            if (!visitedNodes[j]) {
                double minDistance = distance(nodes[currentNode], nodes[j]); //distance between current node and unvisited nodes gets calculated
                if (minDistance < tempDist) {
                    //If the distance is smaller than the current distance it gets saved as the new distance and the next node changes to the closed node
                    tempDist = minDistance;
                    nextNode = j;
                }
            }
        }
        //After the closest unvisited node is found, it gets set to visited and added to the route
        visitedNodes[nextNode] = 1;
        route[i] = nextNode;
        routeCoordinate[i] = nodes[nextNode];
        currentNode = nextNode;
    }
    //Print the route
    // printf("\n");
    printf("\nNearest neighbor:\n");
    for (int i = 0; i < count; i++) {
        printf("Node %d, (%d, %d)\n", route[i] + 1, routeCoordinate[i].x, routeCoordinate[i].y);
    }

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
        printf("(%d, %d)\n", current.x, current.y);
        return;
        }

    //Print current node pos
    printf("(%d, %d) -> ", current.x, current.y);
    //Set current node to parent node and loop
    printPath(l, w, grid, grid[current.parent[0]][current.parent[1]]);
}