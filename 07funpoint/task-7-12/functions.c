//
// Created by mcihal on 01.06.25.
//

#include <stdio.h>
#include "functions.h"

#include <stdlib.h>
#include <time.h>

void print_chicken() {
    printf(" MM\n"
           "<' \\___/|\n"
           "  \\_  _/\n"
           "    ][\n");
}

void print_egg() {
    printf("  .~~~.\n"
           " /     \\\n"
           "(/\\/\\/\\/\\)\n"
           " \\     /\n"
           "  `~~~`\n");
}

void print_rabbit() {
    printf(" \\\\   //\n"
           "  )\\-/(\n"
           "  /o o\\\n"
           " ( =T= )\n"
           " /'---'\\\n");
}

void (**easter(int size, void(*f1)(void), void(*f2)(void), void(*f3)(void)))(void) {

    if (size < 1) return NULL;

    void (**funcs)(void) = malloc(size * sizeof(void (*)(void)));
    if (funcs == NULL) return NULL;

    srand(time(NULL)); // dont care

    int rand_num = 0;
    for(int i = 0; i < size; i++) {
        rand_num = rand() % 3;
        switch (rand_num) {
            case 0:
                *(funcs + i) = f1;
                break;
            case 1:
                *(funcs + i) = f2;
                break;
            case 2:
                *(funcs + i) = f3;
                break;
        }
    }

    return funcs;
}
