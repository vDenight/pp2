#include "figure.h"

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float area_triangle(const struct triangle_t *t) {

    if (t == NULL)
        return -1;

    // check overflow on each part of the logic

    double result_part_1 = t->p2.y;
    double result_part_2 = t->p3.y;
    double result_part_3 = t->p1.y;

    if (result_part_1 > FLT_MAX + (double) t->p3.y || result_part_1 < (-FLT_MAX) + (double) t->p3.y ||
        result_part_2 > FLT_MAX + (double) t->p2.y || result_part_2 < (-FLT_MAX) + (double) t->p2.y ||
        result_part_3 > FLT_MAX + (double) t->p1.y || result_part_3 < (-FLT_MAX) + (double) t->p1.y) {
        return -1;
    }

    result_part_1 -= t->p3.y;
    result_part_2 -= t->p1.y;
    result_part_3 -= t->p2.y;

    if (fabs(result_part_1) > fabs(FLT_MAX / (double) t->p1.x) ||
        fabs(result_part_2) > fabs(FLT_MAX / (double) t->p2.x) ||
        fabs(result_part_3) > fabs(FLT_MAX / (double) t->p3.x)) {
        return -1;
    }

    result_part_1 *= t->p1.x;
    result_part_2 *= t->p2.x;
    result_part_3 *= t->p3.x;

    if (result_part_1 > FLT_MAX - result_part_2 || result_part_1 < (-FLT_MAX) - result_part_2) {
        return -1;
    }

    result_part_1 += result_part_2;

    if (result_part_2 > FLT_MAX - result_part_3 || result_part_2 < (-FLT_MAX) - result_part_3) {
        return -1;
    }

    result_part_1 += result_part_3;

    return result_part_1 == 0 ? -1 : (float) fabs(result_part_1) * 0.5f;
}

float area_rectangle(const struct rectangle_t *r) {

    if (r == NULL)
        return -1;

    if ((double) r->width > FLT_MAX / (double) r->height + 1)
        return -1;

    if (r->height <= 0 || r->width <= 0)
        return -1;

    double result = (double) r->width * (double) r->height;

    if (result > FLT_MAX)
        return -1;

    return (float) result;
}

float area_circle(const struct circle_t *c) {

    if (c == NULL)
        return -1;

    if (c->r <= 0)
        return -1;

    double result = M_PI * c->r * c->r;

    if (result > FLT_MAX)
        return -1;

    return (float) result;
}

float area_figure(const struct figure_t *f) {

    if (f == NULL)
        return -1;

    switch (f->type) {
        case TRIANGLE:
            return area_triangle(&f->triangle);
        case RECTANGLE:
            return area_rectangle(&f->rect);
        case CIRCLE:
            return area_circle(&f->circ);
        default:
            return -1;
    }
}

void display_rectangle(const struct rectangle_t *rect) {
    printf("Rectangle (%d, %d), width = %d, height = %d\n",
        rect->p.x, rect->p.y, rect->width, rect->height);
}

void display_triangle(const struct triangle_t *t) {
    printf("Triangle p1(%d, %d), p2(%d, %d), p3(%d, %d)\n",
        t->p1.x, t->p1.y, t->p2.x, t->p2.y, t->p3.x, t->p3.y);
}

void display_circle(const struct circle_t *circ) {
    printf("Circle (%d, %d), radius = %f\n",
        circ->c.x, circ->c.y, circ->r);
}

void display_figure(struct figure_t *f) {
    switch (f->type) {
        case TRIANGLE:
            display_triangle(&f->triangle);
            break;
        case RECTANGLE:
            display_rectangle(&f->rect);
            break;
        case CIRCLE:
            display_circle(&f->circ);
            break;
    }
}

int compare_figures_by_area(const void* f, const void* g) {

    struct figure_t **f1 = (struct figure_t **) f;
    struct figure_t **f2 = (struct figure_t **) g;

    return (int) area_figure(*f2) - (int) area_figure(*f1);
}

int sort_by_area(struct figure_t **figures, int size) {
    if (figures == NULL || size < 0)
        return 1;

    struct figure_t* current_figure = *figures;

    for (int i = 0; i < size; i++) {
        if (area_figure(current_figure) <= 0)
            return 1;
        current_figure++;
    }

    qsort(figures, size, sizeof(struct figure_t*), compare_figures_by_area);

    return 0;
}