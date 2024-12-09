#include "dijkstra.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int x;
    int y;
    int target;
} Coord;

Coord path_coordinates[1000];
int final_count = 0;

void findMandatoryNodes(int l, int w, Node grid[l][w], Node nodes[l * w], Node startNode, int threshold, int* count) {
    nodes[0] = startNode;
    *count = 1;
    //for loop that loops through the whole grid to check for each node that is above the threshold
    for (int i = 0; i < w; i++) { //loop through each row
        for (int j = 0; j < l; j++) { //loop though each column
            if (grid[i][j].risk >= threshold && grid[i][j].risk <= 100 && i != startNode.x && j != startNode.y){
                nodes[*count] = grid[i][j];
                *count += 1;
            }
        }
    }
}

void nearestNeighbor(int count, Node nodes[count])
{
    Node routeCoordinate[count]; // Array for coordinates of final route
    int currentNode = 0;

    // Setting node to visited does not ruin anything since Dijkstra only uses the coordinates of the node
    nodes[currentNode].visited = 1;
    routeCoordinate[0] = nodes[currentNode];

    for (int i = 1; i < count; i++) {
        double tempDist = INF; //Set the initial distance to infinite so the first found distance is always shorter
        int nextNode = -1;

        for (int j = 0; j < count; j++) {
            if (!nodes[j].visited) {
                int minDistance = distance(nodes[currentNode], nodes[j]); //distance between current node and unvisited nodes gets calculated
                if (minDistance < tempDist) {
                    //If the distance is smaller than the current distance it gets saved as the new distance and the next node changes to the closed node
                    tempDist = minDistance;
                    nextNode = j;
                }
            }
        }
        //After the closest unvisited node is found, it gets set to visited and added to the route
        nodes[nextNode].visited = 1;
        routeCoordinate[i] = nodes[nextNode];
        currentNode = nextNode;
    }

    // printf("\nNearest neighbor:\n");
    for (int i = 0; i < count; i++) {
        nodes[i] = routeCoordinate[i];
    }
}

int distance(Node a, Node b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);; //Check distance between two coordinates. Manhattan distance
}

int isValid(int x, int y, int l, int w)
{
    return x >= 0 && x <= w && y >= 0 && y <= l; //Check if x and y are within bounds
}

int minRisk(int l, int w, Node grid[l][w], int *min_x, int *min_y) {
    int min = INF; // Minimum is initially at the max possible value

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
        for (int i = -1; i <= 1; i++) { // Left, Right
            for (int j = -1; j <= 1; j++) { // Up, Down
                // Disregard diagonal. Sum of difference will always be 1 for orthogonal
                if (abs(i) + abs(j) != 1)
                    continue;

                int nX = x + i;
                int nY = y + j;
                // Determine if neighbour coordinates are within the grid
                if (isValid(nX, nY, l, w) && tempGrid[nX][nY].risk <= 100) {
                    int totalRisk = tempGrid[x][y].tempRisk + tempGrid[nX][nY].risk;
                    // Determine if neighbour already has been visited and it is the shortest path compared to known
                    if (!tempGrid[nX][nY].visited && totalRisk < tempGrid[nX][nY].tempRisk) {
                        tempGrid[nX][nY].tempRisk = totalRisk;
                        tempGrid[nX][nY].parentX = x;
                        tempGrid[nX][nY].parentY = y;
                    }
                }
            }
        }
    }

    // Check if a path was found to the target and print
    if (tempGrid[tarX][tarY].parentX != -1 && tempGrid[tarX][tarY].parentY != -1) {
        savePath(l, w, tempGrid, tarX, tarY, 1);
    } else {
        printf("No path found to the target.\n");
    }
}

void savePath(int l, int w, Node grid[l][w], int x, int y, int isTarget) {
    // Base case, stop when no parent
    if (grid[x][y].parentX == -1 && grid[x][y].parentY == -1)
        return;

    savePath(l, w, grid, grid[x][y].parentX, grid[x][y].parentY, 0);
    printf(" -> (%d, %d)", x, y);
    if (!isTarget)
        path_coordinates[final_count++] = (Coord){x, y, 0};
    else
        path_coordinates[final_count++] = (Coord){x, y, 1};
}

void printGrid(int l, int w)
{
    final_count += 1;
    Coord coordinates[final_count];
    coordinates[0] = (Coord){0, 0, 1};
    for (int i = 0; i < final_count; i++)
        coordinates[i + 1] = path_coordinates[i];
    printf("\n");
    for (int i = 0; i < final_count; i++)
        printf("(%d, %d) -> ", coordinates[i].x, coordinates[i].y);
    // IDK how it should be visualised, but coords are saved now
}