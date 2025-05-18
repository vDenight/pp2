#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_utils.h"

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    INCORRECT_INPUT_DATA = 2,
    ALLOC_FAIL = 8,
    UNSUPPORTED_FAIL_FORMAT = 5,
    CANT_CREATE_FILE = 7
};

enum file_format {
    BINARY,
    TEXT,
    UNSUPPORTED
};

enum file_format read_format(char* filename);

int main(void) {
    struct matrix_t* matrix_point = {0};

    printf("Podaj szerokość i wysokość: ");

    int scanf_val = 0, height = 0, width = 0;
    scanf_val = scanf("%d %d", &width, &height);

    if (scanf_val != 2) {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }
    if (width < 1 || height < 1) {
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }

    matrix_point = matrix_create_struct(width, height);

    if (matrix_point == NULL) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    printf("Podaj wartości: ");
    int read_val = matrix_read(matrix_point);
    if (read_val == READ_WRONG_FORMAT) {
        printf("Incorrect input");
        matrix_destroy_struct(&matrix_point);
        return INCORRECT_INPUT;
    }

    struct matrix_t* t_matrix_point = matrix_transpose(matrix_point);

    if (t_matrix_point == NULL) {
        printf("Failed to allocate memory");
        matrix_destroy_struct(&matrix_point);
        return ALLOC_FAIL;
    }
    matrix_destroy_struct(&matrix_point);

    char* buffer = malloc(41 * sizeof(char));
    if (buffer == NULL) {
        printf("Failed to allocate memory");
        matrix_destroy_struct(&t_matrix_point);
        return ALLOC_FAIL;
    }

    printf("Podaj sciezke do pliku: ");
    scanf("%40s", buffer);

    enum file_format format = read_format(buffer);
    int save_result = 0;
    switch (format) {
        case UNSUPPORTED:
            printf("Unsupported file format");
            free(buffer);
            matrix_destroy_struct(&t_matrix_point);
            return UNSUPPORTED_FAIL_FORMAT;
        case BINARY:
            save_result = matrix_save_b(t_matrix_point, buffer);
            break;
        case TEXT:
            save_result = matrix_save_t(t_matrix_point, buffer);
            break;
    }

    free(buffer);
    matrix_destroy_struct(&t_matrix_point);

    if (save_result == SAVE_FILE_OPEN_ERROR) {
        matrix_destroy_struct(&t_matrix_point);
        printf("Couldn't create file");
    }

    printf("File saved");

    return OK;
}

enum file_format read_format(char* filename) {
    if (filename == NULL) return UNSUPPORTED;

    char* dot = strrchr(filename, '.');
    if (dot == NULL) return UNSUPPORTED;
    if (strcmp(dot + 1, "bin") == 0) return BINARY;
    if (strcmp(dot + 1, "txt") == 0) return TEXT;
    return UNSUPPORTED;
}