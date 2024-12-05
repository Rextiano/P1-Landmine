#define INF 9999

typedef struct{
    int x, y;
    int risk;
    int tempRisk; // Temporary risk value
    int visited; // Flag to indicate if the cell has been visited
    int parentX, parentY;
}Node;

void findMandatoryNodes(int l, int w, Node grid[l][w], Node nodes[l * w + 1], int threshold, int* count); //Should update a list of mandatory nodes (coordinates with values above threshold)
void nearestNeighbor(int count, Node nodes[count]); //Algorithm to order each mandatory node found by closest coordinates
int distance(Node a, Node b); //Distance between coordinates
int isValid(int x, int y, int l, int w); //Check if coordinate is within grid
int minRisk(int l, int w, Node grid[l][w], int *min_x, int *min_y);
void dijkstra(int l, int w, Node grid[l][w], int srcX, int srcY, int tarX, int tarY); //Actual algorithm to determine best route from source to target
void printPath(int l, int w, Node grid[l][w], int x, int y); //Print the result to work with