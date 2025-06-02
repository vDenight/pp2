#include <stdio.h>
#include <stdlib.h>

#include "word_count.h"

enum main_code {
    OK = 0,
    CANNOT_OPEN_FILE = 4,
    ALLOC_FAIL = 8,
    NOT_ENOUGH_ARGS = 9
};

int* count_words_wrapper(const char *filename, int *err_code, int N, char** words_array_start);

int main(int argc, char** argv) {

    if (argc < 3) {
        printf("Not enough arguments");
        return NOT_ENOUGH_ARGS;
    }

    int err;
    char* filename = *(argv + 1);
    int number_of_words = argc - 2;

    int* counts = count_words_wrapper(filename, &err, number_of_words, (char**)(argv + 2));

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

int* count_words_wrapper(const char *filename, int *err_code, int N, char** words_array_start) { // this is the stupidest shit i have ever seen

    switch (N) {
        case 1:  return count_words(filename, err_code, N, *words_array_start);
        case 2:  return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1));
        case 3:  return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2));
        case 4:  return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3));
        case 5:  return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3), *(words_array_start + 4));
        case 6:  return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3), *(words_array_start + 4), *(words_array_start + 5));
        case 7:  return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3), *(words_array_start + 4), *(words_array_start + 5), *(words_array_start + 6));
        case 8:  return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3), *(words_array_start + 4), *(words_array_start + 5), *(words_array_start + 6), *(words_array_start + 7));
        case 9:  return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3), *(words_array_start + 4), *(words_array_start + 5), *(words_array_start + 6), *(words_array_start + 7), *(words_array_start + 8));
        case 10: return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3), *(words_array_start + 4), *(words_array_start + 5), *(words_array_start + 6), *(words_array_start + 7), *(words_array_start + 8), *(words_array_start + 9));
        case 11: return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3), *(words_array_start + 4), *(words_array_start + 5), *(words_array_start + 6), *(words_array_start + 7), *(words_array_start + 8), *(words_array_start + 9), *(words_array_start + 10));
        case 12: return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3), *(words_array_start + 4), *(words_array_start + 5), *(words_array_start + 6), *(words_array_start + 7), *(words_array_start + 8), *(words_array_start + 9), *(words_array_start + 10), *(words_array_start + 11));
        case 13: return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3), *(words_array_start + 4), *(words_array_start + 5), *(words_array_start + 6), *(words_array_start + 7), *(words_array_start + 8), *(words_array_start + 9), *(words_array_start + 10), *(words_array_start + 11), *(words_array_start + 12));
        case 14: return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3), *(words_array_start + 4), *(words_array_start + 5), *(words_array_start + 6), *(words_array_start + 7), *(words_array_start + 8), *(words_array_start + 9), *(words_array_start + 10), *(words_array_start + 11), *(words_array_start + 12), *(words_array_start + 13));
        case 15: return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3), *(words_array_start + 4), *(words_array_start + 5), *(words_array_start + 6), *(words_array_start + 7), *(words_array_start + 8), *(words_array_start + 9), *(words_array_start + 10), *(words_array_start + 11), *(words_array_start + 12), *(words_array_start + 13), *(words_array_start + 14));
        case 16: return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3), *(words_array_start + 4), *(words_array_start + 5), *(words_array_start + 6), *(words_array_start + 7), *(words_array_start + 8), *(words_array_start + 9), *(words_array_start + 10), *(words_array_start + 11), *(words_array_start + 12), *(words_array_start + 13), *(words_array_start + 14), *(words_array_start + 15));
        case 17: return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3), *(words_array_start + 4), *(words_array_start + 5), *(words_array_start + 6), *(words_array_start + 7), *(words_array_start + 8), *(words_array_start + 9), *(words_array_start + 10), *(words_array_start + 11), *(words_array_start + 12), *(words_array_start + 13), *(words_array_start + 14), *(words_array_start + 15), *(words_array_start + 16));
        case 18: return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3), *(words_array_start + 4), *(words_array_start + 5), *(words_array_start + 6), *(words_array_start + 7), *(words_array_start + 8), *(words_array_start + 9), *(words_array_start + 10), *(words_array_start + 11), *(words_array_start + 12), *(words_array_start + 13), *(words_array_start + 14), *(words_array_start + 15), *(words_array_start + 16), *(words_array_start + 17));
        case 19: return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3), *(words_array_start + 4), *(words_array_start + 5), *(words_array_start + 6), *(words_array_start + 7), *(words_array_start + 8), *(words_array_start + 9), *(words_array_start + 10), *(words_array_start + 11), *(words_array_start + 12), *(words_array_start + 13), *(words_array_start + 14), *(words_array_start + 15), *(words_array_start + 16), *(words_array_start + 17), *(words_array_start + 18));
        case 20: return count_words(filename, err_code, N, *words_array_start, *(words_array_start + 1), *(words_array_start + 2), *(words_array_start + 3), *(words_array_start + 4), *(words_array_start + 5), *(words_array_start + 6), *(words_array_start + 7), *(words_array_start + 8), *(words_array_start + 9), *(words_array_start + 10), *(words_array_start + 11), *(words_array_start + 12), *(words_array_start + 13), *(words_array_start + 14), *(words_array_start + 15), *(words_array_start + 16), *(words_array_start + 17), *(words_array_start + 18), *(words_array_start + 19));
        default:
            if (err_code) *err_code = COUNT_WRONG_INPUT; //xddd
            return NULL;
    }
}