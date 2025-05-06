//
// Created by mrybczynski on 5/6/2025.
//

#ifndef MAZE_H
#define MAZE_H
#include <stdio.h>

int load_maze(const char *filename, char ***labirynth);
int solve_maze(char **maze, int x, int y);
void free_maze(char **maze);
void display_maze(char **maze);

/*
1 - w przypadku przekazania błędnych danych,
2 - jeżeli nie uda się otworzyć pliku,
3 jeżeli dane w pliku są uszkodzone (poprawny plik będzie przechowywał labirynt w formacie tekstowym, każdy wiersze będzie tej samej długości),
4 w przypadku niepowodzenia alokacji pamięci,
0 w przypadku sukcesu.
*/
enum load_error_code {
    LOAD_OK = 0,
    LOAD_INPUT_ERROR = 1,
    LOAD_FILE_OPEN_ERROR = 2,
    LOAD_FILE_CORRUPTED_ERROR = 3,
    LOAD_ALLOC_ERROR = 4,
};

enum solve_error_code {
    SOLVE_OK = 1,
    SOLVE_FAILED = 0,
    SOLVE_ERROR = -1
};

#endif //MAZE_H
