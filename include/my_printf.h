/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** Header
*/

#pragma once
#include <stdarg.h>
#include <sys/types.h>

/**
 * A callback to write the data to where it needs to go.
 *
 * It will be called by my_vgprintf when as needed, with the first argument
 * being a pointer to some opaque (for vgprintf) data, that you can use to keep
 * some state. The second argument is a pointer to a char array of arbitrary
 * data to print. It may contain arbitrary null bytes, and is not always
 * terminated by a null byte. This callback should only read up to the length,
 * which is the length of the data to print.
 *
 * This callback must return a zero or positive value on success, and a
 * negative value on failure.
 */
typedef ssize_t(*write_callback_t)(void *, const char *, size_t);

/**
 * See printf(3) for information about this function
 */
int my_printf(const char *format, ...);

/**
 * See vdprintf(3) for information about this function
 */
int my_vdprintf(int fd, const char *format, va_list ap);

/**
 * See dprintf(3) for information about this function
 */
int my_dprintf(int fd, const char *format, ...);

/**
 * Similar to vfprintf(3), but instead of taking a FILE *, it takes a callback
 * and opaque data that is passed to a callback.
 */
int my_vgprintf(
    write_callback_t write, void *write_state, const char *format, va_list ap);

/**
 * Similar to fprintf(3), but instead of taking a FILE *, it takes a callback
 * and opaque data that is passed to a callback.
 */
int my_gprintf(
    write_callback_t write, void *write_state, const char *format, ...);

/**
 * Simular to sprintf(3), but instead allocates the string it needs and returns
 * it. The caller is responsible for freeing the string.
 */
char *my_saprintf(const char *format, ...);
