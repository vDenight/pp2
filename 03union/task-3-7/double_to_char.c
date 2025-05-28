//
// Created by mrybczynski on 5/28/2025.
//
#include "double_to_char.h"

#include <stdio.h>

int save_double(const union double_to_char_t *dtc, const char *filename) {
    if (dtc == NULL || filename == NULL) return SAVE_WRONG_INPUT;

    FILE* f = fopen(filename, "wb");
    if (!f) return SAVE_CANNOT_OPEN_FILE;

    int fwrite_val = (int) fwrite(dtc->tab, sizeof(char), 8, f);

    if (fwrite_val != 8) {
        fclose(f);
        return SAVE_NOT_COMPLETED;
    }

    fclose(f);
    return SAVE_OK;
}

int load_double(union double_to_char_t *dtc, const char *filename) {
    if (dtc == NULL || filename == NULL) return LOAD_WRONG_INPUT;

    FILE* f = fopen(filename, "rb");
    if (!f) return LOAD_CANNOT_OPEN_FILE;

    int fread_val = (int) fread(dtc->tab, sizeof(char), 8, f);

    if (fread_val != 8) {
        fclose(f);
        return LOAD_FILE_CORRUPTED;
    }

    fclose(f);
    return LOAD_OK;
}
