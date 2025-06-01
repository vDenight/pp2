//
// Created by mcihal on 01.06.25.
//

#ifndef BOARD_H
#define BOARD_H

struct point_t {
    int x;
    int y;
};

struct board_t {
    struct point_t player;

    char **board;

    int width;
    int height;

    unsigned char is_init:1;

    struct board_t* (*move_player_up)(struct board_t*);
    struct board_t* (*move_player_down)(struct board_t*);
    struct board_t* (*move_player_left)(struct board_t*);
    struct board_t* (*move_player_right)(struct board_t*);
};

int create_board(struct board_t **board, int width,int height);
void display_board(const struct board_t *board);
void free_board(struct board_t *board);
int set_player(struct board_t *board, int x, int y);

struct board_t* move_player_up(struct board_t*);
struct board_t* move_player_down(struct board_t*);
struct board_t* move_player_left(struct board_t*);
struct board_t* move_player_right(struct board_t*);

enum create_code {
    CREATE_OK = 0,
    CREATE_WRONG_INPUT = 1,
    CREATE_ALLOC_FAIL = 2
};

#endif //BOARD_H
