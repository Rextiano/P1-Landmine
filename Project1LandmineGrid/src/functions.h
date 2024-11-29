typedef struct { //Struct to better find positions of nodes
    int x, y;
    int risk;
    int parent[2];
} Node;

void findMandatoryNodes(int l, int w, Node grid[l][w], Node nodes[l * w + 1], int threshold); //Should update a list of mandatory nodes (coordinates with values above threshold)
void nearestNeighbor(Node *nodes, int count, int *order); //Algorithm to order each mandatory node found by closest coordinates
int isValid(int x, int y, int l, int w); //Check if coordinate is within grid
int distance(Node a, Node b); //Find distance between two nodes' coordinates to determine the closest
void dijkstra(int l, int w, Node ref, Node tar, Node grid[l][w]); //Actual algorithm to determine best route from source to target
void printPath(int l, int w, Node grid[l][w], Node current); //Print the result to debug
