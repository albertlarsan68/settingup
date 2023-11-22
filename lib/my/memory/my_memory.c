/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** My own memory functions
*/

#include <my_memory.h>
#include <my.h>
#include <unistd.h>

static void my_putnbr(int fd, size_t nb)
{
    if (nb >= 10)
        my_putnbr(fd, nb / 10);
    write(fd, &"0123456789"[nb % 10], 1);
}

void *my_memcpy(void *dest, const void *src, size_t num)
{
    for (size_t i = 0; i < num; i++)
        *((char *) dest + i) = *((char *) src + i);
    return dest;
}

void *my_malloc(size_t size)
{
    void *ptr = malloc(size + sizeof(size_t));

    if (!ptr) {
        write(STDERR_FILENO, "Unable to allocate ", 19);
        my_putnbr(STDERR_FILENO, size);
        write(STDERR_FILENO, " bytes\n", 7);
        __builtin_trap();
    }
    *((size_t *) ptr) = size;
    return (char *) ptr + sizeof(size_t);
}

void my_free(void *ptr)
{
    free((char *) ptr - sizeof(size_t));
}

void *my_calloc(size_t nmemb, size_t size)
{
    void *ptr = my_malloc(nmemb * size);

    my_memset(ptr, 0, nmemb * size);
    return ptr;
}

void *my_realloc(void *ptr, size_t size)
{
    void *new_ptr = my_malloc(size);

    if (!ptr)
        return new_ptr;
    my_memcpy(new_ptr, ptr, MIN(*((size_t *) ptr - 1), size));
    my_free(ptr);
    return new_ptr;
}
