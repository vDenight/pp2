#include <stdio.h>
#include <string.h>

#include "bit_inv.h"

int main(void) {
    char buffer[101] = {0};

    printf("Podaj tekst: ");
    fgets(buffer, 101, stdin);
    *(buffer + strlen(buffer) - 1) = '\0';

    show(buffer, strlen(buffer) + 1);
    printf("\n");

    inverse_bits(buffer, 0, strlen(buffer) + 1);
    show(buffer, strlen(buffer));
    printf("\n");

    return 0;
}