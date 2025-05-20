#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_utils.h"

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    ALLOC_FAIL = 8,
    UNSUPPORTED_FAIL_FORMAT = 7,
    FILE_CORRUPT = 6,
    CANNOT_OPEN_FILE = 4
};

enum file_format {
    BINARY,
    TEXT,
    UNSUPPORTED
};

enum file_format read_format(char* filename);

int main(void) {
    char* buffer = NULL;
    struct matrix_t* m1, *m2;
    int err;

    buffer = malloc(20 * sizeof(char));
    if (buffer == NULL) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    printf("Podaj nazwe pierwszego pliku: ");
    scanf("%19s", buffer);
    enum file_format format = read_format(buffer);

    switch (format) {
        case TEXT:
            m1 = matrix_load_t(buffer, &err);
            break;
        case BINARY:
            m1 = matrix_load_b(buffer, &err);
            break;
        case UNSUPPORTED:
            printf("Unsupported file format");
            free(buffer);
            return UNSUPPORTED_FAIL_FORMAT;
    }

    switch (err) {
        case LOAD_ALLOC_FAIL:
            printf("Failed to allocate memory");
            free(buffer);
            return ALLOC_FAIL;
        case LOAD_FILE_CORRUPTED:
            printf("File corrupted");
            free(buffer);
            return FILE_CORRUPT;
        case LOAD_OPEN_FILE_ERROR:
            printf("Couldn't open file");
            free(buffer);
            return CANNOT_OPEN_FILE;
        default:
    }

    printf("Podaj nazwe drugiego pliku: ");
    scanf("%19s", buffer);
    format = read_format(buffer);

    switch (format) {
        case TEXT:
            m2 = matrix_load_t(buffer, &err);
            break;
        case BINARY:
            m2 = matrix_load_b(buffer, &err);
            break;
        case UNSUPPORTED:
            printf("Unsupported file format");
            free(buffer);
            matrix_destroy_struct(&m1);
            return UNSUPPORTED_FAIL_FORMAT;
    }

    switch (err) {
        case LOAD_ALLOC_FAIL:
            printf("Failed to allocate memory");
            free(buffer);
            matrix_destroy_struct(&m1);
            return ALLOC_FAIL;
        case LOAD_FILE_CORRUPTED:
            printf("File corrupted");
            free(buffer);
            matrix_destroy_struct(&m1);
            return FILE_CORRUPT;
        case LOAD_OPEN_FILE_ERROR:
            printf("Couldn't open file");
            free(buffer);
            matrix_destroy_struct(&m1);
            return CANNOT_OPEN_FILE;
        default:
    }

    free(buffer); // no longer needed

    struct matrix_t* result;

    result = matrix_add(m1, m2);
    if (!result) {
        printf("Error\n");
    } else {
        matrix_display(result);
        matrix_destroy_struct(&result);
    }

    result = matrix_subtract(m1, m2);
    if (!result) {
        printf("Error\n");
    } else {
        matrix_display(result);
        matrix_destroy_struct(&result);
    }

    result = matrix_multiply(m1, m2);
    if (!result) {
        printf("Error\n");
    } else {
        matrix_display(result);
        matrix_destroy_struct(&result);
    }

    matrix_destroy_struct(&m1);
    matrix_destroy_struct(&m2);

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