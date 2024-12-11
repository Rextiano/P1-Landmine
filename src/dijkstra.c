#include "dijkstra.h"

Coord path_coordinates[2500];
int final_count = 0;

void findMandatoryNodes(Node grid[l][w], Node nodes[l * w], Node startNode, int threshold, int* count) {
    printf("\nFinding mandatory nodes...\n");
    startNode.risk = 0;
    nodes[0] = startNode;
    *count = 1;
    int risk = 0;
    //for loop that loops through the whole grid to check for each node that is above the threshold
    for (int i = 0; i < l; i++) { //loop through each row
        for (int j = 0; j < w; j++) { //loop though each column
            risk = grid[i][j].risk;
            if (risk >= threshold && risk <= 100){
                nodes[*count] = grid[i][j];
                *count += 1;
            }
        }
    }
    printf("Amount of mandatory nodes with a threshold of %d%%: %d\n", threshold, *count);
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

    printf("\nShortest and safest path from source (%d, %d) to destination (%d, %d):\n",
        nodes[0].x, nodes[0].y,
        nodes[count - 1].x, nodes[count - 1].y);
}

int distance(Node a, Node b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);; //Check distance between two coordinates. Manhattan distance
}

int isValid(int x, int y)
{
    return x >= 0 && x <= l && y >= 0 && y <= w; //Check if x and y are within bounds
}

int minRisk(Node tempGrid[l][w], int *min_x, int *min_y) {
    int min = INF; // Minimum is initially at the max possible value

    // Loop through each node in the grid
    for (int x = 0; x < l; x++) {
        for (int y = 0; y < w; y++) {
            // Determine if node has been visited and temp risk is less than minimum risk found
            if (!tempGrid[x][y].visited && tempGrid[x][y].tempRisk <= min) {
                // Update min to the new minimum found and update coordinate pointers to said coordinate
                min = tempGrid[x][y].tempRisk;
                *min_x = x;
                *min_y = y;
            }
        }
    }

    // Returns 1 if it found a new unvisited node
    return min != INF;
}

void dijkstra(Node grid[l][w], int srcX, int srcY, int tarX, int tarY) {
    // Copy originally created grid to a temp grid to change things
    Node tempGrid[l][w];
    memcpy(tempGrid, grid, l * w * sizeof(grid[0][0]));

    // Set temp risk of source node to the actual risk
    tempGrid[srcX][srcY].tempRisk = tempGrid[srcX][srcY].risk;

    // Loop through every node, order determined through minRisk()
    while (1) {
        int x, y;

        // Find the next coordinates based on lowest temporary risk
        if (!minRisk(tempGrid, &x, &y))
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
                if (isValid(nX, nY) && tempGrid[nX][nY].risk <= 100) {
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
        savePath(tempGrid, tarX, tarY, 1);
    } else {
        printf("(%d, %d) -> (%d, %d) No path found to the target.\n", srcX, srcY, tarX, tarY);
    }
}

void savePath(Node grid[l][w], int x, int y, int isTarget) {
    // Base case, stop when no parent
    if (grid[x][y].parentX == -1 && grid[x][y].parentY == -1)
        return;

    savePath(grid, grid[x][y].parentX, grid[x][y].parentY, 0);
    // printf(" -> (%d, %d)", x, y);
    if (!isTarget)
        path_coordinates[final_count++] = (Coord){x, y, 0};
    else
        path_coordinates[final_count++] = (Coord){x, y, 1};
}

#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

char* getGradientColor(int progress) {
    static char colorStr[50];  // Static to preserve the string across function calls

    // Interpolate between light blue (RGB 0, 255, 255) and dark green (RGB 0, 128, 0) based on progress
    int r = progress * 255 / 100;  // Transition from 0 (blue) to 255 (yellow)
    int g = 255;                   // Keep green at full intensity
    int b = 255 - (progress * 255 / 100);  // Transition from 255 (blue) to 0 (yellow)

    // Format the color string in ANSI escape code format
    sprintf(colorStr, "\033[38;2;%d;%d;%dm", r, g, b);

    return colorStr;
}

void printGrid()
{
    final_count += 1;
    Coord coordinates[final_count];
    coordinates[0] = (Coord){0, 0, 1};
    for (int i = 0; i < final_count; i++)
        coordinates[i + 1] = path_coordinates[i];
    printf("Final count %d", final_count);
    for (int i = 0; i < final_count; i++) {
        if (i != final_count - 1)
            printf("(%d, %d) -> ", coordinates[i].x, coordinates[i].y);
        else
            printf("(%d, %d)", coordinates[i].x, coordinates[i].y);
    }

    printf("\n\nFinal route:");

    int target = 0;
    for (int x = 0; x < l; x ++)
    {
        printf("\n");
        for (int y = 0; y < w; y++)
        {
            target = 0;
            for (int i = 0; i < final_count; i++)
            {
                if (coordinates[i].x == x && coordinates[i].y == y)
                {
                    int progress = (i * 100) / (final_count - 1);  // Percentage of the path (0 to 100)
                    char* color = getGradientColor(progress);

                    // Print the X with the appropriate color
                    if (coordinates[i].target)
                        printf("%s# " RESET, color);  // Print "X" with gradient color
                    else
                        printf("%sx " RESET, color);
                    target = 1;
                    break;
                }
            }
            if (!target)
                printf(". ");
        }
    }
    printf("\n");
}