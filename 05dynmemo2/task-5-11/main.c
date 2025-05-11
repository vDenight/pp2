#include <stdio.h>
#include <string.h>

#include "statistics_utils.h"

int get_format(char* filename, enum save_format_t* format);

int main(void) {

    return 0;
}

// int get_format(char* filename, enum save_format_t* format) {
//     char* dot_pointer = NULL;
//
//     dot_pointer = strchr(filename, '.');
//
//     if (dot_pointer == NULL) {
//         return -1;
//     }
//     if (dot_pointer - filename > 35) {
//         return -2;
//     }
//
//     if (strcmp(dot_pointer + 1, "txt") == 0) {
//         *format = fmt_text;
//     } else if (strcmp(dot_pointer + 1, "bin") == 0) {
//         *format = fmt_binary;
//     } else {
//         return -3;
//     }
//
//     return 0;
// }