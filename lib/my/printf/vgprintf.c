/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** Implementation for vgprintf
*/

#include "vgprintf.h"
#include <my_memory.h>
#include <my_printf.h>
#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>

/**
 * A mock implementation of the write callback, that does nothing.
 *
 * The first 3 lines of the function serve to silence warnings about unused
 * parameters.
 */
static ssize_t mock_write_callback(void *state, const char *str, size_t len)
{
    (void) state;
    (void) str;
    (void) len;
    return 0;
}

/**
 * Gets the length of an argument, using a mock implementation of a write
 * callback.
 *
 * This serves to get the width of the argument to accurately produce space
 * padding
 */
static int get_percent_action_length(printf_state_t *state, arg_t arg)
{
    printf_state_t mock_state = *state;

    mock_state.format = state->format;
    mock_state.ap = NULL;
    mock_state.write = mock_write_callback;
    mock_state.write_state = NULL;
    mock_state.written_len = 0;
    HANDLERS[state->conv_spec](&mock_state, arg);
    return mock_state.written_len;
}

/**
 * Prints the right amount of spaces to pad a value of the given len.
 *
 * This function short-circuits if the field length is greater than the minimum
 * width.
 * This function makes at most one call to state->write
 */
static int put_pad(printf_state_t *state, int field_len)
{
    int pad_len = state->width - field_len;
    char *str = NULL;
    int ret;

    if (pad_len <= 0)
        return 0;
    str = malloc(pad_len);
    if (!str)
        return -1;
    my_memset(str, ' ', pad_len);
    state->written_len += pad_len;
    ret = state->write(state->write_state, str, pad_len);
    free(str);
    return ret;
}

/**
 * Makes the necessary work to print (except in the case of the %n action being
 * requested) the action.
 *
 * It fetches the arg, compute its length, puts the right amount of padding if
 * it is needed, prints the argument according to its specifier, and puts the
 * left-align padding if requested.
 */
static int handle_percent_action(printf_state_t *state)
{
    arg_t arg = ARGS[state->conv_spec](state);
    int field_width = get_percent_action_length(state, arg);

    if (!(state->flags & (LEFT_PAD | ZERO_PAD)))
        if (put_pad(state, field_width) < 0)
            return -1;
    if (HANDLERS[state->conv_spec](state, arg) < 0)
        return -1;
    if (state->flags & LEFT_PAD)
        if (put_pad(state, field_width) < 0)
            return -1;
    return 0;
}

/**
 * Advances the format pointer past the format specifier behind the format
 * pointer, while handling it. If the format ptr is not pointing to a % sign,
 * it returns successfully.
 *
 * It actually parses the format specifier, storing the needed data in the
 * state struct, then runs it.
 * It short-circuits if the format specifier is `%%`, not running the steps
 * above.
 */
static int handle_percent(printf_state_t *state)
{
    int ret;

    if (*state->format != '%')
        return 0;
    state->format++;
    if (*state->format == '%') {
        state->written_len++;
        ret = state->write(state->write_state, state->format, 1);
        state->format++;
        return ret;
    }
    if (parse_percent_action(state) < 0)
        return -1;
    return handle_percent_action(state);
}

/**
 * Advances the format pointer to the next percent or to the end of the string,
 * while printing the part in between.
 *
 * It actually computes the length of the string to print, and does only one
 * call to `state->write`
 */
static int print_until_percent(printf_state_t *state)
{
    const char *start = state->format;
    int len = 0;

    for (; *(state->format) && *(state->format) != '%'; (state->format)++)
        len++;
    state->written_len += len;
    return state->write(state->write_state, start, len);
}

/**
 * Similar to vfprintf(3), but instead of taking a FILE *, it takes a callback
 * and opaque data that is passed to a callback.
 */
int my_vgprintf(const write_callback_t write, void *const write_state,
    const char *format, va_list ap)
{
    va_list ap2;
    printf_state_t state = {.write = write,
        .write_state = write_state,
        .format = format,
        .written_len = 0,
        .ap = &ap2};
    int ret = 0;

    va_copy(ap2, ap);
    while (ret >= 0 && *(state.format)) {
        ret = print_until_percent(&state);
        if (ret < 0)
            break;
        ret = handle_percent(&state);
    }
    va_end(ap2);
    return (ret < 0) ? ret : state.written_len;
}

int my_gprintf(const write_callback_t write, void *const write_state,
    const char *format, ...)
{
    va_list ap;
    int ret;

    va_start(ap, format);
    ret = my_vgprintf(write, write_state, format, ap);
    va_end(ap);
    return ret;
}
