//
// Created by mrybczynski on 5/5/2025.
//

#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H
#include <stdint.h>

union pixel {
    uint8_t pixel_value;
    uint8_t least_significant : 1;
};

union bit_character {
    char char_value;
    struct {
        uint8_t b0 : 1;
        uint8_t b1 : 1;
        uint8_t b2 : 1;
        uint8_t b3 : 1;
        uint8_t b4 : 1;
        uint8_t b5 : 1;
        uint8_t b6 : 1;
        uint8_t b7 : 1;
    } bits;
};

int encode(const char *input, char *txt, const char *output);
int decode(const char * filename, char *txt, int size);

#endif //STEGANOGRAPHY_H
