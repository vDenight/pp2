//
// Created by mcihal on 01.06.25.
//

#include <stdio.h>
#include "easter.h"

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

void (**easter(int size, void(*)(void), void(*)(void), void(*)(void)))(void) {

    if (size < 1) return NULL;

    void (**funcs)(void) = malloc(size * sizeof(void (*)(void)));
    if (funcs == NULL) return NULL;

    srand(time(NULL));

    int rand_num = 0;
    for(int i = 0; i < size; i++) {
        rand_num = rand() % 3;
        switch (rand_num) {
            case 0:
                *(funcs + i) = print_chicken;
                break;
            case 1:
                *(funcs + i) = print_egg;
                break;
            case 2:
                *(funcs + i) = print_rabbit;
                break;
        }
    }

    return funcs;
}
