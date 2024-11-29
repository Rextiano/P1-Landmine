#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

int main() {
    int l = 5, w = 5;
    Node grid[5][5] = {
        {{0, 0, 10, {0, 1}}, {0, 1, 20, {1, 1}}, {0, 2, 30, {-1, -1}}, {0, 3, 40, {-1, -1}}, {0, 4, 50, {-1, -1}}},
        {{1, 0, 60, {-1, -1}}, {1, 1, 70, {1, 2}}, {1, 2, 80, {2, 2}}, {1, 3, 90, {-1, -1}}, {1, 4, 60, {-1, -1}}},
        {{2, 0, 50, {-1, -1}}, {2, 1, 60, {-1, -1}}, {2, 2, 90, {-1, -1}}, {2, 3, 10, {-1, -1}}, {2, 4, 20, {-1, -1}}},
        {{3, 0, 20, {-1, -1}}, {3, 1, 30, {-1, -1}}, {3, 2, 40, {-1, -1}}, {3, 3, 50, {-1, -1}}, {3, 4, 60, {-1, -1}}},
        {{4, 0, 70, {-1, -1}}, {4, 1, 80, {-1, -1}}, {4, 2, 90, {-1, -1}}, {4, 3, 60, {-1, -1}}, {4, 4, 70, {-1, -1}}}
    };
    Node current = grid[0][0];
    printPath(l, w, grid, current);

    Node nodes[l * w + 1];
    int count = 0;
    findMandatoryNodes(l, w, grid, nodes, 80, &count);

    //for loop that runs through the found mandatory nodes that exceed the threshold and prints them
    for (int i = 0; i < count; i++) {
        printf("Node %d: (%d, %d)\n", i+1, nodes[i].x, nodes[i].y);
    }
    return 0;
}
