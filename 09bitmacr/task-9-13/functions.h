//
// Created by mrybczynski on 6/5/2025.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define COUNT_BITS(value, pointer_to_bits_set_counter, pointer_to_bits_cleared_counter) \
    int val_bit_size = (int) sizeof(value) * 8; \
    int bits_set = 0; \
    int bits_cleared = 0; \
    \
    for(int i = 0; i < val_bit_size; i++) { \
        if (value & (1U << i)) bits_set++; \
        else bits_cleared++; \
    } \
    \
    *(pointer_to_bits_set_counter) = bits_set; \
    *(pointer_to_bits_cleared_counter) = bits_cleared; \


#endif //FUNCTIONS_H
