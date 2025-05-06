//
// Created by mrybczynski on 5/6/2025.
//

#ifndef MAZE_H
#define MAZE_H

int load_maze(const char *filename, char ***labirynth);
int solve_maze(char **maze, int x, int y);
void free_maze(char **maze);

#endif //MAZE_H
