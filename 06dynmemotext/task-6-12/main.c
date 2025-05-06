#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "maze.h"

enum main_error_code {
    OK = 0,
    CANT_OPEN_FILE = 4,
    FILE_CORRUPTED = 6,
    CANT_FIND_PATH = 0,
    ALLOC_FAIL = 8
};

int find_coordinates(int* x, int* y, char** maze);

int main(void) {
    char* filename = NULL;
    char** lab = NULL;

    filename = malloc(31 * sizeof(char));
    if (filename == NULL) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    printf("Enter filename: ");
    scanf("%30s", filename);
    int load_val = load_maze(filename, &lab);
    switch (load_val) {

        case LOAD_OK:
            break;
        case LOAD_FILE_OPEN_ERROR:
            free(filename);
            printf("Couldn't open file");
            return CANT_OPEN_FILE;
        case LOAD_FILE_CORRUPTED_ERROR:
            free(filename);
            printf("File corrupted");
            return FILE_CORRUPTED;
        case LOAD_ALLOC_ERROR:
            free(filename);
            printf("Failed to allocate memory");
            return ALLOC_FAIL;
        default:
            free(filename);
            return 2137;
    }

    int x = 0, y = 0;
    if (find_coordinates(&x, &y, lab)) {
        free(filename);
        free_maze(lab);
        printf("File corrupted");
        return FILE_CORRUPTED;
    }

    int solve_val = solve_maze(lab, x, y);
    switch (solve_val) {
        case SOLVE_OK:
            break;
        case SOLVE_FAILED:
            free(filename);
            free_maze(lab);
            printf("Couldn't find path");
            return CANT_FIND_PATH;
        case SOLVE_ERROR:
            free(filename);
            free_maze(lab);
            printf("File corrupted");
            return FILE_CORRUPTED;
        default:
            free(filename);
            free_maze(lab);
            return 2137;
    }

    display_maze(lab);
    free(filename);
    free_maze(lab);

    return OK;
}

int find_coordinates(int* x, int* y, char** maze) {

    _Bool found = 0;
    int i = 0, j = 0;

    while (*(maze + i) != NULL) {
        j = 0;
        while (*(*(maze + i) + j) != '\0') {
            if (*(*(maze + i) + j) == 'a') {
                if (found == 1) {
                    return -1;
                }
                found = 1;
                *x = j;
                *y = i;
            }
            j++;
        }
        i++;
    }

    return 0;
}