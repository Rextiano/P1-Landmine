#include "functions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    //Print the order
    printf("\nNearest neighbor:\n");
    for (int i = 0; i < count; i++) {
        printf("Node %d, (%d, %d)\n", route[i] + 1, routeCoordinate[i].x, routeCoordinate[i].y);
        nodes[i] = routeCoordinate[i];
    }
}

int distance(Node a, Node b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); //Check distance between two coordinates
}

int isValid(int x, int y, int l, int w)
{
    return x >= 0 && x <= w && y >= 0 && y <= l; //Check if x and y are within bounds
}

int minRisk(int l, int w, Node grid[l][w], int *min_x, int *min_y) {
    int min = INF;

    // Loop through each node in the grid
    for (int x = 0; x < l; x++) {
        for (int y = 0; y < w; y++) {
            // Determine if node has been visited and temp risk is less than minimum risk found
            if (!grid[x][y].visited && grid[x][y].tempRisk <= min) {
                // Update min to the new minimum found and update coordinate pointers to said coordinate
                min = grid[x][y].tempRisk;
                *min_x = x;
                *min_y = y;
            }
        }
    }

    // Returns 1 if it found a new unvisited node
    return min != INF;
}

void dijkstra(int l, int w, Node grid[l][w], int srcX, int srcY, int tarX, int tarY) {
    // Copy originally created grid to a temp grid to change things
    Node tempGrid[l][w];
    memcpy(tempGrid, grid, l * w * sizeof(grid[0][0]));

    // Set temp risk of source node to the actual risk
    tempGrid[srcX][srcY].tempRisk = tempGrid[srcX][srcY].risk;

    // Loop through every node, order determined through minRisk()
    while (1) {
        int x, y;

        // Find the next coordinates based on lowest temporary risk
        if (!minRisk(l, w, tempGrid, &x, &y))
            break; // No unprocessed nodes left, break the loop

        // if (x == tarX && y == tarY) {
        //     break; // Target reached, break the loop. Faster but may be more risky in a big grid
        // }

        // Mark the current node as visited
        tempGrid[x][y].visited = 1;

        // Update the tempRisk of neighbors around chosen coordinate
        for (int i = -1; i <= 1; i++) { // Up, Down
            for (int j = -1; j <= 1; j++) { // Left, Right
                // Disregard diagonal. Sum of difference will always be 1 for orthogonal
                if (abs(i) + abs(j) != 1)
                    continue;

                // Determine if neighbour coordinates are within the grid
                if (isValid(x + i, y + j, l, w)) {
                    int totalRisk = tempGrid[x][y].tempRisk + tempGrid[x + i][y + j].risk;
                    // Determine if neighbour already has been visited and it is the shortest path compared to known
                    if (!tempGrid[x + i][y + j].visited && totalRisk < tempGrid[x + i][y + j].tempRisk) {
                        tempGrid[x + i][y + j].tempRisk = totalRisk;
                        tempGrid[x + i][y + j].parentX = x;
                        tempGrid[x + i][y + j].parentY = y;
                    }
                }
            }
        }
    }

    // Check if a path was found to the target
    if (tempGrid[tarX][tarY].parentX != -1 && tempGrid[tarX][tarY].parentY != -1) {
        printf("|");
        printPath(l, w, tempGrid, tarX, tarY);
    } else {
        printf("No path found to the target.\n");
    }
}

void printPath(int l, int w, Node grid[l][w], int x, int y) {
    // Base case, stop when no parent
    if (grid[x][y].parentX == -1 && grid[x][y].parentY == -1)
        return;

    printPath(l, w, grid, grid[x][y].parentX, grid[x][y].parentY);
    printf(" -> (%d, %d)", x, y);
}