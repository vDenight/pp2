#include <stdio.h>
#include <stdlib.h>

#include "figure.h"

int main(void) {
    // struct figure_t figures[] = {
    //     {.type = CIRCLE, .circ = {.c = {-10, -5}, .r = 35.70971452895846}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {0, 11}, .p2 = {-17, 7}, .p3 = {-6, -7}}},
    //     {.type = CIRCLE, .circ = {.c = {2, -4}, .r = 6.937151209125721}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {-9, 11}, .p2 = {10, 14}, .p3 = {12, 4}}},
    //     {.type = RECTANGLE, .rect = {.p = {10, 4}, .width = 28, .height = 48}},
    //     {.type = RECTANGLE, .rect = {.p = {-9, -5}, .width = 16, .height = 40}},
    //     {.type = RECTANGLE, .rect = {.p = {5, 4}, .width = 16, .height = 27}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {10, 9}, .p2 = {-12, 2}, .p3 = {10, 10}}},
    //     {.type = CIRCLE, .circ = {.c = {-2, 7}, .r = 12.178815308822843}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {19, -19}, .p2 = {15, 3}, .p3 = {15, -9}}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {-16, -8}, .p2 = {3, -5}, .p3 = {-17, 19}}},
    //     {.type = RECTANGLE, .rect = {.p = {1, -8}, .width = 23, .height = 31}},
    //     {.type = CIRCLE, .circ = {.c = {8, 10}, .r = 6.763799103471259}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {-10, 11}, .p2 = {6, -3}, .p3 = {12, -6}}},
    //     {.type = RECTANGLE, .rect = {.p = {-6, -2}, .width = 27, .height = 25}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {-18, -13}, .p2 = {-12, -1}, .p3 = {-5, 10}}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {8, -5}, .p2 = {10, 3}, .p3 = {1, -12}}},
    //     {.type = CIRCLE, .circ = {.c = {-10, 0}, .r = 30.76253989637577}},
    //     {.type = RECTANGLE, .rect = {.p = {7, 3}, .width = 33, .height = 44}},
    //     {.type = RECTANGLE, .rect = {.p = {1, -2}, .width = 44, .height = 25}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {18, -13}, .p2 = {18, 2}, .p3 = {5, 13}}},
    //     {.type = CIRCLE, .circ = {.c = {6, -5}, .r = 3.3530867565021785}},
    //     {.type = CIRCLE, .circ = {.c = {-4, -4}, .r = 12.13230948716895}},
    //     {.type = RECTANGLE, .rect = {.p = {7, 9}, .width = 14, .height = 44}},
    //     {.type = RECTANGLE, .rect = {.p = {-6, -2}, .width = 26, .height = 50}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {15, -6}, .p2 = {-19, 11}, .p3 = {-2, -18}}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {-4, -15}, .p2 = {-20, 20}, .p3 = {-11, 3}}},
    //     {.type = CIRCLE, .circ = {.c = {8, -5}, .r = 10.75392195554429}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {20, 15}, .p2 = {10, 15}, .p3 = {12, -14}}},
    //     {.type = RECTANGLE, .rect = {.p = {10, -1}, .width = 15, .height = 41}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {-19, -8}, .p2 = {9, -5}, .p3 = {-3, -2}}},
    //     {.type = CIRCLE, .circ = {.c = {-5, 4}, .r = 4.874798980750415}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {-16, -16}, .p2 = {-5, -20}, .p3 = {6, -15}}},
    //     {.type = CIRCLE, .circ = {.c = {-3, 8}, .r = 29.11167869593732}}
    // };
    // struct figure_t *ptr[34];
    //
    // for (int i = 0; i < 34; ++i)
    //     ptr[i] = &figures[i];
    //
    // printf("------------TABLICA FIGUR DO POSORTOWANIA-----------\n");
    //
    // for (int i = 0; i < 34; ++i) {
    //     printf("%.4f ", area_figure(figures + i));
    //     display_figure(figures + i);
    // }
    //
    // printf("------------TABLICA FIGUR PO SORTOWANIU-----------\n");
    //
    // int res = sort_by_area(ptr, 34);
    //
    // struct figure_t expected_figures[] = {
    //     {.type = CIRCLE, .circ = {.c = {-10, -5}, .r = 35.70971452895846}},
    //     {.type = CIRCLE, .circ = {.c = {-10, 0}, .r = 30.76253989637577}},
    //     {.type = CIRCLE, .circ = {.c = {-3, 8}, .r = 29.11167869593732}},
    //     {.type = RECTANGLE, .rect = {.p = {7, 3}, .width = 33, .height = 44}},
    //     {.type = RECTANGLE, .rect = {.p = {10, 4}, .width = 28, .height = 48}},
    //     {.type = RECTANGLE, .rect = {.p = {-6, -2}, .width = 26, .height = 50}},
    //     {.type = RECTANGLE, .rect = {.p = {1, -2}, .width = 44, .height = 25}},
    //     {.type = RECTANGLE, .rect = {.p = {1, -8}, .width = 23, .height = 31}},
    //     {.type = RECTANGLE, .rect = {.p = {-6, -2}, .width = 27, .height = 25}},
    //     {.type = RECTANGLE, .rect = {.p = {-9, -5}, .width = 16, .height = 40}},
    //     {.type = RECTANGLE, .rect = {.p = {7, 9}, .width = 14, .height = 44}},
    //     {.type = RECTANGLE, .rect = {.p = {10, -1}, .width = 15, .height = 41}},
    //     {.type = CIRCLE, .circ = {.c = {-2, 7}, .r = 12.178815308822843}},
    //     {.type = CIRCLE, .circ = {.c = {-4, -4}, .r = 12.13230948716895}},
    //     {.type = RECTANGLE, .rect = {.p = {5, 4}, .width = 16, .height = 27}},
    //     {.type = CIRCLE, .circ = {.c = {8, -5}, .r = 10.75392195554429}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {15, -6}, .p2 = {-19, 11}, .p3 = {-2, -18}}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {-16, -8}, .p2 = {3, -5}, .p3 = {-17, 19}}},
    //     {.type = CIRCLE, .circ = {.c = {2, -4}, .r = 6.937151209125721}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {20, 15}, .p2 = {10, 15}, .p3 = {12, -14}}},
    //     {.type = CIRCLE, .circ = {.c = {8, 10}, .r = 6.763799103471259}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {0, 11}, .p2 = {-17, 7}, .p3 = {-6, -7}}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {-9, 11}, .p2 = {10, 14}, .p3 = {12, 4}}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {18, -13}, .p2 = {18, 2}, .p3 = {5, 13}}},
    //     {.type = CIRCLE, .circ = {.c = {-5, 4}, .r = 4.874798980750415}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {-19, -8}, .p2 = {9, -5}, .p3 = {-3, -2}}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {-16, -16}, .p2 = {-5, -20}, .p3 = {6, -15}}},
    //     {.type = CIRCLE, .circ = {.c = {6, -5}, .r = 3.3530867565021785}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {19, -19}, .p2 = {15, 3}, .p3 = {15, -9}}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {-4, -15}, .p2 = {-20, 20}, .p3 = {-11, 3}}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {8, -5}, .p2 = {10, 3}, .p3 = {1, -12}}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {-10, 11}, .p2 = {6, -3}, .p3 = {12, -6}}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {10, 9}, .p2 = {-12, 2}, .p3 = {10, 10}}},
    //     {.type = TRIANGLE, .triangle = {.p1 = {-18, -13}, .p2 = {-12, -1}, .p3 = {-5, 10}}}
    // };
    //
    // for (int i = 0; i < 34; ++i) {
    //     printf("%d %.4f ", i, area_figure(ptr[i]));
    //     display_figure(ptr[i]);
    // }
    //
    // printf("------------OCZEKIWANA TABLICA FIGUR-----------\n");
    //
    // for (int i = 0; i < 34; ++i) {
    //     printf("%d %.4f ", i, area_figure(expected_figures + i));
    //     display_figure(expected_figures + i);
    // }
    //
    // printf("------------\n");
    //

    return 0;
}
