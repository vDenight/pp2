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
void display(char **words);


/*
-1 - w przypadku przekazania błędnych danych,
-2 - w przypadku, kiedy niemożliwe będzie utworzenie krzyża z podanych słów
-3 - w przypadku niepowodzenia alokacji pamięci,
*/
enum create_cross_result {
    CREATE_WRONG_INPUT = -1,
    CREATE_CANT_CROSS = -2,
    CREATE_ALLOC_FAIL = -3
};
/*
1 - w przypadku przekazania błędnych danych,
2 - w przypadku, kiedy niemożliwe będzie utworzenie krzyża z podanych słów
3 - w przypadku niepowodzenia alokacji pamięci,
0 - w przypadku sukcesu.
*/
enum double_create_cross_result {
    DCREATE_WRONG_INPUT = 1,
    DCREATE_CANT_CROSS = 2,
    DCREATE_ALLOC_FAIL = 3,
    DCREATE_OK = 0
};

#endif //CROSSWORDS_H
