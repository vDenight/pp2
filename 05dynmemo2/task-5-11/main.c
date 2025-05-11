#include <stdio.h>
#include <string.h>

#include "statistics_utils.h"

char* add_format(char* filename, enum save_format_t format);

int main(void) {
    char* filename = NULL;

    int A[] = {10, 20, 30, 40, 50, 60, 70, -1};
    int B[] = {100, 200, 300, 400, 500, 600, 700, 800, -1};
    int C[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, -1};
    int* D[] = {A, B, C, NULL};

    display(D);

    filename = malloc(40 * sizeof(char));
    if (filename == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Podaj nazwę pliku: ");
    scanf("%39s", filename);

    char* txt_filename = add_format(filename, fmt_text);
    if (txt_filename == NULL) {
        free(filename);
        printf("Failed to allocate memory");
        return 8;
    }

    int save_val = save(txt_filename, D, fmt_text);
    if (save_val == 2) {
        printf("Couldn't create file\n");
    } else {
        printf("File saved\n");
    }
    free(txt_filename);

    char* bin_filename = add_format(filename, fmt_binary);
    if (bin_filename == NULL) {
        free(filename);
        printf("Failed to allocate memory");
        return 8;
    }

    save_val = save(bin_filename, D, fmt_binary);
    if (save_val == 2) {
        printf("Couldn't create file\n");
    } else {
        printf("File saved\n");
    }
    free(bin_filename);
    free(filename);

    struct statistic_t* stat_add;
    int stat_val = statistics(D, &stat_add);
    if (stat_val == 2) {
        printf("Failed to allocate memory");
        return 8;
    }

    display_stats(stat_add, 1);
    free(stat_add);

    return 0;
}

char* add_format(char* filename, enum save_format_t format) {

    char* new_filename = malloc(strlen(filename) + 1 + 4);
    if (new_filename == NULL) return NULL;

    strcpy(new_filename, filename);
    switch (format) {
        case fmt_text:
            strcat(new_filename, ".txt");
            break;
        case fmt_binary:
            strcat(new_filename, ".bin");
            break;
        default:
            return new_filename;
    }
    return new_filename;
}