/*
** EPITECH PROJECT, 2023
** libmy
** File description:
** Contains saprintf function
*/

#include <my_memory.h>
#include <my_printf.h>
#include <stddef.h>
#include <stdio.h>

ssize_t write_callback(void *data, const char *buffer, size_t size)
{
    char **str = data;

    *str = my_strancat(*str, buffer, size);
    return size;
}

char *my_vsaprintf(const char *format, va_list args)
{
    char *str = my_strdup("");

    my_vgprintf(write_callback, &str, format, args);
    return str;
}

char *my_saprintf(const char *format, ...)
{
    va_list args;
    char *str;

    va_start(args, format);
    str = my_vsaprintf(format, args);
    va_end(args);
    return str;
}
