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

int main(void) {
    int minefield[SIZE][SIZE];
    initialise_field(minefield);
    printf("Welcome to minesweeper!\n");

    printf("How many mines? ");
    int mine_count;
    scanf("%d", &mine_count);
    setbuf(stdin, NULL);

    printf("Enter pairs:\n");

    int i = 0;
    for (i; i < mine_count; ++i) {
        char input[50];
        fgets(input, 50, stdin);
        int row = (int)input[0] - '0';
        int col = (int)input[2] - '0';
        minefield[row][col] = HIDDEN_MINE;
    }

    printf("Game Started\n");
    // game loop
    while (1) {
        print_debug_minefield(minefield);
        char input[55];
        fgets(input, 55, stdin);
        int command = (int)input[0] - '0';
        
        if (command == DETECT_ROW) {
            int arg = (int)input[2] - '0';

            int mine_count = 0;
            int i = 0;
            for (i; i < SIZE; ++i) {
                if (minefield[arg-1][i] == 2) {
                    ++mine_count;
                }
            }
            printf("There are %d mines in row %d.\n", mine_count, arg);
        }

        if (command == DETECT_COL) {
            int arg = (int)input[2] - '0';

            int mine_count = 0;
            int i = 0;
            for (i; i < SIZE; ++i) {
                if (minefield[i][arg-1] == 2) {
                    ++mine_count;
                }
            }
            printf("There are %d mines in column %d.\n", mine_count, arg);
        }

    }

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
