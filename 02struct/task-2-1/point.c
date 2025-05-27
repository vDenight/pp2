//
// Created by mcihal on 27.05.25.
//

#include <stddef.h>
#include "point.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point_t* set(struct point_t* p, int x, int y) {
    if (!p) return NULL;

    p->x = x; p->y = y;

    return p;
}

void show(const struct point_t* p) {
    if (!p) return;
    printf("x = %d; y = %d\n", p->x, p->y);
}

struct point_t* read(struct point_t* p) {
    if (!p) return NULL;

    printf("Podaj współrzędną x: ");
    if (!scanf("%d", &p->x)) return NULL;
    printf("Podaj współrzędną y: ");
    if (!scanf("%d", &p->y)) return NULL;
    return p;
}

float distance(const struct point_t* p1, const struct point_t* p2, int *err_code) {
    if (!p1 || !p2) {
        if (err_code) *err_code = 1;
        return -1;
    }

    float distance_x = abs(p2->x - p1->x);
    float distance_y = abs(p2->y - p1->y);

    if (err_code) *err_code = 0;
    return sqrtf(distance_x * distance_x + distance_y * distance_y);
}
