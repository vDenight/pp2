#include <stdio.h>
#include <stdlib.h>

#include "word_count.h"

enum main_code {
    OK = 0,
    CANNOT_OPEN_FILE = 4,
    ALLOC_FAIL = 8,
    NOT_ENOUGH_ARGS = 9
};

int main(int argc, char** argv) {

    if (argc < 3) {
        printf("Not enough arguments");
        return NOT_ENOUGH_ARGS;
    }

    int err;
    char* filename = *(argv + 1);
    int number_of_words = argc - 2;

    int* counts = count_words(filename, &err, number_of_words, (argv + 2));
    if (err == COUNT_CANNOT_OPEN_FILE) {
        printf("Couldn't open file");
        return CANNOT_OPEN_FILE;
    }
    if (err == COUNT_ALLOC_FAIL) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    for (int i = 0; i < number_of_words; i++) {
        printf("%d\n", *(counts + i));
    }
    free(counts);
    return OK;
}