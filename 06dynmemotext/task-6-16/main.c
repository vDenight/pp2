#include <stdio.h>
#include "crosswords.h"

int main(void) {
    char** words;
    create_leading_word_cross("JACEK", "PLACE", &words);
    display(words);
    return 0;
}