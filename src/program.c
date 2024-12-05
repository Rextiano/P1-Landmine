#include <stdio.h>
#include "functions.h"

int main() {
    int l = 5, w = 5;
    Node grid[5][5] = {
        {{0, 0, 10, INF, 0, -1, -1}, {0, 1, 20, INF, 0, -1, -1}, {0, 2, 30, INF, 0, -1, -1}, {0, 3, 40, INF, 0, -1, -1}, {0, 4, 90, INF, 0, -1, -1}},
        {{1, 0, 60, INF, 0, -1, -1}, {1, 1, 70, INF, 0, -1, -1}, {1, 2, 80, INF, 0, -1, -1}, {1, 3, 90, INF, 0, -1, -1}, {1, 4, 60, INF, 0, -1, -1}},
        {{2, 0, 50, INF, 0, -1, -1}, {2, 1, 60, INF, 0, -1, -1}, {2, 2, 90, INF, 0, -1, -1}, {2, 3, 10, INF, 0, -1, -1}, {2, 4, 20, INF, 0, -1, -1}},
        {{3, 0, 20, INF, 0, -1, -1}, {3, 1, 30, INF, 0, -1, -1}, {3, 2, 40, INF, 0, -1, -1}, {3, 3, 50, INF, 0, -1, -1}, {3, 4, 60, INF, 0, -1, -1}},
        {{4, 0, 70, INF, 0, -1, -1}, {4, 1, 80, INF, 0, -1, -1}, {4, 2, 90, INF, 0, -1, -1}, {4, 3, 60, INF, 0, -1, -1}, {4, 4, 70, INF, 0, -1, -1}}
    };

    Node* startNode = &grid[0][0];

    Node nodes[l * w + 1];
    nodes[0] = *startNode;
    int count = 1;
    findMandatoryNodes(l, w, grid, nodes, 80, &count);
    Node mandatoryNodes[count];

    //for loop that runs through the found mandatory nodes that exceed the threshold and prints them
    for (int i = 0; i < count; i++) {
        mandatoryNodes[i] = nodes[i];
        // printf("Node %d: (%d, %d)\n", i+1, nodes[i].x, nodes[i].y);
    }

    nearestNeighbor(count, mandatoryNodes);

    printf("Shortest and safest path from source (%d, %d) to destination (%d, %d):\n(%d, %d)",
        mandatoryNodes[0].x, mandatoryNodes[0].y,
        mandatoryNodes[count - 1].x, mandatoryNodes[count - 1].y,
        mandatoryNodes[0].x, mandatoryNodes[0].y);

    for (int i = 0; i < count - 1; i++)
    {
        dijkstra(l, w, grid, mandatoryNodes[i].x, mandatoryNodes[i].y, mandatoryNodes[i + 1].x, mandatoryNodes[i + 1].y);
    }

    return 0;
}