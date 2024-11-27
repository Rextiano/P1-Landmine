#define GRID_SIZE 5   // Grid Size. Only a square for now
#define THRESHOLD 80  // The determined threshold a node should be above or equal to

typedef struct { //Struct to better find positions of nodes
    int x, y;
} Node;

void findMandatoryNodes(int grid[GRID_SIZE][GRID_SIZE], Node nodes[GRID_SIZE * GRID_SIZE + 1]); //Should update a list of mandatory nodes (coordinates with values above threshold)
void nearestNeighbor(Node *nodes, int count, int *order); //Algorithm to order each mandatory node found by closest coordinates
int isValid(int x, int y); //Check if coordinate is within grid
int distance(Node a, Node b); //Find distance between two nodes' coordinates to determine the closest
void dijkstra(Node ref, Node tar, int risk[GRID_SIZE][GRID_SIZE], Node parent[GRID_SIZE][GRID_SIZE], int grid[GRID_SIZE][GRID_SIZE]); //Actual algorithm to determine best route from source to target
void printPath(Node parent[GRID_SIZE][GRID_SIZE], Node target); //Print the result to debug
