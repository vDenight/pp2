#include <stdio.h>
#include <string.h>

#include "statistics_utils.h"

int get_format(char* filename, enum save_format_t* format);

int main(void) {

    int** table;
    struct statistic_t* stats = NULL;
    char* filename = NULL;
    filename = malloc (40); // to free

    if (filename == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Podaj nazwe pliku: ");

    scanf("%39s", filename);
    enum save_format_t format;

    if (get_format(filename, &format)) {
        free(filename);
        printf("Unsupported file format");
        return 7;
    }

    int load_value = load(filename, &table, format);

    switch (load_value) {
        case 0:
            break;
        case 2:
            free(filename);
            printf("Couldn't open file");
            return 4;
        case 3:
            free(filename);
            printf("File corrupted");
            return 6;
        case 4:
            free(filename);
            printf("Failed to allocate memory");
            return 8;
        default:
            display(table);
            break;
    }

    int stats_amount = statistics_row(table, &stats);

    if (stats_amount == -2) {
        free(filename);
        destroy(&table);
        printf("Failed to allocate memory");
        return 8;
    }

    display_stats(stats, stats_amount);

    free(stats);
    destroy(&table);
    free(filename);
    return 0;
}

int get_format(char* filename, enum save_format_t* format) {
    char* dot_pointer = NULL;

    dot_pointer = strchr(filename, '.');

    if (dot_pointer == NULL) {
        return -1;
    }
    if (dot_pointer - filename > 35) {
        return -2;
    }

    if (strcmp(dot_pointer + 1, "txt") == 0) {
        *format = fmt_text;
    } else if (strcmp(dot_pointer + 1, "bin") == 0) {
        *format = fmt_binary;
    } else {
        return -3;
    }

    return 0;
}