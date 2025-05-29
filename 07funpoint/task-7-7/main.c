#include <stdio.h>
#include <stdlib.h>

#include "comparators.h"

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    INCORRECT_INPUT_DATA = 2,
    ALLOC_FAIL = 8
};

int main(void) {

    printf("Enter width and height: ");
    int width = 0, height = 0;

    if (scanf("%d %d", &width, &height) != 2) {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }

    if (width <= 0 || height <= 0) {
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }

    // now we alloc

    int** tab = calloc(height, sizeof(int*));
    if (!tab) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    for (int i = 0; i < height; i++) {
        *(tab + i) = calloc(width, sizeof(int));
        if (*(tab + i) == NULL) {
            for (int j = 0; j < i; j++) {
                free(*(tab + j)); // free previously allocated tabs
            }
            free(tab); // free the table of pointers
            printf("Failed to allocate memory");
            return ALLOC_FAIL;
        }
    }

    printf("Enter data: ");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (scanf("%d", *(tab + i) + j) != 1) {
                for (int k = 0; k < height; k++) {
                    free(*(tab + k));
                }
                free(tab);
                printf("Incorrect input");
                return INCORRECT_INPUT;
            }
        }
    }

    int choice;
    printf("Selection choice: ");

    if (scanf("%d", &choice) != 1) {
        for (int k = 0; k < height; k++) {
            free(*(tab + k));
        }
        free(tab);
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }

    if (choice < 0 || choice > 2) {
        for (int k = 0; k < height; k++) {
            free(*(tab + k));
        }
        free(tab);
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }

    switch (choice) {
        case 0:
            sort_rows(tab, width, height, comp_min);
            break;
        case 1:
            sort_rows(tab, width, height, comp_max);
            break;
        case 2:
            sort_rows(tab, width, height, comp_sum);
            break;
        default: break;
    }

    // display the table
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d ", *(*(tab + i) + j));
        }
        printf("\n");
    }

    // cleanup
    for (int k = 0; k < height; k++) {
        free(*(tab + k));
    }
    free(tab);

    return OK;
}