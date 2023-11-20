/*
** EPITECH PROJECT, 2023
** libmy
** File description:
** Utils
*/

#include <my.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void *my_memset(void *s, int c, size_t n)
{
    char *str = s;

    for (size_t i = 0; i < n; i++)
        str[i] = c;
    return s;
}

int my_isupper(int c)
{
    return (c >= 'A' && c <= 'Z');
}

int my_atoi(const char *str)
{
    int i = 0;
    int nb = 0;
    int sign = 1;

    while (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        nb *= 10;
        nb += str[i] - '0';
        i++;
    }
    return nb * sign;
}
