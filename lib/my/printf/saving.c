/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** Consumers for vgprintf
*/

#include "vgprintf.h"
#include <my_printf.h>

/**
 * Saves the current number of written bytes to the long pointed by argument.p
 *
 * It does not call write.
 */
int save_lptr(printf_state_t *state, arg_t argument)
{
    long *arg = argument.p;

    *arg = state->written_len;
    return 0;
}

/**
 * Saves the current number of written bytes to the signed char pointed by
 * argument.p
 *
 * It does not call write.
 */
int save_scptr(printf_state_t *state, arg_t argument)
{
    signed char *arg = argument.p;

    *arg = state->written_len;
    return 0;
}

/**
 * Saves the current number of written bytes to the intmax_t pointed by
 * argument.p
 *
 * It does not call write.
 */
int save_smptr(printf_state_t *state, arg_t argument)
{
    intmax_t *arg = argument.p;

    *arg = state->written_len;
    return 0;
}

/**
 * Saves the current number of written bytes to the short pointed by argument.p
 *
 * It does not call write.
 */
int save_sptr(printf_state_t *state, arg_t argument)
{
    short *arg = argument.p;

    *arg = state->written_len;
    return 0;
}

/**
 * Saves the current number of written bytes to the ssize_t pointed by
 * argument.p
 *
 * It does not call write.
 */
int save_zptr(printf_state_t *state, arg_t argument)
{
    ssize_t *arg = argument.p;

    *arg = state->written_len;
    return 0;
}
