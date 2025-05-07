//
// Created by mrybczynski on 5/7/2025.
//

#ifndef CROSSWORDS_H
#define CROSSWORDS_H

int create_leading_word_cross(const char *first, const char *second, char ***result);
int create_double_leading_word_cross(
    const char *first, const char *second, const char *third, const char *fourth,
    char ***result, char ***first_cross, char ***second_cross);

void destroy(char **words);

#endif //CROSSWORDS_H
