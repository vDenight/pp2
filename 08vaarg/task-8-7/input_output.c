//
// Created by mrybczynski on 6/2/2025.
//

#include "input_output.h"

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>

int my_printf(const char* text, ...) {
    int res = 0;

    va_list args;
    va_start(args, text);

    while (*text != '\0') {
        switch (*text) {
            case '%':
                text++;
                switch (*text) {
                    case 'd':
                        int i = va_arg(args, int);
                        res += print_int(i);
                        break;
                    case 's':
                        char* s = va_arg(args, char*);
                        res += print_string(s);
                        break;
                    case 'f':
                        double f = va_arg(args, double);
                        res += print_float(f);
                        break;
                    case 'p':
                        struct point_t p = va_arg(args, struct point_t);
                        res += print_point(p);
                        break;
                    default:
                        putchar('%');
                        putchar(*text);
                        res += 2;
                }
                break;
            default:
                putchar(*text);
                res++;
        }

        text++;
    }
    va_end(args);
    return res;
}

int my_scanf(const char* text, ...) {
    int res = 0;

    va_list args;
    va_start(args, text);

    while (*text != '\0') {
        switch (*text) {
            case '%':
                text++;
                switch (*text) {
                    case 'd':
                        int* i = va_arg(args, int*);
                        res += scan_int(i);
                        break;
                    case 'f':
                        double* f = va_arg(args, double*);
                        res += scan_float(f);
                        break;
                    case 'p':
                        struct point_t* p = va_arg(args, struct point_t*);
                        res += scan_point(p);
                        break;
                    default: break;
                }
                break;
            default: break;
        }

        text++;
    }
    va_end(args);
    return res;
}

int print_string(const char* string) {
    int res = 0;
    while (*string != '\0') {
        putchar(*string);
        string++;
        res++;
    }
    return res;
}

int print_int(int number) {
    int res = 0;

    if (number < 0) {
        putchar('-');
        res++;
    }

    number = abs(number);
    _Bool started = 0;
    int current_digit = 0;
    for (int i = 1000000000; i > 0; i = i / 10) {
        current_digit = number / i;
        if (!started && current_digit == 0) {
            continue;
        }
        started = 1;
        putchar(number / i + '0');
        res++;
        number -= (number / i) * i;
    }
    return res;
}

int print_float(double f) {
    int res = 0;

    if (f < 0) {
        putchar('-');
        res++;
    }

    int number = abs((int)f); // number is an interger part of the float
    _Bool started = 0;
    int current_digit = 0;
    for (int i = 1000000000; i > 0; i = i / 10) {
        current_digit = number / i;
        if (!started && current_digit == 0) {
            continue;
        }
        started = 1;
        putchar(current_digit + '0');
        res++;
        number -= current_digit * i;
    }

    putchar('.'); res++; // the dot

    int fraction_part = (int) ((fabs(f) - abs((int)f)) * 100000);
    for (int i = 10000; i > 0; i = i / 10) {
        current_digit = fraction_part / i;
        putchar(current_digit + '0');
        res++;
        fraction_part -= current_digit * i;
    }

    return res;
}

int print_point(struct point_t point) {
    int res = 0;

    putchar('('); res++;
    res += print_int(point.x);
    putchar(' '); res ++;
    res += print_int(point.y);
    putchar(')'); res ++;

    return res;
}

int scan_int(int* number) {
    *number = 0;
    int c;
    _Bool negative = 0;
    _Bool started = 0;
    while (1) {
        c = getchar();
        if ((c == ' ' || c == '\n') && !started) continue; // skip leading spaces
        if (c == '-' && !started) { // handle minus
            if (negative) break;
            negative = 1;
            continue;
        }
        if (!isdigit(c)) break;
        started = 1;
        *number = (*number * 10) + (c - '0');
    }

    *number = negative ? -*number : *number;
    return started ? 1 : 0;
}

int scan_float(double* f) {
    *f = 0.0;
    int c;
    _Bool started = 0;
    _Bool after_dot = 0;
    double current_exp = 0.1;
    _Bool negative = 0;

    while (1) {
        c = getchar();

        if ((c == ' ' || c == '\n') && !started) continue; // skip leading spaces
        if (c == '-' && !started) { // handle minus
            if (negative) break;
            negative = 1;
            continue;
        }

        if (c == '.' && !started) break; // handle dot
        if (c == '.' && after_dot) break;
        if (c == '.') {
            after_dot = 1;
            continue;
        }
        if (!isdigit(c)) break;

        if (after_dot) {
            *f += (c - '0') * current_exp;
            current_exp *= 0.1;
            if (current_exp == 0.000001) break;
            continue;
        }

        started = 1;
        *f = (*f * 10) + (c - '0');
    }

    return started ? 1 : 0;
}

int scan_point(struct point_t* point) {
    int x = 0, y = 0;
    int c;
    while ((c = getchar()) == ' ') {}
    if (c != '(') return 0;
    if (!scan_int(&x)) return 0;
    point->x = x;
    if (!scan_int(&y)) return 1;
    point->y = y;

    return 2;
}



