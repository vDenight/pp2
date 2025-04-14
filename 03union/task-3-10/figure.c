#include "figure.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float area_triangle(const struct triangle_t *t) {
    return fabsf((float)(t->p1.x * (t->p2.y - t->p3.y) +
                         t->p2.x * (t->p3.y - t->p1.y) +
                         t->p3.x * (t->p1.y - t->p2.y))) * 0.5f;
}

float area_rectangle(const struct rectangle_t *r) {
    return (float) r->width * (float) r->height;
}

float area_circle(const struct circle_t *c) {
    return M_PI * c->r * c->r;
}

float area_figure(const struct figure_t *f) {
    switch (f->type) {
        case TRIANGLE:
            return area_triangle(&f->triangle);
        case RECTANGLE:
            return area_rectangle(&f->rect);
        case CIRCLE:
            return area_circle(&f->circ);
    }
    return 0;
}

void display_rectangle(const struct rectangle_t *rect) {
    printf("Rectangle (%d, %d), width = %d, height = %d",
        rect->p.x, rect->p.y, rect->width, rect->height);
}

void display_triangle(const struct triangle_t *t) {
    printf("Triangle p1(%d, %d), p2(%d, %d), p3(%d, %d)",
        t->p1.x, t->p1.y, t->p2.x, t->p2.y, t->p3.x, t->p3.y);
}

void display_circle(const struct circle_t *circ) {
    printf("Circle (%d, %d), radius = %f",
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
    return (int) (area_figure((const struct figure_t*)f) - area_figure((const struct figure_t*)g));
}

int sort_by_area(struct figure_t **figures, int size) {
    struct figure_t* current_figure = *figures;
    for (int i = 0; i < size; i++) {
        if (current_figure->type != TRIANGLE && current_figure->type != RECTANGLE && current_figure->type != CIRCLE) {
            return 1;
        }
    }

    qsort(figures, size, sizeof(struct figure_t*), compare_figures_by_area);

    return 0;
}