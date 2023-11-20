/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** My own memory functions
*/

#pragma once

#include <stdlib.h>

void my_free(void *ptr);
void *my_malloc(size_t size);
void *my_calloc(size_t nmemb, size_t size);
void *my_realloc(void *ptr, size_t size);
void *my_reallocarray(void *ptr, size_t nmemb, size_t size);
void *my_memset(void *s, int c, size_t n);
size_t my_strlen(char const *str);
char *my_strdup(char const *src);
char *my_stracat(char *dest, char const *src);
char *my_strancat(char *dest, char const *src, size_t n);
int my_strcmp(char const *s1, char const *s2);
void *my_memcpy(void *dest, void const *src, size_t n);
