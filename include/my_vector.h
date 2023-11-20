/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** My own vector
*/

#pragma once

#include <stdlib.h>

typedef void (*vector_destroy_method)(void *);

typedef struct vector {
    void **data;
    size_t size;
    size_t capacity;
    vector_destroy_method destroy_method;
} vector_t;

vector_t *vector_construct(vector_destroy_method destroy_method);
int vector_destroy(vector_t *vector);
int vector_push_back(vector_t *vector, void *element);
void *vector_get(vector_t *vector, size_t index);
void vector_sort(vector_t *vector, int (*cmp)(const void *, const void *));
void vector_reverse(vector_t *vector);

void vector_destroy_free(void *object);
void vector_destroy_noop(void *object);
