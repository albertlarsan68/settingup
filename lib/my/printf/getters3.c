/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** Getters from va_list
*/

#include "vgprintf.h"
#include <my_printf.h>

/**
 * Fetches a ptrdiff_t value from state->ap, storing it in the i field of the
 * returned union.
 */
arg_t get_ptrdiff(printf_state_t *state)
{
    arg_t val;

    val.i = va_arg(*state->ap, ptrdiff_t);
    return val;
}

/**
 * Fetches a signed char value from state->ap, storing it in the i field of the
 * returned union.
 */
arg_t get_schar(printf_state_t *state)
{
    arg_t val;

    val.i = (signed char) va_arg(*state->ap, signed int);
    return val;
}

/**
 * Fetches a short from state->ap, storing it in the i field of the returned
 * union.
 */
arg_t get_short(printf_state_t *state)
{
    arg_t val;

    val.i = (short) va_arg(*state->ap, int);
    return val;
}

/**
 * Fetches a size_t value from state->ap, storing it in the i field of the
 * returned union.
 */
arg_t get_size(printf_state_t *state)
{
    arg_t val;

    val.i = va_arg(*state->ap, size_t);
    return val;
}

/**
 * Fetches a ssize_t value from state->ap, storing it in the i field of the
 * returned union.
 */
arg_t get_ssize(printf_state_t *state)
{
    arg_t val;

    val.i = va_arg(*state->ap, ssize_t);
    return val;
}
