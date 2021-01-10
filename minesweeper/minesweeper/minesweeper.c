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

typedef struct node {
    int row;
    int col;
    struct node* next;
} node;

void initialise_field(int minefield[SIZE][SIZE]);
void print_debug_minefield(int minefield[SIZE][SIZE]);
int char_to_int(char c);
int in_minefield(int row, int col);
void append(node* head, int row, int col);
void detect_row(int (*minefield)[SIZE], char* input);
void detect_col(int (*minefield)[SIZE], char* input);
void detect_square(int(*minefield)[SIZE], char* input);

int main(void) {
    int minefield[SIZE][SIZE];
    initialise_field(minefield);
    printf("Welcome to mine sweeper!\n");

    printf("How many mines? ");
    int mine_count;
    scanf("%d", &mine_count);
    setbuf(stdin, NULL);

    if (mine_count != 0) {
        printf("Enter pairs:\n");
    }

    int i = 0;
    for (i; i < mine_count; ++i) {
        char input[50];
        fgets(input, 50, stdin);
        int row = char_to_int(input[0]);
        int col = char_to_int(input[2]);
        if (!(in_minefield(row, col))) {
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
        int command = char_to_int(input[0]);
        
        if (command == DETECT_ROW) {
            detect_row(&minefield, &input);
        }

        if (command == DETECT_COL) {
            detect_col(&minefield, &input);
        }

        if (command == DETECT_SQUARE) {
            detect_square(&minefield, &input);
        }

        if (command == REVEAL_SQUARE) {
            int row = (int)input[2] - '0';
            int col = (int)input[4] - '0';

        }
    }

    return 0;
}

// set the entire minefield to HIDDEN_SAFE.
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

// print out the actual values of the minefield.
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

int char_to_int(char c) {
    return c - '0';
}

int in_minefield(int row, int col) {
    if (row >= SIZE || col >= SIZE || row < 0 || col < 0) {
        return 0;
    }
    return 1;
}

void append(node* head, int row, int col) {
    node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (node*) malloc(sizeof(node*));
    current->next->row = row;
    current->next->col = col;
    current->next->next = NULL;
}

// return mines coordinates in linked list
node* iterate_sqaure(int (*minefield)[SIZE], int row, int col, int size) {
    int row = row - 1; // start in first coord in top left square
    int col = col - 1;

    // create linked list
    node* head = NULL;

    int i = row;
    for (i; i < row+size; ++i) {
        int j = col;
        for (j; j < col+size; ++j) {
            if (!(in_minefield(row, col))) {
                continue;
            }
            if (*(*(minefield + i) + j) == HIDDEN_MINE) {
                append(head, i, j);
            }
        }
    }
    return head;
}

void detect_row(int (*minefield)[SIZE], char* input) {
    int row = char_to_int(input[2]); 
    int mine_count = 0;

    int col = 0;
    for (col; col < SIZE; ++col) {
        if (*(*(minefield + row) + col) == HIDDEN_MINE) {
            ++mine_count;
        }
    }
    printf("There are %d mine(s) in row %d.\n", mine_count, row);
}


void detect_col(int (*minefield)[SIZE], char* input) {
    int col = char_to_int(input[2]);
    int mine_count = 0;

    int row = 0;
    for (row; row < SIZE; ++row) {
        if (*(*(minefield + row) + col) == HIDDEN_MINE) {
            ++mine_count;
        }
    }
    printf("There are %d mine(s) in column %d.\n", mine_count, col);
}

void detect_square(int(*minefield)[SIZE], char* input) {
    int row = char_to_int(input[2]);
    int col = char_to_int(input[4]);
    int size = char_to_int(input[6]);
    
    int mine_count = 0;
    int square_row = row-1; // start in first coord in square
    int square_col = col-1;
    
    int i = square_row;
    for (i; i < square_row+size; ++i) {
        int j = square_col;
        for (j; j < square_col+size; ++j) {
            if (!(in_minefield(square_row, square_col))) {
                continue;
            }
            if (*(*(minefield + i) + j) == HIDDEN_MINE) {
                ++mine_count;
            }
        }
    }
    printf("There are %d mine(s) in the square centered at row %d, column %d, of size %d\n", mine_count, row, col, size);
}

void reveal_square(int(*minefield)[SIZE], char* input) {

}
