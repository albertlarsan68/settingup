/*
** EPITECH PROJECT, 2023
** settingup
** File description:
** Main file
*/

#include "board.h"
#include "my_memory.h"
#include <my.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    board_t board = NULL;
    int size = 0;

    if (argc == 2) {
        board = board_load_from_file(argv[1]);
    }
    if (argc == 3) {
        size = my_atoi(argv[1]);
        if (size > 0 && my_strlen(argv[2]) > 0)
            board = board_generate(size, argv[2]);
    }
    if (board == NULL)
        return 84;
    board_resolve(board);
    board_display(board);
    board_destroy(board);
    return 0;
}
