#include "grid.h"
#include "dijkstra.h"

void clearInputBuffer() {
    // https://stackoverflow.com/questions/7898215/how-can-i-clear-an-input-buffer-in-c
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Flush the input buffer
}

void updateVariables(int length, int width)
{
    l = length;
    w = width;
}


int l = 0, w = 0;

int main() {
    // Start creating grid
    userInput();

    // Update grid to risk and probability of bomb
    Node grid[l][w];
    riskFactor(grid);

    // Everything above is simply the hypothetical drone capturing data and outputting a grid
    // Here is where we use the data
    int threshold = 0;
    while (1)
    {
        printf("What should the threshold percentage be?\n>");
        if (scanf("%d", &threshold) != 1) {
            printf("Invalid input. Please enter a value between 0 and 100.\n");
            clearInputBuffer(); // Clear the buffer to avoid infinite loops
            continue;
        }
        break;
    }

    // Find all mandatory nodes in the grid
    Node nodes[l * w];
    int count;
    findMandatoryNodes(grid, nodes, grid[0][0], threshold, &count);
    Node mandatoryNodes[count];

    // For loop that creates a correctly sized array
    for (int i = 0; i < count; i++) {
        mandatoryNodes[i] = nodes[i];
    }

    // Run nearest neighbour to sort list of mandatory nodes
    nearestNeighbor(count, mandatoryNodes);

    // Run dijkstra to find the safest path between each mandatory node
    for (int i = 0; i < count - 1; i++)
        dijkstra(grid, mandatoryNodes[i].x, mandatoryNodes[i].y, mandatoryNodes[i + 1].x, mandatoryNodes[i + 1].y);
    printGrid(l, w);

    // See result before program closes
    clearInputBuffer();
    printf("\nProgram finished. Press enter to exit...\n");
    getchar();
    return 0;
}