#include <stdio.h>
#include <stdlib.h>

//programmet kort sagt tager input some størrelsen på et grid og bruger randomtal til koordinater til at placere bomber på et grid
int main(void) {
    restartNewSettings:
    int bombs = 0; //percentage of bombs

    //whatever is left is automatically safe spaces
    int length, width;

    //ascii chars for bombs, double bombs and safe spaces
    char B = 'x', BB = '*', S = '#';

    printf("%c are landmines\n%c are double laid landmines\n%c are safespaces \n", B, BB, S);

    printf("enter the percentage of bomb coverage, less than 100 percent, 10 percent of bombs will be double laid\n");
    scanf("%d", &bombs);

    printf("enter the length and width of the landmine field you want to explore: ");
    scanf("%d%d", &length, &width);

    int totalSize = length * width;

    //percentage of double bombs
    int doubleBombs = bombs * 0.1;

    int amountOfBombs = (totalSize * bombs) / 100;
    int amountOfDoubleBombs = (totalSize * doubleBombs) / 100;

    char grid[length][width];

    restartSameSettings:
    FILE *file = fopen("landmineGrid.txt", "w");

    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return 1; // Return an error code if the file can't be opened
    }



    //fyldet griddet så længe length ikke er overgået, den kører width *length* antal gange
    //så den fylder sidelæns altså et row af gangen, indtil length mængde gange er opnået
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = S; // Fill the grid with safe spaces initially
        }
    }

    //prøver at placere en bombe på et random row, og column index(koordinat) så længe det er et safe space der kan overwrites
    for (int i = 0; i < amountOfBombs; i++) {
        int row, col;
        do {
            row = rand() % length; // Random row index
            col = rand() % width;  // Random column index
        } while (grid[row][col] != S); // Ensure we only place bombs in safe spaces
        grid[row][col] = B; // Place bomb
    }

    //prøver at placere double bombs så længe det er et safespace der bliver ramt med de 2 random tal mod til størrelsen for at holde det indenfor griddet
    //det betyder at alle tal genereret som bliver brugt altid er samme som, eller under griddet
    for (int i = 0; i < amountOfDoubleBombs; i++) {
        int row, col;
        do {
            row = rand() % length;
            col = rand() % width;
        } while (grid[row][col] != S); // Ensure we only place double bombs in safe spaces
        grid[row][col] = BB; // Place double bomb
    }

    // printer det færdige grid, inkluderet bomberne som vi "placerede" i vores grid (array)

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c ", grid[i][j]); // Print each character in the grid
            fprintf(file, "%c ", grid[i][j]);
        }
        printf("\n"); // New line after each row
        fprintf(file, " \n");
    }
    fflush(file);
    fclose(file);

    int reply;
    printf("Enter 1 to exit\nEnter 2 to generate a new field with the same settings \nEnter 3 to generate a new field with new settings");
    scanf("%d", &reply);

    if(reply == 3) {
        //goes to start to ask for settings again
        printf("New field generated with new settings");
        //fclose(file);
        goto restartNewSettings;
    }
    if(reply == 2) {
        //goes back to generating grid with old settings
        printf("New field generated with same settings");
        //fclose(file);
        goto restartSameSettings;
    }
    if(reply == 1) {
        //exits program
        printf("Exiting program...");
        //fclose(file);
        return 0;
    }
    return 0;
}