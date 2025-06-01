#include <ctype.h>
#include <stdio.h>
#include "board.h"

enum main_code {
    OK = 0,
    INCORRECT_INPUT = 1,
    INCORRECT_INPUT_DATA = 2,
    ALLOC_FAIL = 8
};

int main(void) {
    struct board_t* my_board;

    printf("Enter width and height of the board: ");
    int width, height;
    if (scanf("%d %d", &width, &height) != 2) {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }

    if (width < 1 || height < 1) {
        printf("Incorrect input data");
        return INCORRECT_INPUT_DATA;
    }

    if (create_board(&my_board, width, height) == CREATE_ALLOC_FAIL) {
        printf("Failed to allocate memory");
        return ALLOC_FAIL;
    }

    printf("Enter player's initial coordinates (x, y): ");
    int x, y;
    if (scanf("%d %d", &x, &y) != 2) {
        printf("Incorrect input");
        free_board(my_board);
        return INCORRECT_INPUT;
    }

    if (x < 1 || y < 1 || x > width || y > height) {
        printf("Incorrect input data");
        free_board(my_board);
        return INCORRECT_INPUT_DATA;
    }
    getchar(); // get the newline xd

    set_player(my_board, x, y);
    display_board(my_board);


    _Bool game_running = 1;
    _Bool to_display;
    char action;

    while (game_running) {
        to_display = 1;
        printf("Choose your action: ");
        action = getchar();
        if (getchar() != '\n') {
            while (getchar() != '\n') {}
            action = 'r'; // just to drop into default case
        }

        switch (action) {
            case 'w':
                my_board->move_player_up(my_board);
                break;
            case 's':
                my_board->move_player_down(my_board);
                break;
            case 'a':
                my_board->move_player_left(my_board);
                break;
            case 'd':
                my_board->move_player_right(my_board);
                break;
            case 'q':
                to_display = 0;
                game_running = 0;
                break;
            default:
                to_display = 0;
                printf("Incorrect choice\n");
                break;
        }
        if (to_display) {
            display_board(my_board);
        }
    }

    free_board(my_board);

    return OK;
}