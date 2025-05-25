#include <stdio.h>
#include "word_util.h"

int main(void) {
    char input[1000] = "VAMOS POLSKA - Krzysztof J. Stanowski";
    char** split_w = split_words(input);
    display(split_w);
    return 0;
}