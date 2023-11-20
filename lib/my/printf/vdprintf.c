/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** Implementation for vdprintf
*/

#include "vdprintf.h"
#include <my_printf.h>
#include <unistd.h>

/**
 * A callback to write to a file descriptor, specified in the state.
 *
 * The loop is here to retry the writes in case of incomplete writes.
 */
static ssize_t vdpr_write_cb(void *state, const char *str, size_t len)
{
    my_vdprintf_data_t *this_state = state;
    ssize_t write_ret = 0;

    while (len) {
        write_ret = write(this_state->fd, str, len);
        if (write_ret == -1)
            return -1;
        str += write_ret;
        len -= write_ret;
    }
    return 0;
}

/**
 * See vdprintf(3) for information about this function
 */
int my_vdprintf(int fd, const char *format, va_list ap)
{
    my_vdprintf_data_t data = {.fd = fd};

    return my_vgprintf(vdpr_write_cb, &data, format, ap);
}

/**
 * See vdprintf(3) for information about this function
 */
int my_dprintf(int fd, const char *format, ...)
{
    va_list ap;
    int ret;

    va_start(ap, format);
    ret = my_vdprintf(fd, format, ap);
    va_end(ap);
    return ret;
}
