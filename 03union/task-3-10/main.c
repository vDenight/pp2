#include <stdbool.h>
#include <stdio.h>

#include "figure.h"

int main(void) {

    int num = 10;

    struct figure_t figures[50]; // instead of allocating we alloc statically for 50 figs
    struct figure_t *figure_addresses[50] = {0}; // now we alloc for the addresses as well

    struct figure_t* figure = figures; // this pointer will be used to move through the figures array
    struct figure_t** figure_address; // this pointer will be used to move through the figures addresses

    int count = 0;

    for (; count < 50; count++) {

        printf("Enter figure's type: ");
        int num_scanf_val = scanf("%d", &num);

        if (num_scanf_val != 1) {
            printf("Incorrect input");
            return 1;
        }

        if (num == 0) {
            break;
        }

        switch (num) {
            case TRIANGLE:
                printf("Enter vertices' coordinates of a triangle (x1 y1 x2 y2 x3 y3): ");

                int x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0;
                int scanf_val = 0;
                scanf_val = scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
                if (scanf_val != 6) {
                    printf("Incorrect input");
                    return 1;
                }

                struct triangle_t triangle;

                triangle.p1.x = x1;
                triangle.p1.y = y1;
                triangle.p2.x = x2;
                triangle.p2.y = y2;
                triangle.p3.x = x3;
                triangle.p3.y = y3;

                figure->type = TRIANGLE;
                figure->triangle = triangle;

                figure++;
                break;

            case RECTANGLE:
                printf("Enter coordinates of a rectangle along with its dimensions (x y width height): ");

                int x = 0, y = 0, width = 0, height = 0;
                scanf_val = scanf("%d %d %d %d", &x, &y, &width, &height);
                if (scanf_val != 4) {
                    printf("Incorrect input");
                    return 1;
                }

                struct rectangle_t rectangle;

                rectangle.p.x = x;
                rectangle.p.y = y;
                rectangle.width = width;
                rectangle.height = height;

                figure->type = RECTANGLE;
                figure->rect = rectangle;

                figure++;
                break;

            case CIRCLE:
                printf("Enter coordinates and radius of a circle: ");

                int xc = 0, yc = 0;
                float radius = 0;
                scanf_val = scanf("%d %d %f", &xc, &yc, &radius);
                if (scanf_val != 3) {
                    printf("Incorrect input");
                    return 1;
                }

                struct circle_t circle;

                circle.c.x = xc;
                circle.c.y = yc;
                circle.r = radius;

                figure->type = CIRCLE;
                figure->circ = circle;

                figure++;
                break;
            default:
                printf("Incorrect input data");
                return 2;
        }
    }

    // validate all figures
    figure = figures;

    for (int i = 0; i < count; i++) {
        if (validate_figure(figure) == 0) {
            printf("Incorrect input data");
            return 2;
        }
        figure++;
    }

    figure = figures;
    figure_address = figure_addresses;

    for (int i = 0; i < count; i++) {
        *figure_address = figure;
        figure++;
        figure_address++;
    }

    sort_by_area(figure_addresses, count);

    figure_address = figure_addresses;

    for (int i = 0; i < count; i++) {
        display_figure(*figure_address);
        figure_address++;
    }

    return 0;
}
