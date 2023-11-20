#include "board.h"
#include "my.h"
#include <my_memory.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void board_destroy(board_t board)
{
    my_free(board->cells);
    my_free(board);
}

static int does_square_fit(board_t board, int square_size, int x, int y)
{
    if (x + square_size > board->width || y + square_size > board->height)
        return 0;
    for (int i = 0; i < square_size && x + i < board->width; i++)
        for (int j = 0; j < square_size && y + j < board->height; j++)
            if (board->cells[(y + j) * board->width + x + i] != '.')
                return 0;
    return 1;
}

static int does_square_fit_rim(board_t board, int square_size, int x, int y)
{
    for (int i = 0; i < square_size && x + i < board->width; i++)
        if (board->cells[(y + square_size - 1) * board->width + x + i] != '.')
            return 0;
    for (int i = 0; i < square_size && y + i < board->height; i++)
        if (board->cells[(y + i) * board->width + x + square_size - 1] != '.')
            return 0;
    return 1;
}

static void fill_square(board_t board, int square_size, int x, int y)
{
    for (int i = 0; i < square_size; i++)
        for (int j = 0; j < square_size; j++)
            board->cells[(y + i) * board->width + x + j] = 'x';
}

int find_biggest_square_at(board_t board, int *square_size, int x, int y)
{
    int ret = 0;

    if (!does_square_fit(board, *square_size, x, y))
        return 0;
    while (x + *square_size < board->width && y + *square_size < board->height
        && does_square_fit_rim(board, *square_size + 1, x, y)) {
        (*square_size)++;
        ret = 1;
    }
    return ret;
}

void find_biggest_square(board_t board, int *square_size, int *x, int *y)
{
    for (int i = 0; i < board->height; i++)
        for (int j = 0; j < board->width; j++) {
            if (find_biggest_square_at(board, square_size, j, i)) {
                *x = j + 1;
                *y = i + 1;
            };
        }
}

void board_resolve(board_t board)
{
    int square_size = 0;
    int x = 0;
    int y = 0;

    find_biggest_square(board, &square_size, &x, &y);
    fill_square(board, square_size, x - 1, y - 1);
}

void board_display(const board_t board)
{
    for (int i = 0; i < board->height; i++) {
        write(STDOUT_FILENO, board->cells + i * board->width, board->width);
        write(STDOUT_FILENO, "\n", 1);
    }
}

static board_t board_construct(int width, int height)
{
    board_t board = my_malloc(sizeof(*board));

    board->width = width;
    board->height = height;
    board->cells = my_calloc(sizeof(char), width * height);
    my_memset(board->cells, ' ', width * height);
    return board;
}

board_t board_generate(int size, const char *pattern)
{
    board_t board = board_construct(size, size);

    for (int i = 0; i < (size * size) / (int) my_strlen(pattern); i++)
        my_memcpy(board->cells + i * my_strlen(pattern), pattern,
            my_strlen(pattern));
    if ((size * size) % (int) my_strlen(pattern) != 0)
        my_memcpy(board->cells
                + (size * size) / (int) my_strlen(pattern)
                    * my_strlen(pattern),
            pattern, (size * size) % (int) my_strlen(pattern));
    return board;
}

static size_t get_file_size(const char *filename)
{
    struct stat st;

    if (stat(filename, &st) == -1)
        return 0;
    return st.st_size;
}

static int guess_size(int *width, int *height, char **line, char *buffer)
{
    int read_size = *width;

    for (ssize_t i = 0; i < read_size; i++)
        if (buffer[i] == '\n') {
            *height = my_atoi(buffer);
            *line = buffer + i + 1;
            break;
        }
    for (ssize_t i = 0; i < read_size; i++)
        if ((*line)[i] == '\n') {
            *width = i;
            break;
        }
    return 0;
}

board_t board_load_from_file(const char *filename)
{
    int fd = open(filename, O_RDONLY | O_CLOEXEC);
    board_t board = NULL;
    char *buffer = NULL;
    char *line = NULL;
    int height = 0;
    int width = 0;

    buffer = my_malloc(get_file_size(filename));
    if (fd == -1)
        return NULL;
    width = read(fd, buffer, get_file_size(filename));
    if (width == -1)
        return NULL;
    guess_size(&width, &height, &line, buffer);
    board = board_construct(width, height);
    for (int i = 0; i < height; i++)
        my_memcpy(board->cells + i * width, line + i * (width + 1), width);
    my_free(buffer);
    return board;
}
