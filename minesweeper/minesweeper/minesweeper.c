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

void initialise_field(int minefield[SIZE][SIZE]);
void print_debug_minefield(int minefield[SIZE][SIZE]);

int main(void) {
    int minefield[SIZE][SIZE];
    initialise_field(minefield);
    printf("Welcome to mine sweeper!\n");

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
        if (row >= SIZE || col >= SIZE || row < 0 || col < 0) {
            continue;
        }
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
            int row = (int)input[2] - '0';

            int mine_count = 0;
            int col = 0;
            for (col; col < SIZE; ++col) {
                if (minefield[row][col] == 2) {
                    ++mine_count;
                }
            }
            printf("There are %d mine(s) in row %d.\n", mine_count, row);
        }

        if (command == DETECT_COL) {
            int col = (int)input[2] - '0';

            int mine_count = 0;
            int row = 0;
            for (row; row < SIZE; ++row) {
                if (minefield[row][col] == HIDDEN_MINE) {
                    ++mine_count;
                }
            }
            printf("There are %d mine(s) in column %d.\n", mine_count, col);
        }

        if (command == DETECT_SQUARE) {
            int row = (int)input[2] - '0';
            int col = (int)input[4] - '0';
            int size = (int)input[6] - '0';
            
            int mine_count = 0;
            int square_row = row-1; // start in first coord in square
            int square_col = col-1;
            
            int i = square_row;
            for (i; i < square_row+size; ++i) {
                int j = square_col;
                for (j; j < square_col+size; ++j) {
                    if (minefield[i][j] == HIDDEN_MINE) {
                        ++mine_count;
                    }
                }
            }
            printf("There are %d mine(s) in the square centered at row %d, column %d, of size %d\n", mine_count, row, col, size);
        }
    }

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
