//
// Created by mrybczynski on 6/5/2025.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define COUNT_BITS(value, pointer_to_bits_set_counter, pointer_to_bits_cleared_counter) \
    { \
        int val_bit_size = (int) sizeof(value) * 8; \
        *pointer_to_bits_set_counter = 0; \
        *pointer_to_bits_cleared_counter = 0; \
        \
        for(int i = 0; i < val_bit_size; i++) { \
            if (value & (1UL << i)) (*pointer_to_bits_set_counter)++; \
            else (*pointer_to_bits_cleared_counter)++; \
        } \
        \
    } \

# define DISPLAY_BITS(value) \
    { \
        int val_bit_size = (int) sizeof(value) * 8; \
        \
        for(int i = val_bit_size - 1; i >= 0; i--) { \
            if (value & (1UL << i)) putchar('1'); \
            else putchar('0'); \
        } \
    } \

#define REVERSE_BITS(pointer_to_variable) \
    { \
        int val_bit_size = (int) sizeof(*pointer_to_variable) * 8; \
        \
        _Bool temp1, temp2; \
        for(int i = 0; i < val_bit_size / 2; i++) { \
            int front_index = i; \
            int back_index = val_bit_size - i - 1; \
            if (*pointer_to_variable & (1UL << front_index)) temp1 = 1; \
            else temp1 = 0; \
            if (*pointer_to_variable & (1UL << back_index)) temp2 = 1; \
            else temp2 = 0; \
            if (temp1 == 1) *pointer_to_variable = *pointer_to_variable | (1UL << back_index); \
            else *pointer_to_variable = *pointer_to_variable & ~(1UL << back_index); \
            if (temp2 == 1) *pointer_to_variable = *pointer_to_variable | (1UL << front_index); \
            else *pointer_to_variable = *pointer_to_variable & ~(1UL << front_index); \
        } \
    } \


#endif //FUNCTIONS_H
