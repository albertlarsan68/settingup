/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** My own memory functions
*/

#include <my_memory.h>
#include <my.h>

int my_strcmp(const char *s1, const char *s2)
{
    size_t i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}
