/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** parses the format specifier
*/

#include "vgprintf.h"
#include <my_printf.h>
#include <limits.h>

/**
 * Returns whether the given char is a digit or not.
 * Returns 0 if the char is not a digit, and a positive int otherwise
 */
static int my_isdigit(char c)
{
    return c >= '0' && c <= '9';
}

/**
 * Advances the given string pointer, parsing a positive int litteral in
 * base 10.
 * The given string pointer is set to the first non-digit char.
 * If the string litteral is too big to fit in a `int`, this functions return
 * -1.
 */
static int my_getint(const char **s)
{
    int i;

    for (i = 0; my_isdigit(**s); (*s)++) {
        if (i > INT_MAX / 10 || **s - '0' > INT_MAX - 10 * i)
            i = -1;
        else
            i = 10 * i + (**s - '0');
    }
    return i;
}

/**
 * Advances the format pointer, while parsing the optional conversion flags.
 * The pointer must be pointing to the first char of the conversion flags, or
 * to another char if there is no conversion flags. This usually corresponds to
 * the first char after the initial %.
 */
static int parse_conv_flags(printf_state_t *state)
{
    for (state->flags = 0; (unsigned) *state->format - ' ' < 32
        && (FLAGMASK & (1U << (*state->format - ' ')));
        state->format++)
        state->flags |= 1U << (*state->format - ' ');
    return 0;
}

/**
 * Advances the format pointer, while parsing an optional field width
 * specifier.
 * The pointer must be pointing to the first digit of the field width
 * specifier, or to another char if there is no precision specifier.
 * This function handles the `*` case, reading from state->ap as needed.
 * This function handles the negative `*` case, setting the LEFT_PAD flag as
 * needed, and making sure that state->width is always positive.
 */
static int parse_field_width(printf_state_t *state)
{
    if (*state->format == '*') {
        state->width = va_arg(*state->ap, int);
        state->format++;
        if (state->width < 0) {
            state->flags |= LEFT_PAD;
            state->width = -state->width;
        }
    } else {
        state->width = my_getint(&state->format);
    }
    return 0;
}

/**
 * Advances the format pointer, while parsing an optional precision specifier.
 * The pointer must be pointing to the `.` of the precision specifier, or to
 * another char if there is no precision specifier.
 * This function handles the `*` case, reading from state->ap as needed.
 */
static int parse_precision(printf_state_t *state)
{
    if (*state->format == '.' && state->format[1] == '*') {
        state->precision = va_arg(*state->ap, int);
        state->format += 2;
        state->use_precision = (state->precision >= 0);
        return 0;
    }
    if (*state->format == '.' && state->format[1] == '-') {
        state->format += 2;
        my_getint(&state->format);
        state->use_precision = 0;
    } else if (*state->format == '.') {
        state->format++;
        state->precision = my_getint(&state->format);
        state->use_precision = 1;
    } else {
        state->precision = -1;
        state->use_precision = 0;
    }
    return 0;
}

/**
 * Advances the format pointer, while parsing a valid conversion specifier.
 * The pointer must be pointing on the first character of a valid
 * `(length modifier)?+conversion specifier`, and invokes UB if this is not the
 * case.
 */
static int parse_conv_spec(printf_state_t *state)
{
    for (state->conv_spec = BARE; state->conv_spec < END_OF_SPEC;) {
        state->conv_spec =
            STATES[state->conv_spec][INDEX_STATE(*state->format)];
        state->format++;
    }
    return 0;
}

/**
 * Advances the format pointer, while parsing a valid format specifier.
 * The pointer must be pointing on the character just after the start %
 */
int parse_percent_action(printf_state_t *state)
{
    if (parse_conv_flags(state) < 0)
        return -1;
    if (parse_field_width(state) < 0)
        return -1;
    if (parse_precision(state) < 0)
        return -1;
    if (parse_conv_spec(state) < 0)
        return -1;
    if (state->flags & MARK_POS)
        state->flags &= ~PAD_POS;
    if (state->flags & LEFT_PAD)
        state->flags &= ~ZERO_PAD;
    return 0;
}
