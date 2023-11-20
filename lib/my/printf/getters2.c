/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** Getters from va_list
*/

#include "vgprintf.h"
#include <my_printf.h>

/**
 * Fetches a void * value from state->ap, storing it in the p field of the
 * returned union.
 */
arg_t get_ptr(printf_state_t *state)
{
    arg_t val;

    val.p = va_arg(*state->ap, void *);
    return val;
}

/**
 * Fetches a double value from state->ap, storing it in the f field of the
 * returned union.
 */
arg_t get_double(printf_state_t *state)
{
    arg_t val;

    val.f = va_arg(*state->ap, double);
    return val;
}

/**
 * Fetches a long double value from state->ap, storing it in the f field of the
 * returned union.
 */
arg_t get_ldouble(printf_state_t *state)
{
    arg_t val;

    val.f = va_arg(*state->ap, long double);
    return val;
}

/**
 * Fetches a long long value from state->ap, storing it in the i field of the
 * returned union.
 */
arg_t get_longlong(printf_state_t *state)
{
    arg_t val;

    val.i = va_arg(*state->ap, long long);
    return val;
}

/**
 * Fetches a long value from state->ap, storing it in the i field of the
 * returned union.
 */
arg_t get_long(printf_state_t *state)
{
    arg_t val;

    val.i = va_arg(*state->ap, long);
    return val;
}
