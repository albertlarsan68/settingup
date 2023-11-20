/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** My own memory functions
*/

#include <my_memory.h>
#include <my.h>

void *my_reallocarray(void *ptr, size_t nmemb, size_t size)
{
    return my_realloc(ptr, nmemb * size);
}

size_t my_strlen(const char *s)
{
    size_t len = 0;

    while (s[len])
        len++;
    return len;
}

char *my_strdup(const char *s)
{
    size_t len = my_strlen(s);
    char *str = my_malloc(len + 1);

    my_memcpy(str, s, len);
    str[len] = '\0';
    return str;
}

char *my_stracat(char *src, const char *dest)
{
    size_t len_src = my_strlen(src);
    size_t len_dest = my_strlen(dest);
    char *str = my_malloc(len_src + len_dest + 1);

    my_memcpy(str, src, len_src);
    my_memcpy(str + len_src, dest, len_dest);
    str[len_src + len_dest] = '\0';
    my_free(src);
    return str;
}

char *my_strancat(char *src, const char *dest, size_t n)
{
    size_t len_src = my_strlen(src);
    char *str = my_malloc(len_src + n + 1);

    my_memcpy(str, src, len_src);
    my_memcpy(str + len_src, dest, n);
    str[len_src + n] = '\0';
    my_free(src);
    return str;
}
