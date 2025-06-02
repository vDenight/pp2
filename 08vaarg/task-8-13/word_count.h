//
// Created by mrybczynski on 6/2/2025.
//

#ifndef WORD_COUNT_H
#define WORD_COUNT_H

int* count_words(const char *filename, int *err_code, int N, ...);

enum count_code {
    COUNT_OK = 0,
    COUNT_WRONG_INPUT = 1,
    COUNT_CANNOT_OPEN_FILE = 2,
    COUNT_ALLOC_FAIL = 3
};

#endif //WORD_COUNT_H
