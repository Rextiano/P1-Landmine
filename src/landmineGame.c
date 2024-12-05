#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // For _getch()

#define MAX_SIZE 50 // Set a maximum grid size for safety

// Global variables for the grid and player position
char grid[MAX_SIZE][MAX_SIZE];          // Grid to display to the player
char originalGrid[MAX_SIZE][MAX_SIZE];  // To track bomb positions
int playerRow, playerCol;
time_t startTime; // To track game start time

// Function declarations
void initializeGrid(int length, int width, int bombs, int doubleBombs);
void printGrid(int length, int width);
void movePlayer(int length, int width);
void displayWinScreen();
void displayLossScreen();
void updateTimer();

int main(void) {
    int bombs = 25;       // Percentage of bombs
    int doubleBombs = 15; // Percentage of double bombs
    int length, width;

    // ASCII chars for bombs, double bombs, and safe spaces
    char B = 0x9E, BB = 0xFE, S = 0xB0;

    printf("%c are landmines\n%c are double laid landmines\n%c are safe spaces\n", B, BB, S);
    printf("Enter the length and width of the landmine field you want to explore: ");
    scanf("%d%d", &length, &width);

    // Ensure the dimensions don't exceed MAX_SIZE
    if (length > MAX_SIZE || width > MAX_SIZE) {
        printf("Grid dimensions exceed maximum allowed size (%d x %d).\n", MAX_SIZE, MAX_SIZE);
        return 1;
    }

    // Initialize the grid with bombs and safe spaces
    initializeGrid(length, width, bombs, doubleBombs);

    // Set player starting position
    playerRow = length - 1; // Start at the bottom row
    playerCol = width / 2;   // Start in the middle column

    // Start the game timer
    startTime = time(NULL);

    printf("Game Started! Use WASD to move.\n");

    // Game loop
    while (1) {
        updateTimer();
        printGrid(length, width);
        movePlayer(length, width);

        // Check win condition
        if (playerRow == 0) {
            displayWinScreen();
            break;
        }

        // Check loss condition against the original grid
        if (originalGrid[playerRow][playerCol] == 0x9E || originalGrid[playerRow][playerCol] == 0xFE) {
            displayLossScreen();
            break;
        }
    }
    return 0;
}

// Function to initialize the grid with random bombs and safe spaces
void initializeGrid(int length, int width, int bombs, int doubleBombs) {
    char S = 0xB0;  // Safe space character
    char B = 0x9E;  // Bomb character
    char BB = 0xFE; // Double bomb character

    // Fill the grid with safe spaces initially
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = S;           // Fill the grid with safe spaces
            originalGrid[i][j] = S;   // Initialize original grid as well
        }
    }

    int totalSize = length * width;
    int amountOfBombs = (totalSize * bombs) / 100;
    int amountOfDoubleBombs = (totalSize * doubleBombs) / 100;

    // Place bombs randomly
    for (int i = 0; i < amountOfBombs; i++) {
        int row, col;
        do {
            row = rand() % length; // Random row index
            col = rand() % width;  // Random column index
        } while (originalGrid[row][col] != S); // Ensure we only place bombs in safe spaces
        grid[row][col] = B;           // Place bomb in the grid
        originalGrid[row][col] = B;   // Mark in original grid as bomb
    }

    // Place double bombs randomly
    for (int i = 0; i < amountOfDoubleBombs; i++) {
        int row, col;
        do {
            row = rand() % length; // Random row index
            col = rand() % width;  // Random column index
        } while (originalGrid[row][col] != S); // Ensure we only place bombs in safe spaces
        grid[row][col] = BB;           // Place double bomb in the grid
        originalGrid[row][col] = BB;   // Mark in original grid as double bomb
    }
}

// Function to print the grid with the player's position and game timer
void printGrid(int length, int width) {
    system("cls"); // Clear the console (use "clear" for Unix/Linux)

    updateTimer(); // Update and show the timer

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (i == playerRow && j == playerCol) {
                printf("P "); // Print player position
            } else {
                printf("%c ", grid[i][j]); // Print other grid contents
            }
        }
        printf("\n"); // New line after each row
    }
}

// Function to handle player movement
void movePlayer(int length, int width) {
    printf("Move (WASD): ");
    fflush(stdout); // Ensure output is shown

    char move = _getch(); // Get input without Enter
    switch (move) {
        case 'W': case 'w':
            if (playerRow > 0) playerRow--; // Move up
            break;
        case 'S': case 's':
            if (playerRow < length - 1) playerRow++; // Move down
            break;
        case 'A': case 'a':
            if (playerCol > 0) playerCol--; // Move left
            break;
        case 'D': case 'd':
            if (playerCol < width - 1) playerCol++; // Move right
            break;
        default:
            printf("Invalid move. Use W, A, S, or D.\n");
            break;
    }
}

// Function to display the win screen
void displayWinScreen() {
    system("cls"); // Clear the console
    printf("Congratulations! You've reached the top of the field safely!\n");
    printf("You win!\n");
    getchar(); // Wait for enter key
}

// Function to display the loss screen
void displayLossScreen() {
    system("cls"); // Clear the console
    printf("Boom! You stepped on a landmine!\n");
    printf("Game Over.\n");
    getchar(); // Wait for enter key
}

// Function to update and display the timer
void updateTimer() {
    time_t currentTime = time(NULL);
    int elapsedTime = (int)difftime(currentTime, startTime);

    // Display the elapsed time at the top of the screen
    printf("Time Elapsed: %d seconds\n", elapsedTime);
}