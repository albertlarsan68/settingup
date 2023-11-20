#pragma once

typedef struct board {
    int width;
    int height;
    char *cells;
} *board_t;

board_t board_load_from_file(const char *filename);
board_t board_generate(int size, const char *pattern);
void board_destroy(board_t board);
void board_display(const board_t board);
void board_resolve(board_t board);
