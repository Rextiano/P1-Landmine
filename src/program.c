#include <stdio.h>
#include "grid.h"

int main() {
    // Start creating grid
    int l = 0, w = 0;
    userInput(&l, &w);

    // Update grid to risk and probability of bomb
    Node grid[l][w];
    riskFactor(l, w, grid);

    // Find all mandatory nodes in the grid
    Node nodes[l * w];
    int count;
    findMandatoryNodes(l, w, grid, nodes, grid[0][0], 80, &count);
    Node mandatoryNodes[count];

    // For loop that creates a correctly sized array
    for (int i = 0; i < count; i++) {
        mandatoryNodes[i] = nodes[i];
    }

    // Run nearest neighbour to sort list of mandatory nodes
    nearestNeighbor(count, mandatoryNodes);

    printf("Shortest and safest path from source (%d, %d) to destination (%d, %d):\n(%d, %d)",
        mandatoryNodes[0].x, mandatoryNodes[0].y,
        mandatoryNodes[count - 1].x, mandatoryNodes[count - 1].y,
        mandatoryNodes[0].x, mandatoryNodes[0].y);

    for (int i = 0; i < count - 1; i++)
        dijkstra(l, w, grid, mandatoryNodes[i].x, mandatoryNodes[i].y, mandatoryNodes[i + 1].x, mandatoryNodes[i + 1].y);

    return 0;
}