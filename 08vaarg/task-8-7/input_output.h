//
// Created by mrybczynski on 6/2/2025.
//

#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

struct point_t {
    int x;
    int y;
};

int my_printf(char* format, ...);
int my_scanf(char* format, ...);

//helper
int print_string(const char* string);
int print_int(int number);
int print_float(double f);
int print_point(struct point_t point);

int scan_int(int* number);
int scan_float(double* f);
int scan_point(struct point_t* point);


#endif //INPUT_OUTPUT_H
