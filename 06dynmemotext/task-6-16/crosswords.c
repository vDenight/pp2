//
// Created by mrybczynski on 5/7/2025.
//

#include "crosswords.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display(char **words) {
    while (*words != NULL) {
        printf("%s\n", *words);
        words++;
    }
}

_Bool validate_word(const char *word) {
    while (*word != '\0') {
        if (isalpha(*word)) {
            if (isupper(*word)) {
                word++;
                continue;
            }
            return 0;
        }
        return 0;
    }
    return 1;
}

int create_leading_word_cross(const char *first, const char *second, char ***result) {

    if (result == NULL) {
        return CREATE_WRONG_INPUT;
    }

    *result = NULL;

    if (first == NULL || second == NULL) {
        return CREATE_WRONG_INPUT;
    }

    if (!(validate_word(first) && validate_word(second))) {
        return CREATE_WRONG_INPUT;
    }

    // second - horizontal
    // first - vertical

    const char *second_common_char = second;
    const char *first_common_char = NULL;

    while (*second_common_char != '\0') {
        for (int i = 0; i < (int) strlen(first); i++) {
            if (*second_common_char == *(first + i)) {
                first_common_char = first + i;
                break;
            }
        }
        if (first_common_char)
            break;
        second_common_char++;
    }

    if (!first_common_char)
        return CREATE_CANT_CROSS;

    // now some calculation
    int row_amount = (int) (strlen(first));
    int row_min_length = (int) (second_common_char - second) + 1;
    int row_max_length = (int) (strlen(second));
    int max_row_index = (int) (first_common_char - first);

    // now mem alloc

    *result = calloc(row_amount + 1, sizeof(char *));
    if (*result == NULL)
        return CREATE_ALLOC_FAIL;

    int alloc_amount = 0;
    for (int i = 0; i < row_amount; i++) {

        if (i == max_row_index) {
            alloc_amount = row_max_length + 1;
        } else {
            alloc_amount = row_min_length + 1;
        }

        *((*result) + i) = calloc(alloc_amount, sizeof(char));
        if (*((*result) + i) == NULL) {
            for (int j = 0; j < i; j++) {
                free(*(*result + j));
            }
            free(*result);
            *result = NULL;
            return CREATE_ALLOC_FAIL;
        }
    }

    // mem alloc complete, now fill
    strcpy(*((*result) + max_row_index), second);
    int x = {0};
    for (int i = 0; i < row_amount; i++) {
        if (i == max_row_index)
            continue;
        x = row_min_length - 1;
        *(*(*result + i) + x) = *(first + i);
        x--;
        // fill with spaces
        while (x >= 0) {
            *(*(*result + i) + x) = ' ';
            x--;
        }
    }

    return max_row_index;
}

int get_cross_vert_len(char **cross) {
    int vert_len = 0;
    while (*cross != NULL) {
        vert_len++;
        cross++;
    }
    return vert_len;
}

int get_cross_horiz_len(char **cross) {
    int horiz_len = 0;
    while (*cross != NULL) {
        if ((int) strlen(*cross) > horiz_len) {
            horiz_len = (int) strlen(*cross);
        }
        cross++;
    }
    return horiz_len;
}

int get_cross_vert_x(char **cross) {
    int vert_x = get_cross_horiz_len(cross);
    while (*cross != NULL) {
        if ((int) strlen(*cross) - 1 < vert_x) {
            vert_x = (int) strlen(*cross) - 1;
        }
        cross++;
    }
    return vert_x;
}

int create_double_leading_word_cross(const char *first, const char *second, const char *third, const char *fourth,
                                     char ***result, char ***first_cross, char ***second_cross) {
    if (first == NULL || second == NULL || third == NULL || fourth == NULL || result == NULL)
        return DCREATE_WRONG_INPUT;

    *result = NULL;
    *first_cross = NULL;
    *second_cross = NULL;

    int f_horiz_y = create_leading_word_cross(second, first, first_cross);
    if (f_horiz_y < 0) {
        if (f_horiz_y == CREATE_WRONG_INPUT)
            return DCREATE_WRONG_INPUT;
        if (f_horiz_y == CREATE_CANT_CROSS)
            return DCREATE_CANT_CROSS;
        if (f_horiz_y == CREATE_ALLOC_FAIL)
            return DCREATE_ALLOC_FAIL;
    }

    int s_horiz_y = create_leading_word_cross(fourth, third, second_cross);
    if (s_horiz_y < 0) {
        if (s_horiz_y == CREATE_WRONG_INPUT) {
            destroy(*first_cross);
            return DCREATE_WRONG_INPUT;
        }
        if (s_horiz_y == CREATE_CANT_CROSS) {
            destroy(*first_cross);
            return DCREATE_CANT_CROSS;
        }
        if (s_horiz_y == CREATE_ALLOC_FAIL) {
            destroy(*first_cross);
            return DCREATE_ALLOC_FAIL;
        }
    }

    int f_vert_len = get_cross_vert_len(*first_cross);
    int s_vert_len = get_cross_vert_len(*second_cross);

    int f_upper_part = f_horiz_y;
    int s_upper_part = s_horiz_y;

    int f_lower_part = f_vert_len - f_upper_part - 1;
    int s_lower_part = s_vert_len - s_upper_part - 1;

    int row_amount = (f_upper_part > s_upper_part ? f_upper_part : s_upper_part) +
                     (f_lower_part > s_lower_part ? f_lower_part : s_lower_part) + 1;

    *result = calloc(row_amount + 1, sizeof(char *));

    if (*result == NULL) {
        destroy(*first_cross);
        destroy(*second_cross);
        return DCREATE_ALLOC_FAIL;
    }

    int min_row_length = get_cross_vert_x(*first_cross) + 1; // actual numer
    int medium_row_length = get_cross_horiz_len(*first_cross) + get_cross_vert_x(*second_cross) + 1 + 3; // three spaces
    int max_row_length = get_cross_horiz_len(*first_cross) + get_cross_horiz_len(*second_cross) + 3;
    printf("%d %d %d\n", get_cross_horiz_len(*first_cross), get_cross_horiz_len(*second_cross), get_cross_vert_x(*second_cross));
    int max_row_length_index = f_horiz_y > s_horiz_y ? f_horiz_y : s_horiz_y;

    printf("%d %d %d\n", min_row_length, medium_row_length, max_row_length);

    int i = 0;
    for (; i < f_upper_part - s_upper_part; i++) {
        *((*result) + i) = calloc(min_row_length + 1, sizeof(char));
        if (*((*result) + i) == NULL) {
            for (int j = 0; j < i; j++) {
                free(*(*result + j));
            }
            free(*result);
            destroy(*first_cross);
            destroy(*second_cross);
            *result = NULL;
            return DCREATE_ALLOC_FAIL;
        }
        memset(*((*result + i)), ' ', min_row_length);
    }

    for (; i < max_row_length_index; i++) {
        *((*result) + i) = calloc(medium_row_length + 1, sizeof(char));
        if (*((*result) + i) == NULL) {
            for (int j = 0; j < i; j++) {
                free(*(*result + j));
            }
            free(*result);
            destroy(*first_cross);
            destroy(*second_cross);
            *result = NULL;
            return DCREATE_ALLOC_FAIL;
        }
        memset(*((*result) + i), ' ', medium_row_length);
    }

    *((*result) + i) = calloc(max_row_length + 1, sizeof(char)); // error handling later;
    if (*((*result) + i) == NULL) {
        for (int j = 0; j < i; j++) {
            free(*(*result + j));
        }
        free(*result);
        destroy(*first_cross);
        destroy(*second_cross);
        *result = NULL;
        return DCREATE_ALLOC_FAIL;
    }
    memset(*((*result) + i), ' ', max_row_length);
    i++;

    for (; i < max_row_length_index + 1 + s_lower_part; i++) {
        *((*result) + i) = calloc(medium_row_length + 1, sizeof(char));
        if (*((*result) + i) == NULL) {
            for (int j = 0; j < i; j++) {
                free(*(*result + j));
            }
            free(*result);
            destroy(*first_cross);
            destroy(*second_cross);
            *result = NULL;
            return DCREATE_ALLOC_FAIL;
        }
        memset(*((*result) + i), ' ', medium_row_length);
    }

    for (; i < max_row_length_index + 1 + f_lower_part; i++) {

        *((*result) + i) = calloc(min_row_length + 1, sizeof(char));
        if (*((*result) + i) == NULL) {
            for (int j = 0; j < i; j++) {
                free(*(*result + j));
            }
            free(*result);
            destroy(*first_cross);
            destroy(*second_cross);
            *result = NULL;
            return DCREATE_ALLOC_FAIL;
        }
        memset(*((*result) + i), ' ', min_row_length);
    }

    // printf("%d, %d\n", row_amount, i);

    // now we should input the data
    int y_displacement = f_upper_part - s_upper_part;
    int x_displacement = get_cross_horiz_len(*first_cross) + 3;

    // copy the first cross
    for (int j = 0; j < f_vert_len; j++) {
        int current_char_index = 0;
        int double_y_displacement = y_displacement < 0 ? -y_displacement : 0;
        while (*(*(*first_cross + j) + current_char_index)) {
            memcpy(*(*result + j + double_y_displacement) + current_char_index,
                   *(*first_cross + j) + current_char_index, sizeof(char));
            current_char_index++;
        }
    }

    // coping the second cross
    for (int j = 0; j < s_vert_len; j++) {
        int current_char_index = 0;
        int double_y_displacement = y_displacement > 0 ? y_displacement : 0;
        while (*(*(*second_cross + j) + current_char_index)) {
            memcpy(*(*result + j + double_y_displacement) + current_char_index + x_displacement,
                   *(*second_cross + j) + current_char_index, sizeof(char));
            current_char_index++;
        }
    }
    return DCREATE_OK;
}

void destroy(char **words) {
    if (words == NULL) return;
    char **current = words;
    while (*current != NULL) {
        free(*current);
        current++;
    }
    free(words);
}
