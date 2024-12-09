#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

int main() {
    // Start creating grid
    int l = 0, w = 0;
    userInput(&l, &w);

    // Update grid to risk and probability of bomb
    Node grid[l][w];
    riskFactor(l, w, grid);

    // Everything above is simply the hypothetical drone capturing data and outputting a grid
    // Here is where we use the data
    int threshold = 0;
    printf("What should the threshold percentage be?\n");
    scanf("%d", &threshold);

    // Find all mandatory nodes in the grid
    Node nodes[l * w];
    int count;
    findMandatoryNodes(l, w, grid, nodes, grid[0][0], threshold, &count);
    Node mandatoryNodes[count];

    // For loop that creates a correctly sized array
    for (int i = 0; i < count; i++) {
        mandatoryNodes[i] = nodes[i];
    }
    printf("Amount of mandatory nodes: %d\n", count);

    // Run nearest neighbour to sort list of mandatory nodes
    nearestNeighbor(count, mandatoryNodes);

    printf("Shortest and safest path from source (%d, %d) to destination (%d, %d):\n",
        mandatoryNodes[0].x, mandatoryNodes[0].y,
        mandatoryNodes[count - 1].x, mandatoryNodes[count - 1].y);

    // Run dijkstra to find the safest path between each mandatory node
    for (int i = 0; i < count - 1; i++)
        dijkstra(l, w, grid, mandatoryNodes[i].x, mandatoryNodes[i].y, mandatoryNodes[i + 1].x, mandatoryNodes[i + 1].y);
    printGrid(l, w);

    // See result before program closes
    while (getchar() != '\n');

    printf("\nProgram finished. Press enter to exit...\n");
    getchar();
    return 0;
}