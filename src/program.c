#include "grid.h"
#include "dijkstra.h"

int l = 0, w = 0;
int isTest = 0;
int trialMax = 100;

int main()
{
    if (isTest)
    {
        printf("test1");
        monteCarlo(5, 15);
        printf("test2");
        monteCarlo(25, 25);
        return 0;
    }
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
            if (threshold < 0 || threshold > 100) {
                printf("Invalid input. Please enter a value between 0 and 100.\n");
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
        printGrid();

        // See result before program closes
        clearInputBuffer();
        printf("\nProgram finished. Press enter to exit...\n");
        getchar();

    return 0;
}

void clearInputBuffer()
{
    // https://stackoverflow.com/questions/7898215/how-can-i-clear-an-input-buffer-in-c
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Flush the input buffer
}

void monteCarlo(int length, int width)
{
    // Loop 500 trials, 3 times. 10x25 grid, 25x25 grid and 50x50 grid
    // Choose random start position each trial
    // Choose random % of landmines in grid
    // Choose random threshold
    // Output average path length and total risk and grid accuracy (amount of landmines hit / total landmines * 100) of each different grid size
    srand(time(NULL));
    l = length;
    w = width;

    for (int trial = 0; trial < trialMax; trial++)
    {
        Node grid[l][w];
        int bombs = rand() % 79 + 1;
        generateGrid(bombs);
        riskFactor(grid);
        int threshold = rand() % 30 + 50;
        Node nodes[l * w];
        int count = 0;
        findMandatoryNodes(grid, nodes, grid[0][0], threshold, &count);
        Node mandatoryNodes[count];

        // For loop that creates a correctly sized array
        for (int i = 0; i < count; i++) {
            mandatoryNodes[i] = nodes[i];
        }
        nearestNeighbor(count, mandatoryNodes);

        for (int i = 0; i < count - 1; i++)
            dijkstra(grid, mandatoryNodes[i].x, mandatoryNodes[i].y, mandatoryNodes[i + 1].x, mandatoryNodes[i + 1].y);
        printGrid();
    }
}