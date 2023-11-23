/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** My own memory functions
*/

#include <my_memory.h>
#include <my.h>
#include <unistd.h>

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
        write(2, "Error: malloc failed\n", 21);
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

size_t my_strlen(const char *s)
{
    size_t len = 0;

    while (s[len])
        len++;
    return len;
}
