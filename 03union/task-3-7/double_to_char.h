//
// Created by mrybczynski on 5/28/2025.
//

#ifndef DOUBLE_TO_CHAR_H
#define DOUBLE_TO_CHAR_H

union double_to_char_t {
    double d;
    char tab[8];
};

int save_double(const union double_to_char_t *dtc, const char *filename);
int load_double(union double_to_char_t *dtc, const char *filename);

enum save_code {
    SAVE_OK = 0,
    SAVE_WRONG_INPUT = 1,
    SAVE_CANNOT_OPEN_FILE = 2,
    SAVE_NOT_COMPLETED = 3
};

enum load_code {
    LOAD_OK = 0,
    LOAD_WRONG_INPUT = 1,
    LOAD_CANNOT_OPEN_FILE = 2,
    LOAD_FILE_CORRUPTED = 3
};

#endif //DOUBLE_TO_CHAR_H
