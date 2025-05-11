//
// Created by mcihal on 26.04.25.
//

#include "statistics_utils.h"

#include <limits.h>
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

float calculate_avg(int **ptr) {

    int row_amount = calculate_row_amount(ptr);
    int row_length = 0;
    float sum = 0;
    int num_amount = 0;

    for (int i = 0; i < row_amount; i++) {
        row_length = calculate_row_length(ptr, i);
        num_amount += row_length;
        for (int j = 0; j < row_length; j++) {
            sum += (float) *(*(ptr + i) + j);
        }
    }

    return sum / (float) num_amount;
}

int find_min(int** ptr) {
    int row_amount = calculate_row_amount(ptr);
    int row_length = 0;
    int min = INT_MAX;

    for (int i = 0; i < row_amount; i++) {
        row_length = calculate_row_length(ptr, i);
        for (int j = 0; j < row_length; j++) {
            if ( *(*(ptr + i) + j) < min) {
                min = *(*(ptr + i) + j);
            }
        }
    }

    return min;
}

int find_max(int** ptr) {
    int row_amount = calculate_row_amount(ptr);
    int row_length = 0;
    int max = INT_MIN;

    for (int i = 0; i < row_amount; i++) {
        row_length = calculate_row_length(ptr, i);
        for (int j = 0; j < row_length; j++) {
            if ( *(*(ptr + i) + j) > max) {
                max = *(*(ptr + i) + j);
            }
        }
    }

    return max;
}

float calculate_standard_deviation(int** ptr, float avg) {
    int row_amount = calculate_row_amount(ptr);
    int row_length = 0;
    int num_amount = 0;

    double sum_of_dev_squared = 0;

    for (int i = 0; i < row_amount; i++) {
        row_length = calculate_row_length(ptr, i);
        num_amount += row_length;
        for (int j = 0; j < row_length; j++) {
            sum_of_dev_squared += pow((float) *(*(ptr + i) + j) - avg, 2);
        }
    }
    return (float) sqrt(sum_of_dev_squared / (float) row_length);
}

int statistics(int **ptr, struct statistic_t **stats) {
    if (ptr == NULL || stats == NULL) {
        return 1;
    }

    int number_amount = 0;
    int row_amount = calculate_row_amount(ptr);
    for (int i = 0; i < row_amount; i++) {
        number_amount += calculate_row_length(ptr, i);
    }

    if (number_amount <= 0) return 3;

    *stats = malloc(sizeof(struct statistic_t));
    if (*stats == NULL) {
        return 2;
    }

    (*stats)->avg = calculate_avg(ptr);
    (*stats)->min = find_min(ptr);
    (*stats)->max = find_max(ptr);
    (*stats)->range = (*stats)->max - (*stats)->min;
    (*stats)->standard_deviation = calculate_standard_deviation(ptr, (*stats)->avg);

    return 0;
}

void display_stats(struct statistic_t *stats, int stats_amount) {
    for (int i = 0; i < stats_amount; i++) {
        printf("%d %d %d %.2f %.2f\n", (stats+i)->min, (stats+i)->max, (stats+i)->range,
            (stats+i)->avg, (stats+i)->standard_deviation);
    }
}

int save_txt(const char *filename, int **ptr);
int save_bin(const char *filename, int **ptr);

int save(const char *filename, int **ptr, enum save_format_t format) {
    if (filename == NULL || ptr == NULL) return 1;

    switch (format) {
        fmt_text:
            return save_txt(filename, ptr);
        fmt_binary:
            return save_bin(filename, ptr);
        default:
            return 1;
    }
}

int save_txt(const char *filename, int **ptr) {

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return 2;
    }

    int row_amount = calculate_row_amount(ptr);
    int row_length = 0;

    for (int i = 0; i < row_amount; i++) {
        row_length = calculate_row_length(ptr, i);
        for (int j = 0; j < row_length; j++) {
            fprintf(file, "%d ", *(*(ptr + i) + j));
        }
        fprintf(file, " -1\n");
    }
    fclose(file);
    return 0;
}

int save_bin(const char *filename, int **ptr) {

    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 2;
    }

    int row_amount = calculate_row_amount(ptr);
    int row_length = 0;

    for (int i = 0; i < row_amount; i++) {
        row_length = calculate_row_length(ptr, i);
        fwrite(*(ptr + i), sizeof(int), row_length + 1, file);
    }
    const void* null_pointer = NULL;
    fwrite(null_pointer, sizeof(void*), 1, file);

    fclose(file);
    return 0;
}