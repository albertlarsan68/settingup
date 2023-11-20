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

/**
 * Prints a pointer given in argument.ptr.
 *
 * This may do multiple calls to state->write
 */
int print_ptr(printf_state_t *state, arg_t argument)
{
    arg_t arg = {.i = (uintptr_t) argument.p};

    state->flags = ALT_FORM | ZERO_PAD;
    return print_uintmax_x(state, arg);
}
