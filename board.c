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

/**
 * @brief Check if a square of a given size can fit in the board at the given
 * position.
 *
 * Complexity: O(square_size²)
 *
 * @param board The board to check.
 * @param square_size The size of the square to check.
 * @param x The x position of the square.
 * @param y The y position of the square.
 * @return int 1 if the square can fit, 0 otherwise.
 */
static int does_square_fit(
    board_t board, size_t square_size, size_t x, size_t y)
{
    if (x + square_size > board->width || y + square_size > board->height)
        return 0;
    for (size_t i = 0; i < square_size && x + i < board->width; i++)
        for (size_t j = 0; j < square_size && y + j < board->height; j++)
            if (board->cells[(y + j) * board->width + x + i] != '.')
                return 0;
    return 1;
}

/**
 * @brief Check if the right and bottom sides of a square of a given size can
 * fit in the board at the given position.
 *
 * Complexity: O(2 * square_size)
 *
 * @param board The board to check.
 * @param square_size The size of the square to check.
 * @param x The x position of the square.
 * @param y The y position of the square.
 * @return int 1 if the square can fit, 0 otherwise.
 */
static int does_square_fit_rim(
    board_t board, size_t square_size, size_t x, size_t y)
{
    for (size_t i = 0; i < square_size && x + i < board->width; i++)
        if (board->cells[(y + square_size - 1) * board->width + x + i] != '.')
            return 0;
    for (size_t i = 0; i < square_size && y + i < board->height; i++)
        if (board->cells[(y + i) * board->width + x + square_size - 1] != '.')
            return 0;
    return 1;
}

/**
 * @brief Fill a square of a given size in the board at the given position.
 *
 * Complexity: O(square_size²)
 *
 * @param board The board to fill.
 * @param square_size The size of the square to fill.
 * @param x The x position of the square.
 * @param y The y position of the square.
 */
static void fill_square(board_t board, size_t square_size, size_t x, size_t y)
{
    for (size_t i = 0; i < square_size; i++)
        for (size_t j = 0; j < square_size; j++)
            board->cells[(y + i) * board->width + x + j] = 'x';
}

/**
 * @brief Find the biggest square that can fit in the board at the given
 * position.
 *
 * Complexity: O(square_size²)
 *
 * @param board The board to check.
 * @param square_size The size of the square to check, will be updated to the
 * size of the biggest square that can fit.
 * @param x The x position of the square.
 * @param y The y position of the square.
 * @return int 1 if the square can fit, 0 otherwise.
 */
int find_biggest_square_at(
    board_t board, size_t *square_size, size_t x, size_t y)
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

/**
 * @brief Find the biggest square that can fit in the board.
 *
 * Complexity: O(board->width * board->height * square_size²)
 *
 * @param board The board to check.
 * @param square_size The size of the square to check, will be updated to the
 * size of the biggest square that can fit.
 * @param x The x position of the square.
 * @param y The y position of the square.
 */
void find_biggest_square(
    board_t board, size_t *square_size, size_t *x, size_t *y)
{
    for (size_t i = *x; i < board->height - *square_size; i++)
        for (size_t j = *y; j < board->width - *square_size; j++) {
            if (find_biggest_square_at(board, square_size, j, i)) {
                *x = j + 1;
                *y = i + 1;
            };
        }
}

/**
 * @brief Resolve the board by filling the biggest square with 'x'.
 *
 * Complexity: O(board->width * board->height * square_size²)
 *
 * @param board The board to resolve.
 */
void board_resolve(board_t board)
{
    size_t square_size = 0;
    size_t x = 0;
    size_t y = 0;

    find_biggest_square(board, &square_size, &x, &y);
    fill_square(board, square_size, x - 1, y - 1);
}

/**
 * @brief Display the board on the standard output.
 *
 * Syscall complexity: O((2 * board->height)(write))
 *
 * @param board The board to display.
 */
void board_display(const board_t board)
{
    for (size_t i = 0; i < board->height; i++) {
        write(STDOUT_FILENO, board->cells + i * board->width, board->width);
        write(STDOUT_FILENO, "\n", 1);
    }
}

/**
 * @brief Construct a board of a given size.
 *
 * Syscall complexity: O(2(malloc))
 *
 * @param width The width of the board.
 * @param height The height of the board.
 * @return board_t The constructed board.
 */
static board_t board_construct(size_t width, size_t height)
{
    board_t board = my_malloc(sizeof(*board));

    board->width = width;
    board->height = height;
    board->cells = my_calloc(sizeof(char), width * height);
    return board;
}

/**
 * @brief Generate a board of a given size with a given pattern.
 *
 * Complexity: O(size² / my_strlen(pattern))
 *
 * @param size The size of the board.
 * @param pattern The pattern to fill the board with.
 * @return board_t The generated board.
 */
board_t board_generate(size_t size, const char *pattern)
{
    board_t board = board_construct(size, size);

    for (size_t i = 0; pattern[i] != '\0'; i++)
        if (pattern[i] != '.' && pattern[i] != 'o')
            return NULL;
    for (size_t i = 0; i < (size * size) / my_strlen(pattern); i++)
        my_memcpy(board->cells + i * my_strlen(pattern), pattern,
            my_strlen(pattern));
    if ((size * size) % my_strlen(pattern) != 0)
        my_memcpy(board->cells
                + (size * size) / my_strlen(pattern) * my_strlen(pattern),
            pattern, (size * size) % my_strlen(pattern));
    return board;
}

/**
 * @brief Get the size of a file.
 *
 * Complexity: O(1)
 *
 * Syscall complexity: O(1(stat))
 *
 * @param filename The name of the file.
 * @return size_t The size of the file.
 */
static size_t get_file_size(const char *filename)
{
    struct stat st;

    if (stat(filename, &st) == -1)
        return 0;
    return st.st_size;
}

/**
 * @brief Guess the size of the board from the first two lines of the file.
 *
 * Complexity: O(width)
 *
 * @param str The string to convert.
 * @return int The converted integer.
 */
static int guess_size(
    ssize_t *width, size_t *height, char **line, char *buffer)
{
    ssize_t read_size = *width;

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

/**
 * @brief Check if a line is valid.
 *
 * Complexity: O(width)
 *
 * @param filename The name of the file.
 * @return board_t The loaded board.
 */
int is_line_valid(char *line, size_t width)
{
    for (size_t i = 0; i < width; i++)
        if (line[i] != '.' && line[i] != 'o')
            return 0;
    return 1;
}

/**
 * @brief Load a board from a file.
 *
 * Complexity: O(file_size)
 *
 * @param filename The name of the file.
 * @return board_t The loaded board.
 */
board_t board_load_from_file(const char *filename)
{
    int fd = open(filename, O_RDONLY | O_CLOEXEC);
    board_t board = NULL;
    char *buffer = NULL;
    char *line = NULL;
    size_t height = 0;
    ssize_t width = 0;

    buffer = my_malloc(get_file_size(filename));
    if (fd == -1)
        return NULL;
    width = read(fd, buffer, get_file_size(filename));
    if (width == -1)
        return NULL;
    guess_size(&width, &height, &line, buffer);
    board = board_construct(width, height);
    for (size_t i = 0; i < height; i++) {
        if (line[i * (width + 1) + width] != '\n')
            return NULL;
        if ((i + 1) * width + (line - buffer) > get_file_size(filename))
            return NULL;
        if (is_line_valid(line + i * (width + 1), width))
            my_memcpy(board->cells + i * width, line + i * (width + 1), width);
        else
            return NULL;
    }
    my_free(buffer);
    return board;
}
