/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** Consumers for vgprintf
*/

#include "vgprintf.h"
#include <limits.h>
#include <my_printf.h>
#include <stdint.h>
#include <my_classify.h>

/**
 * Returns the number of digits of an uintmax_t in a given base.
 *
 * This is a dynamic version of a potential uintmax_log10.
 */
static int uintmax_logdyn(uintmax_t nbr, int base)
{
    int ret = 0;

    for (; nbr; nbr /= base)
        ret++;
    return ret;
}

/**
 * Returns the minimum length of the number to print.
 */
static int get_min_nbr_digits(printf_state_t *state)
{
    if (state->use_precision)
        return state->precision;
    if (state->flags & ZERO_PAD)
        return state->width;
    return 1;
}

/**
 * Returns a ^ b.
 */
static uintmax_t powi(int a, int b)
{
    uintmax_t ret = 1;

    for (; b; b--)
        ret *= a;
    return ret;
}

/**
 * Prints an uintmax_t given in argument.i in a given base.
 *
 * This may do multiple calls to state->write
 */
int print_uintmax_base(
    printf_state_t *state, arg_t argument, const char *base, int base_len)
{
    int nb_digits =
        MAX(get_min_nbr_digits(state), uintmax_logdyn(argument.i, base_len));

    state->written_len += nb_digits;
    for (; nb_digits; nb_digits--) {
        state->write(state->write_state,
            &base[argument.i / powi(base_len, nb_digits - 1)
                % (uintmax_t) base_len],
            1);
    }
    return 0;
}

/**
 * Prints an uintmax_t given in argument.i.
 *
 * This may do multiple calls to state->write
 */
int print_uintmax(printf_state_t *state, arg_t argument)
{
    return print_uintmax_base(state, argument, "0123456789", 10);
}

/**
 * Prints an intmax_t given in argument.i.
 *
 * This may do multiple calls to state->write
 */
int print_intmax(printf_state_t *state, arg_t argument)
{
    intmax_t arg = argument.i;

    if (arg < 0 || state->flags & (MARK_POS | PAD_POS)) {
        state->written_len++;
        if (state->flags & ZERO_PAD)
            state->width--;
    }
    if (arg < 0)
        if (state->write(state->write_state, "-", 1) < 0)
            return -1;
    if (arg >= 0 && state->flags & MARK_POS)
        if (state->write(state->write_state, "+", 1) < 0)
            return -1;
    if (arg >= 0 && state->flags & PAD_POS)
        if (state->write(state->write_state, " ", 1) < 0)
            return -1;
    if (arg < 0)
        argument.i = -argument.i;
    return print_uintmax(state, argument);
}

/**
 * Prints an uintmax_t given in argument.i in hexadecimal.
 *
 * This may do multiple calls to state->write
 */
int print_uintmax_x(printf_state_t *state, arg_t argument)
{
    const char *string = my_isupper((state->format - 1)[0])
        ? "0123456789ABCDEF0X"
        : "0123456789abcdef0x";

    if (state->flags & ALT_FORM) {
        state->written_len += 2;
        if (state->write(state->write_state, string + 16, 2) < 0)
            return -1;
    }
    return print_uintmax_base(state, argument, string, 16);
}

/**
 * Prints an uintmax_t given in argument.i in octal.
 *
 * This may do multiple calls to state->write
 */
int print_uintmax_o(printf_state_t *state, arg_t argument)
{
    if (state->flags & ALT_FORM) {
        state->precision =
            MAX(state->precision, uintmax_logdyn(argument.i, 8) + 1);
        state->use_precision = 1;
    }
    return print_uintmax_base(state, argument, "01234567", 8);
}
