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

int statistics(int **ptr, struct statistic_t **stats);
void display(int **ptr);
int save(const char *filename, int **ptr, enum save_format_t format);

void display_stats(struct statistic_t *stats, int stats_amount);

#endif //STATISTICS_UTILS_H
