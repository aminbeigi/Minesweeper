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
    struct node *next;
} node;

void initialise_field(int minefield[SIZE][SIZE]);
int game_is_won(int(*minefield)[SIZE]);
void print_debug_minefield(int(*minefield)[SIZE]);
void print_gameplay_minefield(int(*minefield)[SIZE]);
int char_to_int(char c);
int in_minefield(int row, int col);
void append(node **head, int row, int col);
int list_size(node *head);
int row_col_in_list(node *head, int row, int col);
node* iterate_sqaure(int(*minefield)[SIZE], int row, int col);
void detect_row(int(*minefield)[SIZE], char* input);
void detect_col(int(*minefield)[SIZE], char* input);
void detect_square(int(*minefield)[SIZE], char* input);
void reveal_square(int(*minefield)[SIZE], char* input);

int main(void) {
    int minefield[SIZE][SIZE];
    int hints_remaining = 3;
    char* out_of_hints_message = "Help already used";

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
    int in_gameplay_mode = 0;
    // game loop
    while (1) {
        if (in_gameplay_mode) {
            print_gameplay_minefield(&minefield);
        } else {
            print_debug_minefield(&minefield);
        }

        if (game_is_won(&minefield)) {
            exit(0);
        }

        // TODO: don't use 55
        char input[55];
        fgets(input, 55, stdin);
        int command = char_to_int(input[0]);
        
        if (hints_remaining == 0 && (command == DETECT_ROW || command == DETECT_COL || command == DETECT_SQUARE)) {
            printf("%s\n", out_of_hints_message);
            continue;
        }

        if (command == DETECT_ROW) {
            detect_row(&minefield, &input);
            --hints_remaining;
        }

        if (command == DETECT_COL) {
            detect_col(&minefield, &input);
            --hints_remaining;
        }

        if (command == DETECT_SQUARE) {
            detect_square(&minefield, &input);
            --hints_remaining;
        }

        if (command == REVEAL_SQUARE) {
            reveal_square(&minefield, &input);
        }

        if (command == GAMEPLAY_MODE) {
            in_gameplay_mode = 1;
        }

        if (command == DEBUG_MODE) {
            in_gameplay_mode = 0;
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

int game_is_won(int (*minefield)[SIZE]) {
    int value;

    int row = 0;
    for (row; row < SIZE; ++row) {
        int col = 0;
        for (col; col < SIZE; ++col) {
            value = (*(*(minefield + row) + col));
            if (value == HIDDEN_SAFE) {
                return 0;
            }
        }
    }
    printf("Game won!\n");
    return 1;
}

// print out the actual values of the minefield.
void print_debug_minefield(int (*minefield)[SIZE]) {
    int row = 0;
    while (row < SIZE) {
        int col = 0;
        while (col < SIZE) {
            printf("%d ", (*(*(minefield + row) + col)));
            col++;
        }
        printf("\n");
        row++;
    }
}

// print hidden values of the minefield.
void print_gameplay_minefield(int (*minefield)[SIZE]) {
    // TODO: add variables (pre-processor directives?) here too cryptic
    char* header_row = "    00 01 02 03 04 05 06 07";
    char* horizontal_border = "   -------------------------";
    int value;
    int mine_count;

    printf("%s\n%s\n", header_row, horizontal_border);
    
    int row = 0;
    for (row; row < SIZE; ++row) {
        int col = 0;
        printf("0%d |", row);
        for (col; col < SIZE; ++col) {
            value = (*(*(minefield + row) + col));
            if (value == VISIBLE_SAFE) {
                node *head = iterate_sqaure(minefield, row, col);
                mine_count = list_size(head);
                if (mine_count == 0) {
                    printf("   ");
                } else {
                    printf("0%d ", mine_count);
                }
            }
            if (value == HIDDEN_SAFE || value == HIDDEN_MINE) {
                printf("## ");
    
            }
        }
        printf("|\n");
    }
    printf("%s\n", horizontal_border);
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

void append(node **head, int row, int col) {
    node *new_node = (node*)malloc(sizeof(node));
    
    if (new_node == NULL) {
        fprintf(stderr, "Unable to allocate memory for new node\n");
        exit(-1);
    }

    new_node->row = row;
    new_node->col = col;
    new_node->next = NULL;

    // check for first iteration
    if (*head == NULL) {
        *head = new_node;
    } else {
        node* current = *head;

        while (current->next != NULL) {
            current = current->next;
        }
        
        current->next = new_node;
        current->next->next = NULL;
    }
}

int list_size(node *head) {
    node *current = head;
    if (current == NULL) {
        return 0;
    }
    
    int count = 1;
    while (current->next != NULL) {
        current = current->next;
        ++count;
    }
    return count;
}

int row_col_in_list(node *head, int row, int col) {
    node *current = head;
    if (current == NULL) {
        return 0;
    }
    
    while (current != NULL) {
        if (current->row == row && current->col == col) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// return row and column of mines in linked list
node* iterate_sqaure(int (*minefield)[SIZE], int row, int col) {
    row -= 1; // start in first coord in top left square
    col -= 1;
    int size = 3;

    // create linked list
    node *head = NULL;

    int i = row;
    for (i; i < row+size; ++i) {
        int j = col;
        for (j; j < col+size; ++j) {
            if (!(in_minefield(row, col))) {
                continue;
            }
            if (*(*(minefield + i) + j) == HIDDEN_MINE) {
                append(&head, i, j);
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

    node *head = iterate_sqaure(minefield, row, col);
    int mine_count = list_size(head);
    
    printf("There are %d mine(s) in the square centered at row %d, column %d, of size 3\n", mine_count, row, col);
    free(head);
}

void reveal_square(int(*minefield)[SIZE], char* input) {
    // TODO: add win condition
    int row = char_to_int(input[2]);
    int col = char_to_int(input[4]);
    int size = 3;

    node *head = iterate_sqaure(minefield, row, col);
    int mine_count = list_size(head);

    // player selects mine
    if (row_col_in_list(head, row, col)) {
        print_debug_minefield(minefield);
        printf("Game over");
        exit(0);
    }

    if (mine_count == 0) {
       row -= 1; // start in first coord in top left square
       col -= 1;

        int i = row;
        for (i; i < row+size; ++i) {
            int j = col;
            for (j; j < col+size; ++j) {
                if (!(in_minefield(i, j))) {
                    continue;
                }
                (*(*(minefield + i) + j)) = VISIBLE_SAFE;
            }
        }
    } else {
        (*(*(minefield + row) + col)) = VISIBLE_SAFE;
    }
    free(head);
} 