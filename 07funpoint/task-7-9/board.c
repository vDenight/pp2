//
// Created by mcihal on 01.06.25.
//

#include <stdlib.h>
#include "board.h"

#include <stdio.h>
#include <string.h>

int create_board(struct board_t **board, int width,int height) {
    if (board == NULL || width <= 0 || height <= 0) return CREATE_WRONG_INPUT;

    struct board_t* new_board = malloc(sizeof(struct board_t));
    if (!new_board) return CREATE_ALLOC_FAIL;

    new_board->board = calloc(height, sizeof(char*));
    if (!new_board->board) {
        free(new_board);
        return CREATE_ALLOC_FAIL;
    }

    for (int i = 0; i < height; i++) {
        *(new_board->board + i) = calloc(width + 1, sizeof(char));
        if (!(*(new_board->board + i))) {
            for (int j = 0; j < i; j++) {
                free(*(new_board->board + j));
            }
            free(new_board->board);
            free(new_board);
            return CREATE_ALLOC_FAIL;
        }
        memset(*(new_board->board + i), '.', width);
    }

    new_board->width = width;
    new_board->height = height;
    new_board->is_init = 0;

    new_board->move_player_up = move_player_up;
    new_board->move_player_down = move_player_down;
    new_board->move_player_left = move_player_left;
    new_board->move_player_right = move_player_right;

    *board = new_board;
    return CREATE_OK;
}



void display_board(const struct board_t *board) {
    if (board == NULL || board->board == NULL || board->width <= 0 || board->height <= 0) return;

    for (int i = 0; i < board->height; i++) {
        printf("%s\n", *(board->board + i));
    }
}

void free_board(struct board_t *board) {
    if (board == NULL || board->board == NULL || board->width <= 0 || board->height <= 0) return;
    for (int i = 0; i < board->height; i++) {
        if (*(board->board + i)) {
            free(*(board->board + i));
            *(board->board + i) = NULL;
        }
    }
    free(board->board);
    free(board);
}

int set_player(struct board_t *board, int x, int y) {
    if (board == NULL || board->board == NULL || board->width <= 0 || board->height <= 0 ||
        x < 0 || y < 0 || x >= board->width || y>= board->height || board->is_init == 1) return 1;

    board->player.x = x;
    board->player.y = y;

    *(*(board->board + y) + x) = '@';

    board->is_init = 1;

    return 0;
}

struct board_t* move_player_up(struct board_t* b) {
    if (b == NULL || b->board == NULL || b->width <= 0 || b->height <= 0 || b->is_init == 0 ||
        b->player.x < 0 || b->player.x >= b->width || b->player.y < 0 || b->player.y >= b->height) return NULL;
    int new_y = b->player.y - 1;

    if (new_y == -1) new_y= b->height - 1;

    *(*(b->board + b->player.y) + b->player.x) = '.';

    b->player.y = new_y;
    *(*(b->board + b->player.y) + b->player.x) = '@';
    return b;
}

struct board_t* move_player_down(struct board_t* b) {
    if (b == NULL || b->board == NULL || b->width <= 0 || b->height <= 0 || b->is_init == 0 ||
        b->player.x < 0 || b->player.x >= b->width || b->player.y < 0 || b->player.y >= b->height) return NULL;
    int new_y = b->player.y + 1;

    if (new_y == b->height) new_y = 0;

    *(*(b->board + b->player.y) + b->player.x) = '.';

    b->player.y = new_y;
    *(*(b->board + b->player.y) + b->player.x) = '@';
    return b;
}

struct board_t* move_player_left(struct board_t* b) {
    if (b == NULL || b->board == NULL || b->width <= 0 || b->height <= 0 || b->is_init == 0 ||
        b->player.x < 0 || b->player.x >= b->width || b->player.y < 0 || b->player.y >= b->height) return NULL;
    int new_x = b->player.x - 1;

    if (new_x == -1) new_x = b->width - 1;

    *(*(b->board + b->player.y) + b->player.x) = '.';

    b->player.x = new_x;
    *(*(b->board + b->player.y) + b->player.x) = '@';
    return b;
}

struct board_t* move_player_right(struct board_t* b) {
    if (b == NULL || b->board == NULL || b->width <= 0 || b->height <= 0 || b->is_init == 0 ||
        b->player.x < 0 || b->player.x >= b->width || b->player.y < 0 || b->player.y >= b->height) return NULL;
    int new_x = b->player.x + 1;

    if (new_x == b->width) new_x = 0;

    *(*(b->board + b->player.y) + b->player.x) = '.';

    b->player.x = new_x;
    *(*(b->board + b->player.y) + b->player.x) = '@';
    return b;
}