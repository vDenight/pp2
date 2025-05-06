//
// Created by mrybczynski on 5/6/2025.
//

#include "maze.h"

#include <stdio.h>
#include <stdlib.h>

int calculate_row_length_file(FILE* file) {
    int row_length = 0;
    int c;
    while ((c = fgetc(file)) != EOF && c != '\n') {
        row_length++;
    }
    fseek(file, 0, SEEK_SET);
    return row_length;
}

int calculate_row_amount_file(FILE* file) {
    int row_amount = 0;
    int c = {0};
    char prev_char = {0};
    while (1) {
        prev_char = c;
        c = fgetc(file);
        if (c == '\n') {
            row_amount++;
        }
        if (c == EOF) {
            if (prev_char != '\n') {
                row_amount++;
            }
            break;
        }
    }
    fseek(file, 0, SEEK_SET);
    return row_amount;
}

int validate_maze_file(FILE* file, int row_length, int row_amount) {
    if (row_length <= 0 || row_amount <= 0) {
        return -5;
    }

    int c;
    _Bool b_present = 0;
    for (int i = 0; i < row_amount; i++) {
        for (int j = 0; j < row_length; j++) {
            c = fgetc(file);
            if (!(c == 'a' || c == '#' || c == ' ' || c == 'b')) {
                return -1;
            }
            if (c == 'b') { // dont want to get double b
                if (b_present)
                    return -3;
                b_present = 1;
            }
        }
        c = fgetc(file);
        if (c != '\n') {
            if ((c == EOF) && (i == row_amount - 1)) {
                break;
            }
            return -2;
        }
    }

    fseek(file, 0, SEEK_SET);
    return 0;
}

int load_maze(const char *filename, char ***labirynth) {

    if (filename == NULL || labirynth == NULL) {
        return LOAD_INPUT_ERROR;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return LOAD_FILE_OPEN_ERROR;
    }

    int row_length = calculate_row_length_file(file);
    int row_amount = calculate_row_amount_file(file);
    if (validate_maze_file(file, row_length, row_amount)) {
        fclose(file);
        return LOAD_FILE_CORRUPTED_ERROR;
    }

    *labirynth = malloc(sizeof(char *) * (row_amount + 1));
    if (*labirynth == NULL) {
        fclose(file);
        return LOAD_ALLOC_ERROR;
    }
    *(*labirynth + row_amount) = NULL;

    for (int i = 0; i < row_amount; i++) {
        *((*labirynth) + i) = malloc(sizeof(char) * (row_length + 1));
        if (*((*labirynth) + i) == NULL) {
            for (int j = 0; j < i; j++) {
                free(*((*labirynth) + j));
            }
            free(*labirynth);
            fclose(file);
            return LOAD_ALLOC_ERROR;
        }
        *(*((*labirynth) + i) + row_length) = '\0';
    }

    // all memory alloced now we fill
    char c;
    for (int i = 0; i < row_amount; i++) {
        for (int j = 0; j < row_length; j++) {
            c = fgetc(file);
            *(*((*labirynth) + i) + j) = c;
        }
        fgetc(file); // get the newline :))
    }

    fclose(file);
    return LOAD_OK;
}

int solve_maze_req(char **maze, int x, int y, int row_amount, int row_length) {

    if (x < 0 || x >= row_length || y < 0 || y >= row_amount) {
        return SOLVE_FAILED;
    }

    if (*(*(maze + y) + x) == 'b') {
        return SOLVE_OK;
    }

    if (*(*(maze + y) + x)  == '#') {
        return SOLVE_FAILED; // wall
    }
    if (*(*(maze + y) + x) == '*') {
        return SOLVE_FAILED; // visited
    }

    *(*(maze + y) + x) = '*';

    // recursion (hell nah)
    if (solve_maze_req(maze, x + 1, y, row_amount, row_length) ||
        solve_maze_req(maze, x - 1, y, row_amount, row_length) ||
        solve_maze_req(maze, x, y + 1, row_amount, row_length) ||
        solve_maze_req(maze, x, y - 1, row_amount, row_length)) {
        return SOLVE_OK;
        }

    *(*(maze + y) + x) = ' '; // the magic
    return SOLVE_FAILED;
}

int calculate_row_amount(char** maze) {
    int row_amount = 0;
    while (*maze != NULL) {
        row_amount++;
        maze++;
    }
    return row_amount;
}

int calculate_row_length(char** maze) {
    int row_length = 0;
    char* row_cursor = *maze;
    while (*row_cursor != '\0') {
        row_length++;
        row_cursor++;
    }
    return row_length;
}

int validate_maze_array(char** maze, int row_length, int row_amount) {
    if (row_length <= 0 || row_amount <= 0) {
        return -5;
    }

    _Bool b_present = 0;
    for (int i = 0; i < row_amount; i++) {
        if (*(maze + i) == NULL) {
            return -4;
        }
        for (int j = 0; j < row_length; j++) {
            char c = *(*(maze + i) + j);
            if (!(c == 'a' || c == '#' || c == ' ' || c == 'b')) {
                return -1;
            }
            if (c == 'b') {
                if (b_present) {
                    return -3;
                }
                b_present = 1;
            }
        }
        if (*(*(maze + i) + row_length) != '\0') {
            return -2; // row longer than expected or not null terminated
        }
    }
    if (*(maze + row_amount) != NULL) {
        return -6; // too many rows
    }

    return b_present ? 0 : -1;
}

int solve_maze(char**maze, int x, int y) {
    if (maze == NULL || x < 0 || y < 0) {
        return SOLVE_ERROR;
    }
    int row_amount = calculate_row_amount(maze);
    int row_length = calculate_row_length(maze);
    if (y >= row_amount || x >= row_length) {
        return SOLVE_ERROR;
    }
    if (validate_maze_array(maze, row_length, row_amount)) {
        return SOLVE_ERROR;
    }

    const _Bool found = (_Bool) solve_maze_req(maze, x, y, row_amount, row_length);

    if (found) {
        *(*(maze + y) + x) = 'a';
        return SOLVE_OK;
    }

    return SOLVE_FAILED;
}

void display_maze(char **maze) {
    int i = 0, j = 0;

    while (*(maze + i) != NULL) {
        j = 0;
        while (*(*(maze + i) + j) != '\0') {
            printf("%c", *(*(maze + i) + j));
            j++;
        }
        printf("\n");
        i++;
    }
}

void free_maze(char **maze) {
    for (int i = 0; i < calculate_row_amount(maze); i++) {
        free(*(maze + i));
    }
    free(maze); // lol?
}
