/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** Consumers for vgprintf
*/

#include "vgprintf.h"
#include <my_printf.h>

/**
 * Prints a string given in argument.p, according to the requirements in state
 *
 * It computes the length of the string, capping it at state->precision if
 * state->use_precision is not 0.
 * It then only does a single call to state->write.
 */
int put_string(printf_state_t *state, arg_t argument)
{
    const char *str = argument.p;
    int len = 0;
    const char *start = str;

    for (; *str != 0; str++)
        len++;
    len = state->use_precision ? MIN(len, state->precision) : len;
    state->written_len += len;
    return state->write(state->write_state, start, len);
}

/**
 * Prints a given char in argument.i.
 *
 * It casts the argument.i value to a char before doing a single call to
 * state->write
 */
int put_char(printf_state_t *state, arg_t argument)
{
    char c = argument.i;

    state->written_len++;
    return state->write(state->write_state, &c, 1);
}

/**
 * Saves the current number of written bytes to the int pointed by argument.p
 *
 * It does not call write.
 */
int save_intptr(printf_state_t *state, arg_t argument)
{
    int *arg = argument.p;

    *arg = state->written_len;
    return 0;
}

/**
 * Saves the current number of written bytes to the ptrdiff_t pointed by
 * argument.p
 *
 * It does not call write.
 */
int save_dptr(printf_state_t *state, arg_t argument)
{
    ptrdiff_t *arg = argument.p;

    *arg = state->written_len;
    return 0;
}

/**
 * Saves the current number of written bytes to the long long pointed by
 * argument.p
 *
 * It does not call write.
 */
int save_llptr(printf_state_t *state, arg_t argument)
{
    long long *arg = argument.p;

    *arg = state->written_len;
    return 0;
}
