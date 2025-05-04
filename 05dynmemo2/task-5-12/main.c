#include <stdio.h>
#include "statistics_utils.h"

int main(void) {

    FILE* file = fopen("test.txt", "r");

    // printf("rows amount: %d\n", calculate_row_amount(file));
    // for (int i = 0; i < calculate_row_amount(file) + 1; i++) {
    //     printf("row %d length: %d\n", i + 1, calculate_row_length(file));
    // }
    int** table;

    int load_val = load("test2.bin", &table, fmt_binary);
    printf("load value: %d\n", load_val);
    display(table);
    destroy(&table);

    load_val = load("test.txt", &table, fmt_text);
    printf("load value: %d\n", load_val);
    display(table);
    destroy(&table);

    return 0;
}