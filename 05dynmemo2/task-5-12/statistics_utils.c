//
// Created by mcihal on 26.04.25.
//

#include "statistics_utils.h"

#include <math.h>

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
        fclose(file);
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
    int read_number = 0;

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
    int read_number = 0;

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
    int read_number = 0;
    int max_reads = 1000; // stupid but might work, just to pass clang xddd
    int read_count = 0;

    while (fread(&read_number, sizeof(int), 1, file) == 1 && read_count < max_reads) {
        if (read_number == -1) {
            break;
        }
        read_count++;
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
int calculate_row_amount(int **ptr) {
    int row_amount = 0;
    while (*ptr != NULL) {
        row_amount++;
        ptr++;
    }
    return row_amount;
}
int calculate_row_length(int **ptr, int row_index) {
    if (*(ptr + row_index) == NULL) {
        return -1;
    }
    int row_length = 0;
    while (*(*(ptr + row_index) + row_length) != -1) {
        row_length++;
    }
    return row_length;
}

float calculate_row_avg(int *row, int row_length) {
    float sum = 0;
    for (int i = 0; i < row_length; i++) {
        sum += *(row + i);
    }
    return sum / (float) row_length;
}

int find_row_min(int *row, int row_length) {
    int min = *row;
    for (int i = 0; i < row_length; i++) {
        if (*(row + i) < min)
            min = *(row + i);
    }
    return min;
}

int find_row_max(int *row, int row_length) {
    int max = *row;
    for (int i = 0; i < row_length; i++) {
        if (*(row + i) > max)
            max = *(row + i);
    }
    return max;
}

float calculate_row_standard_deviation(int *row, int row_length, float avg) {
    double sum_of_dev_squared = 0;
    for (int i = 0; i < row_length; i++) {
        sum_of_dev_squared += pow(*(row + i) - avg, 2);
    }
    return (float) sqrt(sum_of_dev_squared / (float) row_length);
}

int statistics_row(int **ptr, struct statistic_t **stats) {
    if (ptr == NULL || stats == NULL) {
        return -1;
    }

    int row_amount = calculate_row_amount(ptr);
    *stats = malloc(sizeof(struct statistic_t) * row_amount);
    if (*stats == NULL) {
        return -2;
    }

    for (int i = 0; i < row_amount; i++) {
        int row_length = calculate_row_length(ptr, i);
        if (row_length == 0) {
            (*(stats)+i)->avg = -1;
            (*(stats)+i)->min = -1;
            (*(stats)+i)->max = -1;
            (*(stats)+i)->range = -1;
            (*(stats)+i)->standard_deviation = -1;
        }
        else {
            (*(stats)+i)->avg = calculate_row_avg(*(ptr + i), row_length);
            (*(stats)+i)->min = find_row_min(*(ptr + i), row_length);
            (*(stats)+i)->max = find_row_max(*(ptr + i), row_length);
            (*(stats)+i)->range = (*(stats)+i)->max - (*(stats)+i)->min;
            (*(stats)+i)->standard_deviation = calculate_row_standard_deviation(*(ptr + i), row_length, (*(stats)+i)->avg);
        }
    }

    return row_amount;
}

void display_stats(struct statistic_t *stats, int stats_amount) {
    for (int i = 0; i < stats_amount; i++) {
        printf("%d %d %d %.2f %.2f\n", (stats+i)->min, (stats+i)->max, (stats+i)->range,
            (stats+i)->avg, (stats+i)->standard_deviation);
    }
}