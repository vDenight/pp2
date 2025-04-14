#include <stdio.h>
#include "figure.h"

int main(void) {
    struct rectangle_t r;
    r.p.x = 0;
    r.p.y = 0;
    r.height = 10;
    r.width = 10;

    struct figure_t f;
    f.type = RECTANGLE;
    f.rect = r;

    printf("%f\n", area_figure(&f));
    display_figure(&f);

    return 0;
}