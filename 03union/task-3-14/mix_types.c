//
// Created by mcihal on 27.05.25.
//

#include "mix_types.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int compare_mix_types(const void *a, const void *b) {
    struct data_t** aa = (struct data_t**)a;
    struct data_t** bb = (struct data_t**)b;

    double aa_val = {0};
    double bb_val = {0};

    if ((*aa)->type == CHARACTER) aa_val = (double) (int) (*aa)->c;
    if ((*bb)->type == CHARACTER) bb_val = (double) (int) (*bb)->c;
    
    if ((*aa)->type == INTEGER) aa_val = (double) (*aa)->i;
    if ((*bb)->type == INTEGER) bb_val = (double) (*bb)->i;
    
    if ((*aa)->type == DOUBLE) aa_val = (*aa)->d;
    if ((*bb)->type == DOUBLE) bb_val = (*bb)->d;

    double comparison = (bb_val - aa_val);

    if (comparison < 0) return -1;
    if (comparison > 0) return 1;

    int aa_type_val = 0;
    int bb_type_val = 0;

    if ((*aa)->type == CHARACTER) aa_type_val = 0;
    if ((*bb)->type == CHARACTER) bb_type_val = 0;
    if ((*aa)->type == INTEGER) aa_type_val = 2;
    if ((*bb)->type == INTEGER) bb_type_val = 2;
    if ((*aa)->type == DOUBLE) aa_type_val = 1;
    if ((*bb)->type == DOUBLE) bb_type_val = 1;
    return aa_type_val - bb_type_val;

}

int sort(struct data_t *data[], int size) {
    if (data == NULL || size <= 0) return 1;

    qsort(data, size, sizeof(struct data_t*), compare_mix_types);

    return 0;
}


void display(struct data_t *data[], int size) {
    if (data == NULL || size <= 0) return;
    for (int i = 0; i < size; i++) {
        switch ((*(data + i))->type) {
            case CHARACTER:
                printf("%c ", ((*(data + i))->c)); break;
            case INTEGER:
                printf("%d ", ((*(data + i))->i)); break;
            case DOUBLE:
                printf("%.14f ", ((*(data + i))->d)); break;
        }
    }
}

int read_mix_type(struct data_t* element) {

    int c;
    _Bool started = 0;
    _Bool is_negative = 0;
    _Bool after_dot = 0;
    _Bool is_int = 1;
    _Bool is_char = 1;

    double val = 0;
    double magnitude = 0.1;
    double after_dot_part = 0;

    while (1) {
        c = getchar();

        if (c == ' ') {
            if (!started) return READ_CORRUPTED_DATA;
            if (is_negative && is_char && after_dot) return READ_CORRUPTED_DATA;
            if (is_negative && is_char) {
                element->type = CHARACTER;
                element->c = '-';
                return READ_OK;
            }
            if (is_int) {
                    element->type = INTEGER;
                    element->i = is_negative ? (int) -val : (int) val;
                    return READ_OK;
                }
                // else its float

                // check if there was digit after dor
                if (magnitude == 0.1) return READ_CORRUPTED_DATA;

                element->type = DOUBLE;
                element->d = is_negative ? -(val + after_dot_part) : val + after_dot_part;
                return READ_OK;
        }

        if (c == '\n') {
            if (!started) return READ_CORRUPTED_DATA;
            if (is_negative && is_char && after_dot) return READ_CORRUPTED_DATA;
            if (is_negative && is_char) {
                element->type = CHARACTER;
                element->c = '-';
                return READ_FINISHED;
            }
            if (is_int) {
                element->type = INTEGER;
                element->i = is_negative ? (int) -val : (int) val;
                return READ_FINISHED;
            }
            // else its float

            // check if there was digit after dor
            if (magnitude == 0.1) return READ_CORRUPTED_DATA;

            element->type = DOUBLE;
            element->d = is_negative ? -(val + after_dot_part) : val + after_dot_part;
            return READ_FINISHED;
        }

        if (c == '-') {
            if (started) return READ_CORRUPTED_DATA;
            started = 1;
            is_negative = 1;
            continue; // might be char might not
        }

        if (c == '.') {
            if (!started) {
                // it might be char if not read_corrupted
                element->type = CHARACTER;
                element->c = '.';
                c = getchar();
                if (c == '\n') return READ_FINISHED;
                if (c == ' ') return READ_OK;
                return READ_CORRUPTED_DATA; // it was not char
            }
            if (after_dot) return READ_CORRUPTED_DATA;
            // must be started then (no char)
            after_dot = 1;
            is_int = 0;
            continue; // it is not a char
        }

        if (!(isdigit(c))) {
            if (started) return READ_CORRUPTED_DATA;
            element->type = CHARACTER;
            element->c = c;
            c = getchar();
            if (c == '\n') return READ_FINISHED;
            if (c == ' ') return READ_OK;
            return READ_CORRUPTED_DATA;
        }

        // it is a digit
        is_char = 0;
        started = 1;
        if (!after_dot) {
            val = val * 10 + (c - '0');
        } else {
            after_dot_part = after_dot_part + (c - '0') * magnitude;
            magnitude *= 0.1;
        }

    }
}
