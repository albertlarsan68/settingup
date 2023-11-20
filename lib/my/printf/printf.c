/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** Implementation for printf
*/

#include <my_printf.h>

/**
 * See printf(3) for information about this function
 */
int my_printf(const char *format, ...)
{
    va_list ap;
    int ret;

    va_start(ap, format);
    ret = my_vdprintf(1, format, ap);
    va_end(ap);
    return ret;
}
