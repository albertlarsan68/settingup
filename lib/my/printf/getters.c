/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** Getters from va_list
*/

#include "vgprintf.h"
#include <my_printf.h>

/**
 * Fetches a char value from state->ap, storing it in the i field of the
 * returned union.
 */
arg_t get_char(printf_state_t *state)
{
    arg_t val;

    val.i = (char) va_arg(*state->ap, int);
    return val;
}

/**
 * Fetches an int value from state->ap, storing it in the i field of the
 * returned union
 */
arg_t get_int(printf_state_t *state)
{
    arg_t val;

    val.i = (int) va_arg(*state->ap, int);
    return val;
}

/**
 * Fetches an int value from state->ap, storing it in the i field of the
 * returned union
 */
arg_t get_uint(printf_state_t *state)
{
    arg_t val;

    val.i = (unsigned int) va_arg(*state->ap, unsigned int);
    return val;
}

/**
 * Fetches an intmax_t value from state->ap, storing it in the i field of the
 * returned union
 */
arg_t get_intmax(printf_state_t *state)
{
    arg_t val;

    val.i = va_arg(*state->ap, intmax_t);
    return val;
}

/**
 * Fetches an uintmax_t value from state->ap, storing it in the i field of the
 * returned union
 */
arg_t get_uintmax(printf_state_t *state)
{
    arg_t val;

    val.i = va_arg(*state->ap, uintmax_t);
    return val;
}
