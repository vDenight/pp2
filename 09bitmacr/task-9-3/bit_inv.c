//
// Created by mcihal on 07.06.25.
//

#include "bit_inv.h"

#include <stdint.h>
#include <stdio.h>

void show(const void* ptr, size_t count) {
    uint8_t* ptr8 = (uint8_t*) ptr;
    for (size_t i = 0; i < count; i++) printf("%02x ", *(ptr8 + i));
}

uint8_t inverse_byte(uint8_t byte);

void inverse_bits(void* ptr, size_t offset, size_t count) {
    if (ptr == NULL || count < 1) return;
    uint8_t* ptr8 = (uint8_t*) ptr;
    for (size_t i = offset; i < count + offset; i++) {
        *(ptr8 + i) = inverse_byte(*(ptr8 + i));
    }
}

uint8_t inverse_byte(uint8_t byte) {
    uint8_t result = 0;
    for (int i = 0; i < 8; i++) {
        if (byte & (1 << i)) {
            result = result & ~(1 << i);
        } else {
            result = result | (1 << i);
        }
    }
    return result;
}
