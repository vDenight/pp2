//
// Created by mcihal on 26.04.25.
//

#ifndef STATISTICS_UTILS_H
#define STATISTICS_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "format_type.h"


int load(const char *filename, int ***ptr, enum save_format_t format);
// int statistics_row(int **ptr, struct statistic_t **stats);
void destroy(int ***ptr);
void display(int **ptr);

int calculate_row_amount_txt(FILE *file);
int calculate_row_length_txt(FILE *file);
int load_txt(const char *filename, int ***ptr);
int load_bin(const char *filename, int ***ptr);

#endif //STATISTICS_UTILS_H
