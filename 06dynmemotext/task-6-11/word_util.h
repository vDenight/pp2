//
// Created by mcihal on 25.05.25.
//

#ifndef WORD_UTIL_H
#define WORD_UTIL_H

char **split_words(const char *text);
int sort_words(char **words);
void destroy(char **words);
void display(char **words);

#endif //WORD_UTIL_H
