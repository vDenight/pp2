//
// Created by mcihal on 26.04.25.
//

#include "statistics_utils.h"

void display(int **ptr) {
    if (ptr == NULL) {
      return;
    }

    while (*ptr != NULL) {
        int* ptr_cursor = *ptr;
        while (*ptr_cursor != -1) {
          printf("%d ", *ptr_cursor);
          ptr_cursor++;
        }
        printf("\n");
        ptr++;
    }
}

int load(const char *filename, int ***ptr, enum save_format_t format) {

    switch (format) {
        case fmt_text:
            return load_txt(filename, ptr);
        case fmt_binary:
            return load_bin(filename, ptr);
        default:
            return 1;
    }
}

int calculate_row_amount_txt(FILE *file) {
    int row_amount = 0;
    long old_pos = ftell(file);
    fseek(file, 0, SEEK_SET);
    int fscanf_val;
    int read_number;

    while(1) {

       fscanf_val = fscanf(file, "%d", &read_number);

        if (fscanf_val == -1) {
            break;
        }

       if (fscanf_val == 0) {
           return -1;
       }

       if (read_number == -1) {
           row_amount++;
       }
    }

    fseek(file, old_pos, SEEK_SET);
    return row_amount;
}

int calculate_row_length_txt(FILE *file) {

    long old_pos = ftell(file);
    int row_length = 0;
    int fscanf_val;
    int read_number;
    while(1) {
        fscanf_val = fscanf(file, "%d", &read_number);
        if (fscanf_val == -1) {
            return -2; // something is wrong
        }
        if (fscanf_val == 0) {
            return -1; // non numeric char
        }
        if (read_number == -1) {
            fseek(file, old_pos, SEEK_SET);
            return row_length;
        }
        row_length++;
    }
}

void input_row_data_from_txt(FILE *file, int row_length, int **ptr) {
    long int start_pos = ftell(file);
    for (int i = 0; i < row_length; i++) {
        fscanf(file, "%d", *ptr + i);
    }
    fseek(file, start_pos, SEEK_SET);
}

void advance_row_txt(FILE *file) {
    int read_number;
    while(1) {
        fscanf(file, "%d", &read_number);
        if (read_number == -1) {
            break;
        }
    }
}

int load_txt(const char *filename, int ***ptr) {

    if (filename == NULL || ptr == NULL) {
        return 1;
    }

    FILE *file = fopen(filename, "r"); // to close

    if (file == NULL) {
        return 2;
    }

    int row_amount = calculate_row_amount_txt(file);

    if (row_amount <= 0) {
        return 3;
    }

    *ptr = malloc(sizeof(int*) * (row_amount + 1)); // to free
    if (*ptr == NULL) {
        fclose(file);
        return 4;
    }
    *(*ptr + row_amount) = NULL; // set last element to null

    int row_length = 0;
    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < row_amount; i++) {
        row_length = calculate_row_length_txt(file);

        if (row_length < 0) { // something is wrong, file corrupted
            for (int j = 0; j < i; j++) {
                free(*(*ptr + j));
            }
            free(*ptr);
            fclose(file);
            return 3;
        }

        *(*ptr + i) = malloc(sizeof(int) * (row_length + 1)); // to free

        if (*(*ptr + i) == NULL) { // alloc failed
            for (int j = 0; j < i; j++) {
                free(*(*ptr + j));
            }
            free(*ptr);
            fclose(file);
            return 4;
        }

        input_row_data_from_txt(file, row_length + 1, *ptr + i); // inputing
        advance_row_txt(file); // advance after input read
    }

    fseek(file, 0, SEEK_SET);

    fclose(file);
    return 0;
}

int calculate_row_amount_bin(FILE *file) {
    int row_amount = 0;
    long old_pos = ftell(file);
    fseek(file, 0, SEEK_SET);
    int read_number;

    while (fread(&read_number, sizeof(int), 1, file) == 1) {
        if (read_number == -1) {
            row_amount++;
        }
    }

    fseek(file, old_pos, SEEK_SET);
    return row_amount;
}

int calculate_row_length_bin(FILE *file) {
    long old_pos = ftell(file);
    int row_length = 0;
    int read_number;

    while (fread(&read_number, sizeof(int), 1, file) == 1) {
        if (read_number == -1) {
            fseek(file, old_pos, SEEK_SET);
            return row_length;
        }
        row_length++;
    }

    fseek(file, old_pos, SEEK_SET);
    return -2; // End of file reached without finding -1
}

void input_row_data_from_bin(FILE *file, int row_length, int **ptr) {
    long int start_pos = ftell(file);
    fread(*ptr, sizeof(int), row_length, file);
    fseek(file, start_pos, SEEK_SET);
}

void advance_row_bin(FILE *file) {
    int read_number;
    while (fread(&read_number, sizeof(int), 1, file) == 1) {
        if (read_number == -1) {
            break;
        }
    }
}

int load_bin(const char *filename, int ***ptr) {
    if (filename == NULL || ptr == NULL) {
        return 1;
    }

    FILE *file = fopen(filename, "rb"); // Open in binary read mode

    if (file == NULL) {
        return 2;
    }

    int row_amount = calculate_row_amount_bin(file);

    if (row_amount <= 0) {
        fclose(file);
        return 3;
    }

    *ptr = malloc(sizeof(int*) * (row_amount + 1));
    if (*ptr == NULL) {
        fclose(file);
        return 4;
    }
    *(*ptr + row_amount) = NULL; // Set last element to NULL

    int row_length = 0;
    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < row_amount; i++) {
        row_length = calculate_row_length_bin(file);

        if (row_length < 0) { // Something is wrong, file corrupted or end of file
            for (int j = 0; j < i; j++) {
                free(*(*ptr + j));
            }
            free(*ptr);
            fclose(file);
            return 3;
        }

        *(*ptr + i) = malloc(sizeof(int) * (row_length + 1));
        if (*(*ptr + i) == NULL) { // Allocation failed
            for (int j = 0; j < i; j++) {
                free(*(*ptr + j));
            }
            free(*ptr);
            fclose(file);
            return 4;
        }

        input_row_data_from_bin(file, row_length + 1, *ptr + i);
        advance_row_bin(file);
    }

    fclose(file);
    return 0;
}

void destroy(int ***ptr) {
    if (ptr == NULL) {
        return;
    }

    if (*ptr == NULL) {
        return;
    }

    int** ptr_cursor = *ptr;

    while (*ptr_cursor != NULL) {
        free(*ptr_cursor);
        ptr_cursor++;
    }
    free(*ptr);
}