/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** Getters from va_list
*/

#include "vgprintf.h"
#include <my_printf.h>

/**
 * Fetches an unsigned char value from state->ap, storing it in the i field of
 * the returned union.
 */
arg_t get_uchar(printf_state_t *state)
{
    arg_t val;

    val.i = (unsigned char) va_arg(*state->ap, unsigned int);
    return val;
}

/**
 * Fetches an unsigned long value from state->ap, storing it in the i field of
 * the returned union.
 */
arg_t get_ulong(printf_state_t *state)
{
    arg_t val;

    val.i = va_arg(*state->ap, unsigned long);
    return val;
}

/**
 * Fetches an unsigned long long value from state->ap, storing it in the i
 * field of the returned union.
 */
arg_t get_ulonglong(printf_state_t *state)
{
    arg_t val;

    val.i = va_arg(*state->ap, unsigned long long);
    return val;
}

/**
 * Fetches an unsigned short value from state->ap, storing it in the i field of
 * the returned union.
 */
arg_t get_ushort(printf_state_t *state)
{
    arg_t val;

    val.i = (unsigned short) va_arg(*state->ap, unsigned int);
    return val;
}
