//
// Created by mcihal on 26.04.25.
//

#ifndef STATISTICS_UTILS_H
#define STATISTICS_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "format_type.h"

struct statistic_t
{
    int min;
    int max;
    float avg;
    float standard_deviation;
    int range;
};

int load(const char *filename, int ***ptr, enum save_format_t format);
int statistics_row(int **ptr, struct statistic_t **stats);
void destroy(int ***ptr);
void display(int **ptr);

void display_stats(struct statistic_t *stats, int stats_amount);

#endif //STATISTICS_UTILS_H
