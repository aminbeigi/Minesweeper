#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// Possible square states.
#define VISIBLE_SAFE    0
#define HIDDEN_SAFE     1
#define HIDDEN_MINE     2

// The size of the starting grid.
#define SIZE 8

// The possible command codes.
#define DETECT_ROW              1
#define DETECT_COL              2
#define DETECT_SQUARE           3
#define REVEAL_SQUARE           4
#define GAMEPLAY_MODE           5
#define DEBUG_MODE              6
#define REVEAL_RADIAL           7

#define _CRT_SECURE_NO_WARNINGS

void initialise_field(int minefield[SIZE][SIZE]);
void print_debug_minefield(int minefield[SIZE][SIZE]);

// Place your function prototyes here.

int main(void) {
    int minefield[SIZE][SIZE];
    initialise_field(minefield);
    printf("Welcome to minesweeper!\n");

    printf("How many mines? ");
    int mine_count;
    scanf("%d", &mine_count);
    setbuf(stdin, NULL);

    // TODO: Scan in the number of pairs of mines.

    printf("Enter pairs:\n");

    int i = 0;
    for (i; i < mine_count; ++i) {
        char input[50];
        fgets(input, 50, stdin);
        int row = (int)input[0] - 48;
        int col = (int)input[2] - 48;
        minefield[row][col] = HIDDEN_MINE;
    }

    // TODO: Scan in the pairs of mines and place them on the grid.

    printf("Game Started\n");
    print_debug_minefield(minefield);

    // TODO: Scan in commands to play the game until the game ends.
    // A game ends when the player wins, loses, or enters EOF (Ctrl+D).
    // You should display the minefield after each command has been processed.

    return 0;
}

// Set the entire minefield to HIDDEN_SAFE.
void initialise_field(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            minefield[i][j] = HIDDEN_SAFE;
            j++;
        }
        i++;
    }
}

// Print out the actual values of the minefield.
void print_debug_minefield(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            printf("%d ", minefield[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

void parse_input(char* input) {
    int row = input[0];
    int col = input[2];
    return row, col;
}