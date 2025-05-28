//
// Created by mrybczynski on 5/28/2025.
//

#include <stdio.h>
#include <string.h>
#include "read_line.h"

void read_line(char* buffer, int max_len) {
    int c;
    int size = 0;
    memset(buffer, 0, max_len);

    while ((c = getchar()) != '\n') {
        if (size < max_len) {
            *(buffer + size) = (char) c;
            size++;
        }
    }
}
